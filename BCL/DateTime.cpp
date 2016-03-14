#include "BCL.h"

#include <Windows.h>

namespace System
{
	// Number of 100ns ticks per time unit
	static const int64_t TicksPerMillisecond = 10000;
	static const int64_t TicksPerSecond = TicksPerMillisecond * 1000;
	static const int64_t TicksPerMinute = TicksPerSecond * 60;
	static const int64_t TicksPerHour = TicksPerMinute * 60;
	static const int64_t TicksPerDay = TicksPerHour * 24;

	// Number of milliseconds per time unit
	static const int32_t MillisPerSecond = 1000;
	static const int32_t MillisPerMinute = MillisPerSecond * 60;
	static const int32_t MillisPerHour = MillisPerMinute * 60;
	static const int32_t MillisPerDay = MillisPerHour * 24;

	// Number of days in a non-leap year
	static const int32_t DaysPerYear = 365;
	// Number of days in 4 years
	static const int32_t DaysPer4Years = DaysPerYear * 4 + 1;       // 1461
	// Number of days in 100 years
	static const int32_t DaysPer100Years = DaysPer4Years * 25 - 1;  // 36524
	// Number of days in 400 years
	static const int32_t DaysPer400Years = DaysPer100Years * 4 + 1; // 146097

	// Number of days from 1/1/0001 to 12/31/1600
	static const int32_t DaysTo1601 = DaysPer400Years * 4;          // 584388
	// Number of days from 1/1/0001 to 12/30/1899
	static const int32_t DaysTo1899 = DaysPer400Years * 4 + DaysPer100Years * 3 - 367;
	// Number of days from 1/1/0001 to 12/31/9999
	static const int32_t DaysTo10000 = DaysPer400Years * 25 - 366;  // 3652059

	static const int64_t MinTicks = 0;
	static const int64_t MaxTicks = DaysTo10000 * TicksPerDay - 1;
	static const int64_t MaxMillis = int64_t(DaysTo10000) * MillisPerDay;

	static const int64_t FileTimeOffset = DaysTo1601 * TicksPerDay;
	static const int64_t DoubleDateOffset = DaysTo1899 * TicksPerDay;
	// The minimum OA date is 0100/01/01 (Note it's year 100).
	// The maximum OA date is 9999/12/31
	static const int64_t OADateMinAsTicks = (DaysPer100Years - DaysPerYear) * TicksPerDay;
	// All OA dates must be greater than (not >=) OADateMinAsDouble
	static const double OADateMinAsDouble = -657435.0;
	// All OA dates must be less than (not <=) OADateMaxAsDouble
	static const double OADateMaxAsDouble = 2958466.0;

	static const int32_t DatePartYear = 0;
	static const int32_t DatePartDayOfYear = 1;
	static const int32_t DatePartMonth = 2;
	static const int32_t DatePartDay = 3;

	static const int32_t DaysToMonth365[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	static const int32_t DaysToMonth366[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

	static const uint64_t TicksMask = 0x3FFFFFFFFFFFFFFF;
	static const uint64_t FlagsMask = 0xC000000000000000;
	static const uint64_t LocalMask = 0x8000000000000000;
	static const int64_t TicksCeiling = 0x4000000000000000;
	static const uint64_t KindUnspecified = 0x0000000000000000;
	static const uint64_t KindUtc = 0x4000000000000000;
	static const uint64_t KindLocal = 0x8000000000000000;
	static const uint64_t KindLocalAmbiguousDst = 0xC000000000000000;
	static const int32_t KindShift = 62;



	///  TimeSpan constants

	static const double MillisecondsPerTick = 1.0 / TicksPerMillisecond;

	static const double SecondsPerTick = 1.0 / TicksPerSecond;         // 0.0001

	static const double MinutesPerTick = 1.0 / TicksPerMinute; // 1.6666666666667e-9

	static const double HoursPerTick = 1.0 / TicksPerHour; // 2.77777777777777778e-11

	static const double DaysPerTick = 1.0 / TicksPerDay; // 1.1574074074074074074e-12

	static const int64_t MaxSeconds = MaxTicks / TicksPerSecond;
	static const int64_t MinSeconds = MinTicks / TicksPerSecond;
	
	static const int64_t MaxMilliSeconds = std::numeric_limits<int64_t>::max() / TicksPerMillisecond;
	static const int64_t MinMilliSeconds = std::numeric_limits<int64_t>::min() / TicksPerMillisecond;

	static const int64_t TicksPerTenthSecond = TicksPerMillisecond * 100;


	// DateTime public constants
	const DateTime DateTime::MinValue = DateTime(MinTicks, DateTimeKind::Unspecified);
	const DateTime DateTime::MaxValue = DateTime(MaxTicks, DateTimeKind::Unspecified);


	// Returns the tick count corresponding to the given year, month, and day.
	// Will check the if the parameters are valid.
	static int64_t DateToTicks(int32_t year, int32_t month, int32_t day)
	{
		if (!(year >= 1 && year <= 9999 && month >= 1 && month <= 12))
		{
			throw ArgumentOutOfRangeException("", "Bad Year Month Day");
		}
		const int32_t* days = DateTime::IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
		if (day >= 1 && day <= days[month] - days[month - 1])
		{
			int y = year - 1;
			int n = y * 365 + y / 4 - y / 100 + y / 400 + days[month - 1] + day - 1;
			return n * TicksPerDay;
		}
		throw ArgumentOutOfRangeException("", "Bad Year Month Day");
	}

	static int64_t TimeToTicks(int32_t hour, int32_t minute, int32_t second)
	{
		if (!(hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60))
		{
			throw ArgumentOutOfRangeException("", "Bad Hour Minute Second");
		}

		// totalSeconds is bounded by 2^31 * 2^12 + 2^31 * 2^8 + 2^31,
		// which is less than 2^44, meaning we won't overflow totalSeconds.
		auto totalSeconds = int64_t(hour) * 3600 + int64_t(minute) * 60 + int64_t(second);
		if (totalSeconds > MaxSeconds || totalSeconds < MinSeconds)
		{
			throw ArgumentOutOfRangeException("", "TimeSpan Too Long");
		}

		return totalSeconds * TicksPerSecond;
	}

	static uint64_t GetKindBits(DateTimeKind kind)
	{
		uint64_t kindBits;
		switch (kind)
		{
		case DateTimeKind::Unspecified: kindBits = 0; break;
		case DateTimeKind::Utc: kindBits = 1; break;
		case DateTimeKind::Local: kindBits = 2; break;
		default: throw ArgumentOutOfRangeException("kind");
		}
		return kindBits;
	}

	DateTime::DateTime(int64_t ticks, DateTimeKind kind, Boolean isAmbiguousDst)
		: value(uint64_t(ticks) | (isAmbiguousDst ? KindLocalAmbiguousDst : KindLocal))
	{
		if (ticks < MinTicks || ticks > MaxTicks)
		{
			throw new ArgumentOutOfRangeException("ticks", "DateTime Bad Ticks");
		}
		if (kind != DateTimeKind::Local) throw ArgumentException("Private constructor is for local times only", "kind");
	}

	DateTime::DateTime(int64_t ticks) : value(uint64_t(ticks))
	{
		if (ticks < MinTicks || ticks > MaxTicks)
			throw ArgumentOutOfRangeException("ticks", "DateTime Bad Ticks");
	}

	DateTime::DateTime(uint64_t ticks) : value(ticks)
	{
	}

	DateTime::DateTime(int64_t ticks, DateTimeKind kind) : value(uint64_t(ticks) | (GetKindBits(kind) << KindShift))
	{
		if (ticks < MinTicks || ticks > MaxTicks)
		{
			throw ArgumentOutOfRangeException("ticks", "DateTime Bad Ticks");
		}
	}

	DateTime::DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second) : value(DateToTicks(year, month, day) + TimeToTicks(hour, minute, second))
	{
	}

	DateTime::DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, int32_t millisecond)
		: value(DateToTicks(year, month, day) + TimeToTicks(hour, minute, second) + millisecond * TicksPerMillisecond)
	{
		if (millisecond < 0 || millisecond >= MillisPerSecond)
		{
			throw new ArgumentOutOfRangeException("millisecond");
		}
		if (int64_t(value) < MinTicks || int64_t(value) > MaxTicks)
		{
			throw new ArgumentException("DateTime Range");
		}
	}

	DateTime::DateTime(int32_t year, int32_t month, int32_t day) : value(uint64_t(DateToTicks(year, month, day)))
	{
	}

	DateTime::DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, DateTimeKind kind)
	{
		if (kind < DateTimeKind::Unspecified || kind > DateTimeKind::Local)
		{
			throw ArgumentException("Invalid DateTimeKind", "kind");
		}

		int64_t ticks = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
		value = (uint64_t(ticks) | (GetKindBits(kind) << KindShift));
	}

	int32_t DateTime::DaysInMonth(int32_t year, int32_t month)
	{
		if (month < 1 || month > 12) throw ArgumentOutOfRangeException("month");

		// IsLeapYear checks the year argument
		const int32_t* days = IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
		return days[month] - days[month - 1];
	}

	// Checks whether a given year is a leap year. This method returns true if
	// year is a leap year, or false if not.
	bool DateTime::IsLeapYear(int32_t year)
	{
		if (year < 1 || year > 9999)
		{
			throw ArgumentOutOfRangeException("year");
		}

		return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
	}

	DateTime DateTime::GetNow()
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		auto ticks = DateToTicks(time.wYear, time.wMonth, time.wDay)
			+ TimeToTicks(time.wHour, time.wMinute, time.wSecond)
			+ time.wMilliseconds * TicksPerMillisecond;
		return DateTime(uint64_t(ticks | KindLocal));
	}

	DateTime DateTime::GetUtcNow()
	{
		SYSTEMTIME sysTime;
		GetSystemTime(&sysTime);
		uint64_t ticks = DateToTicks(sysTime.wYear, sysTime.wMonth, sysTime.wDay)
			+ TimeToTicks(sysTime.wHour, sysTime.wMinute, sysTime.wSecond)
			+ sysTime.wMilliseconds * TicksPerMillisecond;
		return DateTime(uint64_t(ticks | KindUtc));
	}

	DateTimeKind DateTime::GetKind() const
	{
		switch (GetInternalKind())
		{
		case KindUnspecified: return DateTimeKind::Unspecified;
		case KindUtc: return DateTimeKind::Utc;
		default: return DateTimeKind::Local;
		}
	}

	int64_t DateTime::GetInternalTicks() const
	{
		return value & TicksMask;
	}

	uint64_t DateTime::GetInternalKind() const
	{
		return value & FlagsMask;
	}

	DateTime DateTime::GetToday()
	{
		return DateTime::GetNow().GetDate();
	}

	int64_t DateTime::GetTicks() const
	{
		return GetInternalTicks();
	}

	int32_t DateTime::GetMillisecond() const
	{
		return int32_t((GetInternalTicks() / TicksPerMillisecond) % 1000);
	}

	int32_t DateTime::GetSecond() const
	{
		return int32_t((GetInternalTicks() / TicksPerSecond) % 60);
	}

	int32_t DateTime::GetMinute() const
	{
		return int32_t((GetInternalTicks() / TicksPerMinute) % 60);
	}

	int32_t DateTime::GetHour() const
	{
		return int32_t((GetInternalTicks() / TicksPerHour) % 24);
	}

	int32_t DateTime::GetDay() const
	{
		return GetDatePart(DatePartDay);
	}

	int32_t DateTime::GetMonth() const
	{
		return GetDatePart(DatePartMonth);
	}

	int32_t DateTime::GetYear() const
	{
		return GetDatePart(DatePartYear);
	}

	int32_t DateTime::GetDayOfYear() const
	{
		return GetDatePart(DatePartDayOfYear);
	}

	DateTime DateTime::GetDate() const
	{
		int64_t ticks = GetInternalTicks();
		return DateTime(uint64_t((ticks - ticks % TicksPerDay) | GetInternalKind()));
	}

	int32_t DateTime::GetDatePart(int32_t part) const
	{
		auto ticks = GetInternalTicks();
		// n = number of days since 1/1/0001
		auto n = int(ticks / TicksPerDay);
		// y400 = number of whole 400-year periods since 1/1/0001
		auto y400 = n / DaysPer400Years;
		// n = day number within 400-year period
		n -= y400 * DaysPer400Years;
		// y100 = number of whole 100-year periods within 400-year period
		auto y100 = n / DaysPer100Years;
		// Last 100-year period has an extra day, so decrement result if 4
		if (y100 == 4) y100 = 3;
		// n = day number within 100-year period
		n -= y100 * DaysPer100Years;
		// y4 = number of whole 4-year periods within 100-year period
		auto y4 = n / DaysPer4Years;
		// n = day number within 4-year period
		n -= y4 * DaysPer4Years;
		// y1 = number of whole years within 4-year period
		auto y1 = n / DaysPerYear;
		// Last year has an extra day, so decrement result if 4
		if (y1 == 4) y1 = 3;
		// If year was requested, compute and return it
		if (part == DatePartYear)
		{
			return y400 * 400 + y100 * 100 + y4 * 4 + y1 + 1;
		}
		// n = day number within year
		n -= y1 * DaysPerYear;
		// If day-of-year was requested, return it
		if (part == DatePartDayOfYear) return n + 1;
		// Leap year calculation looks different from IsLeapYear since y1, y4,
		// and y100 are relative to year 1, not year 0
		auto leapYear = y1 == 3 && (y4 != 24 || y100 == 3);
		auto days = leapYear ? DaysToMonth366 : DaysToMonth365;
		// All months have less than 32 days, so n >> 5 is a good conservative
		// estimate for the month
		auto m = (n >> 5) + 1;
		// m = 1-based month number
		while (n >= days[m]) m++;
		// If month was requested, return it
		if (part == DatePartMonth) return m;
		// Return 1-based day-of-month
		return n - days[m - 1] + 1;
	}

	DateTime DateTime::AddTicks(int64_t value) const
	{
		auto ticks = GetInternalTicks();
		if (value > MaxTicks - ticks || value < MinTicks - ticks)
		{
			throw ArgumentOutOfRangeException("value", "Bad Date Arithmetic");
		}
		return DateTime(uint64_t((ticks + value) | GetInternalKind()));
	}

	DateTime DateTime::Add(double value, int32_t scale) const
	{
		int64_t millis = int64_t(value * scale + (value >= 0 ? 0.5 : -0.5));
		if (millis <= -MaxMillis || millis >= MaxMillis) throw ArgumentOutOfRangeException("value", "Add Value");
		return AddTicks(millis * TicksPerMillisecond);
	}

	DateTime DateTime::Add(const TimeSpan& value) const
	{
		return AddTicks(value.GetTicks());
	}

	DateTime DateTime::Subtract(const TimeSpan& value) const
	{
		return AddTicks(-value.GetTicks());
	}

	DateTime DateTime::AddMilliseconds(double value) const
	{
		return Add(value, 1);
	}

	DateTime DateTime::AddSeconds(double value) const
	{
		return Add(value, MillisPerSecond);
	}

	DateTime DateTime::AddMinutes(double value) const
	{
		return Add(value, MillisPerMinute);
	}

	DateTime DateTime::AddHours(double value) const
	{
		return Add(value, MillisPerHour);
	}

	DateTime DateTime::AddDays(double value) const
	{
		return Add(value, MillisPerDay);
	}

	DateTime DateTime::AddMonths(int32_t months) const
	{
		if (months < -120000 || months > 120000)
		{
			throw ArgumentOutOfRangeException("months", "DateTime Bad Months");
		}

		int y = GetDatePart(DatePartYear);
		int m = GetDatePart(DatePartMonth);
		int d = GetDatePart(DatePartDay);
		int i = m - 1 + months;
		if (i >= 0)
		{
			m = i % 12 + 1;
			y = y + i / 12;
		}
		else
		{
			m = 12 + (i + 1) % 12;
			y = y + (i - 11) / 12;
		}
		if (y < 1 || y > 9999)
		{
			throw ArgumentOutOfRangeException("months", "Date Arithmetic");
		}
		int days = DaysInMonth(y, m);
		if (d > days) d = days;

		return DateTime(uint64_t((DateToTicks(y, m, d) + GetInternalTicks() % TicksPerDay) | GetInternalKind()));
	}

	DateTime DateTime::AddYears(int32_t years) const
	{
		if (years < -10000 || years > 10000) throw ArgumentOutOfRangeException("years", "DateTime Bad Years");
		return AddMonths(years * 12);
	}

	int32_t DateTime::GetHashCode() const
	{
		int64_t ticks = GetInternalTicks();
		return int32_t(ticks) ^ int32_t(ticks >> 32);
	}

	int32_t DateTime::CompareTo(const DateTime& other) const
	{
		auto valueTicks = other.GetInternalTicks();
		auto ticks = GetInternalTicks();
		if (ticks > valueTicks) return 1;
		if (ticks < valueTicks) return -1;
		return 0;
	}

	DateTime DateTime::operator+(const TimeSpan& other) const
	{
		return Add(other);
	}

	DateTime DateTime::operator-(const TimeSpan& other) const
	{
		return Subtract(other);
	}

	Boolean DateTime::operator>(const DateTime& other) const
	{
		return value > other.value;
	}

	Boolean DateTime::operator<(const DateTime& other) const
	{
		return value < other.value;
	}

	Boolean DateTime::operator>=(const DateTime& other) const
	{
		return value >= other.value;
	}

	Boolean DateTime::operator<=(const DateTime& other) const
	{
		return value <= other.value;
	}

	Boolean DateTime::operator==(const DateTime& other) const
	{
		return value == other.value;
	}

	Boolean DateTime::operator!=(const DateTime& other) const
	{
		return value != other.value;
	}

	Boolean DateTime::Equals(const DateTime& other) const
	{
		return value == other.value;
	}

	/////////////////////////////////////////////////////////////////////////
	// Implementation of TimeSpan

	const TimeSpan TimeSpan::Zero = TimeSpan(0);
	const TimeSpan TimeSpan::MaxValue = TimeSpan(int64_t::MaxValue);
	const TimeSpan TimeSpan::MinValue = TimeSpan(int64_t::MinValue);

	TimeSpan::TimeSpan(int64_t ticks) : ticks(ticks)
	{
	}

	TimeSpan::TimeSpan(int32_t hours, int32_t minutes, int32_t seconds)
	{
		ticks = TimeToTicks(hours, minutes, seconds);
	}

	TimeSpan::TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds)
	{
		int64_t totalMilliSeconds = (int64_t(days) * 3600 * 24 + int64_t(hours) * 3600 + int64_t(minutes) * 60 + seconds) * 1000 + milliseconds;
		if (totalMilliSeconds > MaxMilliSeconds || totalMilliSeconds < MinMilliSeconds)
		{
			throw ArgumentOutOfRangeException("", "TimeSpan Too Long");
		}
		ticks = int64_t(totalMilliSeconds) * TicksPerMillisecond;
	}

	int32_t TimeSpan::GetDays() const
	{
		return int32_t(ticks / TicksPerDay);
	}

	int32_t TimeSpan::GetMilliseconds() const
	{
		return int32_t((ticks / TicksPerMillisecond) % 1000);
	}

	int32_t TimeSpan::GetSeconds() const
	{
		return int32_t((ticks / TicksPerSecond) % 60);
	}

	int32_t TimeSpan::GetMinutes() const
	{
		return int32_t((ticks / TicksPerMinute) % 60);
	}

	int32_t TimeSpan::GetHours() const
	{
		return int32_t((ticks / TicksPerHour) % 24);
	}

	int64_t TimeSpan::GetTicks() const
	{
		return ticks;
	}

	double TimeSpan::GetTotalDays() const
	{
		return double(ticks) * DaysPerTick;
	}

	double TimeSpan::GetTotalHours() const
	{
		return double(ticks) * HoursPerTick;
	}

	double TimeSpan::GetTotalSeconds() const
	{
		return double(ticks) * SecondsPerTick;
	}

	double TimeSpan::GetTotalMinutes() const
	{
		return double(ticks) * MinutesPerTick;
	}

	double TimeSpan::GetTotalMilliseconds() const
	{
		double temp = double(ticks) * MillisecondsPerTick;
		if (temp > MaxMilliSeconds)
			return double(MaxMilliSeconds);

		if (temp < MinMilliSeconds)
			return double(MinMilliSeconds);

		return temp;
	}

	TimeSpan TimeSpan::Duration() const
	{
		if (ticks == TimeSpan::MinValue.ticks) throw OverflowException("Duration");
		return TimeSpan(ticks >= 0 ? ticks : -ticks);
	}

	Boolean TimeSpan::operator>(const TimeSpan& other) const
	{
		return ticks > other.ticks;
	}

	Boolean TimeSpan::operator<(const TimeSpan& other) const
	{
		return ticks < other.ticks;
	}

	Boolean TimeSpan::operator>=(const TimeSpan& other) const
	{
		return ticks >= other.ticks;
	}

	Boolean TimeSpan::operator<=(const TimeSpan& other) const
	{
		return ticks <= other.ticks;
	}

	Boolean TimeSpan::operator==(const TimeSpan& other) const
	{
		return ticks == other.ticks;
	}

	Boolean TimeSpan::operator!=(const TimeSpan& other) const
	{
		return ticks != other.ticks;
	}

	TimeSpan TimeSpan::operator+(const TimeSpan& ts) const
	{
		return Add(ts);
	}

	TimeSpan TimeSpan::operator-(const TimeSpan& ts) const
	{
		return Subtract(ts);
	}

	TimeSpan TimeSpan::Add(const TimeSpan& ts) const
	{
		auto result = ticks + ts.ticks;
		// Overflow if signs of operands was identical and result's
		// sign was opposite.
		// >> 63 gives the sign bit (either 64 1's or 64 0's).
		if ((ticks >> 63 == ts.ticks >> 63) && (ticks >> 63 != result >> 63))
		{
			throw OverflowException("Time Span Too Long");
		}
		return TimeSpan(result);
	}

	TimeSpan TimeSpan::Subtract(const TimeSpan& ts) const
	{
		auto result = ticks - ts.ticks;

		// Overflow if signs of operands was identical and result's
		// sign was opposite.
		// >> 63 gives the sign bit (either 64 1's or 64 0's).
		if ((ticks >> 63 == ts.ticks >> 63) && (ticks >> 63 != result >> 63))
		{
			throw OverflowException("Time Span Too Long");
		}
		return TimeSpan(result);
	}

	TimeSpan TimeSpan::Negate() const
	{
		if (ticks == TimeSpan::MinValue.ticks)
			throw OverflowException("Negate Twos Complement Number");

		return TimeSpan(-ticks);
	}

	static TimeSpan Interval(double value, int32_t scale)
	{
		if (double::IsNaN(value)) throw ArgumentException("Can not Be NaN");

		double tmp = value * scale;
		auto millis = tmp + (value >= 0 ? 0.5 : -0.5);
		if ((millis > int64_t::MaxValue / TicksPerMillisecond) || (millis < int64_t::MinValue / TicksPerMillisecond))
		{
			throw OverflowException("TimeSpan Too Long");
		}
		return TimeSpan(int64_t(millis) * TicksPerMillisecond);
	}

	TimeSpan TimeSpan::FromMilliseconds(double value)
	{
		return Interval(value, 1);
	}

	TimeSpan TimeSpan::FromSeconds(double value)
	{
		return Interval(value, MillisPerSecond);
	}

	TimeSpan TimeSpan::FromMinutes(double value)
	{
		return Interval(value, MillisPerMinute);
	}

	TimeSpan TimeSpan::FromHours(double value)
	{
		return Interval(value, MillisPerHour);
	}

	TimeSpan TimeSpan::FromDays(double value)
	{
		return Interval(value, MillisPerDay);
	}

	int32_t TimeSpan::CompareTo(const TimeSpan& value) const
	{
		if (ticks > value.ticks) return 1;
		if (ticks < value.ticks) return -1;
		return 0;
	}

	Boolean TimeSpan::Equals(const TimeSpan& span) const
	{
		return ticks == span.ticks;
	}

	int32_t TimeSpan::GetHashCode() const
	{
		return int32_t(ticks) ^ int32_t(ticks >> 32);
	}

	/////////////////////////////////////////////////////////////////////////
	// Implementation of DateTimeOffset

	const int64_t MaxOffset = TicksPerHour * 14;
	const int64_t MinOffset = -MaxOffset;

	static DateTime ValidateDate(DateTime dateTime, TimeSpan offset)
	{
		// The key validation is that both the UTC and clock times fit. The clock time is validated
		// by the DateTime constructor.
		if (!(offset.GetTicks() >= MinOffset && offset.GetTicks() <= MaxOffset))
		{
			throw ArgumentOutOfRangeException("offset", "Offset not validated.");
		}
		// This operation cannot overflow because offset should have already been validated to be within
		// 14 hours and the DateTime instance is more than that distance from the boundaries of int64_t.
		int64_t utcTicks = dateTime.GetTicks() - offset.GetTicks();
		if (utcTicks < MinTicks || utcTicks > MaxTicks)
		{
			throw ArgumentOutOfRangeException("offset", "UTC Out Of Range");
		}
		// make sure the Kind is set to Unspecified
		return DateTime(utcTicks, DateTimeKind::Unspecified);
	}

	// Ensures the TimeSpan is valid to go in a DateTimeOffset.
	static Int16 ValidateOffset(TimeSpan offset)
	{
		int64_t ticks = offset.GetTicks();
		if (ticks % TicksPerMinute != 0)
		{
			throw ArgumentException("Offset Precision", "offset");
		}
		if (ticks < MinOffset || ticks > MaxOffset)
		{
			throw ArgumentOutOfRangeException("offset", "Offset Out Of Range");
		}
		return int16_t(offset.GetTicks() / TicksPerMinute);
	}

	DateTimeOffset::DateTimeOffset(DateTime value, Int16 offset)
		: dateTime(value), offset(offset)
	{
	}

	DateTimeOffset::DateTimeOffset(int64_t ticks, TimeSpan offset)
		: dateTime(ValidateDate(DateTime(ticks), offset)), offset(ValidateOffset(offset))
	{
	}

	DateTimeOffset::DateTimeOffset(DateTime dateTime, TimeSpan offset)
		: dateTime(ValidateDate(dateTime, offset)), offset(ValidateOffset(offset))
	{
		if (dateTime.GetKind() == DateTimeKind::Local)
		{
			throw ArgumentException("Date local not supported", "offset");
		}
		else if (dateTime.GetKind() == DateTimeKind::Utc)
		{
			if (offset != TimeSpan::Zero)
			{
				throw ArgumentException("Offset Utc Mismatch", "offset");
			}
		}
	}

	DateTimeOffset::DateTimeOffset(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, TimeSpan offset)
		: dateTime(ValidateDate(DateTime(year, month, day, hour, minute, second), offset)), offset(ValidateOffset(offset))
	{
	}

	DateTimeOffset::DateTimeOffset(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, int32_t millisecond, TimeSpan offset)
		: dateTime(ValidateDate(DateTime(year, month, day, hour, minute, second, millisecond), offset)), offset(ValidateOffset(offset))
	{
	}

	DateTime DateTimeOffset::GetClockDateTime() const
	{
		return DateTime((dateTime + GetOffset()).GetTicks(), DateTimeKind::Unspecified);
	}

	TimeSpan DateTimeOffset::GetOffset() const
	{
		return TimeSpan(0, int32_t(offset), 0);
	}

	DateTime DateTimeOffset::GetDateTime() const
	{
		return GetClockDateTime();
	}

	DateTime DateTimeOffset::GetUtcDateTime() const
	{
		return DateTime(dateTime.GetTicks(), DateTimeKind::Utc);
	}

	int64_t DateTimeOffset::GetTicks() const
	{
		return GetClockDateTime().GetTicks();
	}

	int64_t DateTimeOffset::GetUtcTicks() const
	{
		return GetUtcDateTime().GetTicks();
	}

	int32_t DateTimeOffset::GetMillisecond() const
	{
		return GetClockDateTime().GetMillisecond();
	}

	int32_t DateTimeOffset::GetSecond() const
	{
		return GetClockDateTime().GetSecond();
	}

	int32_t DateTimeOffset::GetMinute() const
	{
		return GetClockDateTime().GetMinute();
	}

	int32_t DateTimeOffset::GetHour() const
	{
		return GetClockDateTime().GetHour();
	}

	int32_t DateTimeOffset::GetDay() const
	{
		return GetClockDateTime().GetDay();
	}

	int32_t DateTimeOffset::GetMonth() const
	{
		return GetClockDateTime().GetMonth();
	}

	int32_t DateTimeOffset::GetYear() const
	{
		return GetClockDateTime().GetYear();
	}

	int32_t DateTimeOffset::GetDayOfYear() const
	{
		return GetClockDateTime().GetDayOfYear();
	}

	DateTime DateTimeOffset::GetDate() const
	{
		return GetClockDateTime().GetDate();
	}


	DateTimeOffset DateTimeOffset::AddTicks(int64_t value) const
	{
		return DateTimeOffset(GetClockDateTime().AddTicks(value), offset);
	}

	DateTimeOffset DateTimeOffset::Add(const TimeSpan& value) const
	{
		return DateTimeOffset(GetClockDateTime().Add(value), offset);
	}

	DateTimeOffset DateTimeOffset::Subtract(const TimeSpan& value) const
	{
		return DateTimeOffset(GetClockDateTime().Subtract(value), offset);
	}

	DateTimeOffset DateTimeOffset::AddMilliseconds(double value) const
	{
		return DateTimeOffset(GetClockDateTime().AddMilliseconds(value), offset);
	}

	DateTimeOffset DateTimeOffset::AddSeconds(double value) const
	{
		return DateTimeOffset(GetClockDateTime().AddSeconds(value), offset);
	}

	DateTimeOffset DateTimeOffset::AddMinutes(double value) const
	{
		return DateTimeOffset(GetClockDateTime().AddMinutes(value), offset);
	}

	DateTimeOffset DateTimeOffset::AddHours(double value) const
	{
		return DateTimeOffset(GetClockDateTime().AddHours(value), offset);
	}

	DateTimeOffset DateTimeOffset::AddDays(double value) const
	{
		return DateTimeOffset(GetClockDateTime().AddDays(value), offset);
	}

	DateTimeOffset DateTimeOffset::AddMonths(int32_t value) const
	{
		return DateTimeOffset(GetClockDateTime().AddMonths(value), offset);
	}

	DateTimeOffset DateTimeOffset::AddYears(int32_t value) const
	{
		return DateTimeOffset(GetClockDateTime().AddYears(value), offset);
	}

	DateTimeOffset DateTimeOffset::GetNow()
	{
		SYSTEMTIME time;
		GetLocalTime(&time);

		DYNAMIC_TIME_ZONE_INFORMATION dynamicTimeZoneInfo;
		auto mode = GetDynamicTimeZoneInformation(&dynamicTimeZoneInfo);

		auto offset = dynamicTimeZoneInfo.Bias;
		switch (mode)
		{
		case TIME_ZONE_ID_STANDARD: offset += dynamicTimeZoneInfo.StandardBias; break;
		case TIME_ZONE_ID_DAYLIGHT: offset += dynamicTimeZoneInfo.DaylightBias; break;
		}

		return DateTimeOffset(time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, TimeSpan(offset*TicksPerMinute));
	}

	DateTimeOffset DateTimeOffset::GetUtcNow()
	{
		SYSTEMTIME time;
		GetSystemTime(&time);
		return DateTimeOffset(time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, TimeSpan(0));
	}
}