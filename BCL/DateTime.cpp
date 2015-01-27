#include "BCL.h"

#include <Windows.h>

namespace System
{
	// Number of 100ns ticks per time unit
	static const Int64 TicksPerMillisecond = 10000;
	static const Int64 TicksPerSecond = TicksPerMillisecond * 1000;
	static const Int64 TicksPerMinute = TicksPerSecond * 60;
	static const Int64 TicksPerHour = TicksPerMinute * 60;
	static const Int64 TicksPerDay = TicksPerHour * 24;

	// Number of milliseconds per time unit
	static const Int32 MillisPerSecond = 1000;
	static const Int32 MillisPerMinute = MillisPerSecond * 60;
	static const Int32 MillisPerHour = MillisPerMinute * 60;
	static const Int32 MillisPerDay = MillisPerHour * 24;

	// Number of days in a non-leap year
	static const Int32 DaysPerYear = 365;
	// Number of days in 4 years
	static const Int32 DaysPer4Years = DaysPerYear * 4 + 1;       // 1461
	// Number of days in 100 years
	static const Int32 DaysPer100Years = DaysPer4Years * 25 - 1;  // 36524
	// Number of days in 400 years
	static const Int32 DaysPer400Years = DaysPer100Years * 4 + 1; // 146097

	// Number of days from 1/1/0001 to 12/31/1600
	static const Int32 DaysTo1601 = DaysPer400Years * 4;          // 584388
	// Number of days from 1/1/0001 to 12/30/1899
	static const Int32 DaysTo1899 = DaysPer400Years * 4 + DaysPer100Years * 3 - 367;
	// Number of days from 1/1/0001 to 12/31/9999
	static const Int32 DaysTo10000 = DaysPer400Years * 25 - 366;  // 3652059

	static const Int64 MinTicks = 0;
	static const Int64 MaxTicks = DaysTo10000 * TicksPerDay - 1;
	static const Int64 MaxMillis = (Int64)DaysTo10000 * MillisPerDay;

	static const Int64 FileTimeOffset = DaysTo1601 * TicksPerDay;
	static const Int64 DoubleDateOffset = DaysTo1899 * TicksPerDay;
	// The minimum OA date is 0100/01/01 (Note it's year 100).
	// The maximum OA date is 9999/12/31
	static const Int64 OADateMinAsTicks = (DaysPer100Years - DaysPerYear) * TicksPerDay;
	// All OA dates must be greater than (not >=) OADateMinAsDouble
	static const Double OADateMinAsDouble = -657435.0;
	// All OA dates must be less than (not <=) OADateMaxAsDouble
	static const Double OADateMaxAsDouble = 2958466.0;

	static const Int32 DatePartYear = 0;
	static const Int32 DatePartDayOfYear = 1;
	static const Int32 DatePartMonth = 2;
	static const Int32 DatePartDay = 3;

	static const Int32 DaysToMonth365[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	static const Int32 DaysToMonth366[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

	static const UInt64 TicksMask = 0x3FFFFFFFFFFFFFFF;
	static const UInt64 FlagsMask = 0xC000000000000000;
	static const UInt64 LocalMask = 0x8000000000000000;
	static const Int64 TicksCeiling = 0x4000000000000000;
	static const uint64_t KindUnspecified = 0x0000000000000000;
	static const uint64_t KindUtc = 0x4000000000000000;
	static const uint64_t KindLocal = 0x8000000000000000;
	static const uint64_t KindLocalAmbiguousDst = 0xC000000000000000;
	static const Int32 KindShift = 62;



	///  TimeSpan constants

	static const Double MillisecondsPerTick = 1.0 / TicksPerMillisecond;

	static const Double SecondsPerTick = 1.0 / TicksPerSecond;         // 0.0001

	static const Double MinutesPerTick = 1.0 / TicksPerMinute; // 1.6666666666667e-9

	static const Double HoursPerTick = 1.0 / TicksPerHour; // 2.77777777777777778e-11

	static const Double DaysPerTick = 1.0 / TicksPerDay; // 1.1574074074074074074e-12

	static const Int64 MaxSeconds = Int64::MaxValue / TicksPerSecond;
	static const Int64 MinSeconds = Int64::MinValue / TicksPerSecond;

	static const Int64 MaxMilliSeconds = Int64::MaxValue / TicksPerMillisecond;
	static const Int64 MinMilliSeconds = Int64::MinValue / TicksPerMillisecond;

	static const Int64 TicksPerTenthSecond = TicksPerMillisecond * 100;


	// DateTime public constants
	const DateTime DateTime::MinValue = DateTime(MinTicks, DateTimeKind::Unspecified);
	const DateTime DateTime::MaxValue = DateTime(MaxTicks, DateTimeKind::Unspecified);


	// Returns the tick count corresponding to the given year, month, and day.
	// Will check the if the parameters are valid.
	static Int64 DateToTicks(Int32 year, Int32 month, Int32 day)
	{
		if (!(year >= 1 && year <= 9999 && month >= 1 && month <= 12))
		{
			throw ArgumentOutOfRangeException("", "Bad Year Month Day");
		}
		const Int32* days = DateTime::IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
		if (day >= 1 && day <= days[month] - days[month - 1])
		{
			int y = year - 1;
			int n = y * 365 + y / 4 - y / 100 + y / 400 + days[month - 1] + day - 1;
			return n * TicksPerDay;
		}
		throw ArgumentOutOfRangeException("", "Bad Year Month Day");
	}

	static Int64 TimeToTicks(Int32 hour, Int32 minute, Int32 second)
	{
		if (!(hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60))
		{
			throw ArgumentOutOfRangeException("", "Bad Hour Minute Second");
		}

		// totalSeconds is bounded by 2^31 * 2^12 + 2^31 * 2^8 + 2^31,
		// which is less than 2^44, meaning we won't overflow totalSeconds.
		Int64 totalSeconds = (Int64)hour * 3600 + (Int64)minute * 60 + (Int64)second;
		if (totalSeconds > MaxSeconds || totalSeconds < MinSeconds)
		{
			throw ArgumentOutOfRangeException("", "TimeSpan Too Long");
		}

		return totalSeconds * TicksPerSecond;
	}

	static UInt64 GetKindBits(DateTimeKind kind)
	{
		UInt64 kindBits;
		switch (kind)
		{
		case DateTimeKind::Unspecified: kindBits = 0; break;
		case DateTimeKind::Utc: kindBits = 1; break;
		case DateTimeKind::Local: kindBits = 2; break;
		default: throw ArgumentOutOfRangeException("kind");
		}
		return kindBits;
	}

	DateTime::DateTime(Int64 ticks, DateTimeKind kind, Boolean isAmbiguousDst) 
		: value((UInt64)ticks | (isAmbiguousDst ? KindLocalAmbiguousDst : KindLocal))
	{
		if (ticks < MinTicks || ticks > MaxTicks) 
		{
			throw new ArgumentOutOfRangeException("ticks", "DateTime Bad Ticks");
		}
		if (kind != DateTimeKind::Local) throw ArgumentException("Private constructor is for local times only", "kind");
	}

	DateTime::DateTime(Int64 ticks) : value((UInt64)ticks)
	{
		if (ticks < MinTicks || ticks > MaxTicks)
			throw ArgumentOutOfRangeException("ticks", "DateTime Bad Ticks");
	}

	DateTime::DateTime(UInt64 ticks) : value(ticks)
	{
	}

	DateTime::DateTime(Int64 ticks, DateTimeKind kind) : value((UInt64)ticks | (GetKindBits(kind) << KindShift))
	{
		if (ticks < MinTicks || ticks > MaxTicks)
		{
			throw ArgumentOutOfRangeException("ticks", "DateTime Bad Ticks");
		}
	}

	DateTime::DateTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second) : value(DateToTicks(year, month, day) + TimeToTicks(hour, minute, second))
	{
	}

	DateTime::DateTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, Int32 millisecond) 
		: value(DateToTicks(year, month, day) + TimeToTicks(hour, minute, second) + millisecond * TicksPerMillisecond)
	{
		if (millisecond < 0 || millisecond >= MillisPerSecond) 
		{
			throw new ArgumentOutOfRangeException("millisecond");
		}
		if ((Int64)value < MinTicks || (Int64)value > MaxTicks)
		{
			throw new ArgumentException("DateTime Range");
		}
	}

	DateTime::DateTime(Int32 year, Int32 month, Int32 day) : value((UInt64)DateToTicks(year, month, day))
	{
	}

	DateTime::DateTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, DateTimeKind kind)
	{
		if (kind < DateTimeKind::Unspecified || kind > DateTimeKind::Local)
		{
			throw ArgumentException("Invalid DateTimeKind", "kind");
		}

		Int64 ticks = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
		value = ((UInt64)ticks | (GetKindBits(kind) << KindShift));
	}

	Int32 DateTime::DaysInMonth(Int32 year, Int32 month)
	{
		if (month < 1 || month > 12) throw ArgumentOutOfRangeException("month");
		
		// IsLeapYear checks the year argument
		const Int32* days = IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
		return days[month] - days[month - 1];
	}

	// Checks whether a given year is a leap year. This method returns true if
	// year is a leap year, or false if not.
	bool DateTime::IsLeapYear(Int32 year)
	{
		if (year < 1 || year > 9999)
		{
			throw ArgumentOutOfRangeException("year");
		}

		return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
	}

	DateTime DateTime::GetNow()
	{
		DateTime utc = GetUtcNow();
		Boolean isAmbiguousLocalDst = false;
		
		DYNAMIC_TIME_ZONE_INFORMATION timeZone;
		DWORD currentMode = GetDynamicTimeZoneInformation(&timeZone);
		Int64 offset = timeZone.Bias * TicksPerMinute;
		if (currentMode == TIME_ZONE_ID_DAYLIGHT)
		{
			offset += timeZone.DaylightBias * TicksPerMinute;
		}
		else if (currentMode == TIME_ZONE_ID_STANDARD)
		{
			offset += timeZone.StandardBias * TicksPerMinute;
		}

		// Int64 offset = TimeZoneInfo.GetDateTimeNowUtcOffsetFromUtc(utc, out isAmbiguousLocalDst).Ticks;
		auto tick = utc.GetTicks() + offset;
		if (tick > MaxTicks)
		{
			return DateTime(MaxTicks, DateTimeKind::Local);
		}
		if (tick < MinTicks) 
		{
			return DateTime(MinTicks, DateTimeKind::Local);
		}
		return DateTime(tick, DateTimeKind::Local, isAmbiguousLocalDst);
	}

	DateTime DateTime::GetUtcNow()
	{
		SYSTEMTIME sysTime;
		GetSystemTime(&sysTime);
		uint64_t ticks = DateToTicks(sysTime.wYear, sysTime.wMonth, sysTime.wDay) 
			+ TimeToTicks(sysTime.wHour, sysTime.wMinute, sysTime.wSecond) 
			+ sysTime.wMilliseconds * TicksPerMillisecond;
		return DateTime((UInt64)(ticks | (uint64_t)KindUtc));
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

	Int64 DateTime::GetInternalTicks() const
	{
		return value & TicksMask;
	}

	UInt64 DateTime::GetInternalKind() const
	{
		return value & FlagsMask;
	}

	DateTime DateTime::GetToday()
	{
		return DateTime::GetNow().GetDate();
	}

	Int64 DateTime::GetTicks() const
	{
		return GetInternalTicks();
	}

	Int32 DateTime::GetMillisecond() const
	{
		return (Int32)((GetInternalTicks() / TicksPerMillisecond) % 1000);
	}

	Int32 DateTime::GetSecond() const
	{
		return (Int32)((GetInternalTicks() / TicksPerSecond) % 60);
	}

	Int32 DateTime::GetMinute() const
	{
		return (Int32)((GetInternalTicks() / TicksPerMinute) % 60);
	}

	Int32 DateTime::GetHour() const
	{
		return (Int32)((GetInternalTicks() / TicksPerHour) % 24);
	}

	Int32 DateTime::GetDay() const
	{
		return GetDatePart(DatePartDay);
	}

	Int32 DateTime::GetMonth() const
	{
		return GetDatePart(DatePartMonth);
	}

	Int32 DateTime::GetYear() const
	{
		return GetDatePart(DatePartYear);
	}

	Int32 DateTime::GetDayOfYear() const
	{
		return GetDatePart(DatePartDayOfYear);
	}

	DateTime DateTime::GetDate() const
	{
		Int64 ticks = GetInternalTicks();
		return DateTime((UInt64)((ticks - ticks % TicksPerDay) | GetInternalKind()));
	}

	Int32 DateTime::GetDatePart(Int32 part) const
	{
		Int64 ticks = GetInternalTicks();
		// n = number of days since 1/1/0001
		int n = (int)(ticks / TicksPerDay);
		// y400 = number of whole 400-year periods since 1/1/0001
		int y400 = n / DaysPer400Years;
		// n = day number within 400-year period
		n -= y400 * DaysPer400Years;
		// y100 = number of whole 100-year periods within 400-year period
		int y100 = n / DaysPer100Years;
		// Last 100-year period has an extra day, so decrement result if 4
		if (y100 == 4) y100 = 3;
		// n = day number within 100-year period
		n -= y100 * DaysPer100Years;
		// y4 = number of whole 4-year periods within 100-year period
		int y4 = n / DaysPer4Years;
		// n = day number within 4-year period
		n -= y4 * DaysPer4Years;
		// y1 = number of whole years within 4-year period
		int y1 = n / DaysPerYear;
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
		bool leapYear = y1 == 3 && (y4 != 24 || y100 == 3);
		const Int32* days = leapYear ? DaysToMonth366 : DaysToMonth365;
		// All months have less than 32 days, so n >> 5 is a good conservative
		// estimate for the month
		int m = (n >> 5) + 1;
		// m = 1-based month number
		while (n >= days[m]) m++;
		// If month was requested, return it
		if (part == DatePartMonth) return m;
		// Return 1-based day-of-month
		return n - days[m - 1] + 1;
	}

	DateTime DateTime::AddTicks(Int64 value) const
	{
		auto ticks = GetInternalTicks();
		if (value > MaxTicks - ticks || value < MinTicks - ticks)
		{
			throw ArgumentOutOfRangeException("value", "Bad Date Arithmetic");
		}
		return DateTime((UInt64)((ticks + value) | GetInternalKind()));
	}

	DateTime DateTime::Add(Double value, Int32 scale) const
	{
		Int64 millis = (int64_t)(value * scale + (value >= 0 ? 0.5 : -0.5));
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

	DateTime DateTime::AddMilliseconds(Double value) const
	{
		return Add(value, 1);
	}

	DateTime DateTime::AddSeconds(Double value) const
	{
		return Add(value, MillisPerSecond);
	}

	DateTime DateTime::AddMinutes(Double value) const
	{
		return Add(value, MillisPerMinute);
	}

	DateTime DateTime::AddHours(Double value) const
	{
		return Add(value, MillisPerHour);
	}

	DateTime DateTime::AddDays(Double value) const
	{
		return Add(value, MillisPerDay);
	}

	DateTime DateTime::AddMonths(Int32 months) const
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

		return DateTime((UInt64)((DateToTicks(y, m, d) + GetInternalTicks() % TicksPerDay) | GetInternalKind()));
	}

	DateTime DateTime::AddYears(Int32 years) const
	{
		if (years < -10000 || years > 10000) throw ArgumentOutOfRangeException("years", "DateTime Bad Years");
		return AddMonths(years * 12);
	}

	Int32 DateTime::GetHashCode() const
	{
		int64_t ticks = GetInternalTicks();
		return (int32_t)ticks ^ (int32_t)(ticks >> 32);
	}

	Int32 DateTime::CompareTo(const DateTime& other) const
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
	const TimeSpan TimeSpan::MaxValue = TimeSpan(Int64::MaxValue);
	const TimeSpan TimeSpan::MinValue = TimeSpan(Int64::MinValue);

	TimeSpan::TimeSpan(Int64 ticks) : ticks(ticks)
	{
	}

	TimeSpan::TimeSpan(Int32 hours, Int32 minutes, Int32 seconds)
	{
		ticks = TimeToTicks(hours, minutes, seconds);
	}

	TimeSpan::TimeSpan(Int32 days, Int32 hours, Int32 minutes, Int32 seconds, Int32 milliseconds)
	{
		Int64 totalMilliSeconds = ((Int64)days * 3600 * 24 + (Int64)hours * 3600 + (Int64)minutes * 60 + seconds) * 1000 + milliseconds;
		if (totalMilliSeconds > MaxMilliSeconds || totalMilliSeconds < MinMilliSeconds)
		{
			throw ArgumentOutOfRangeException("", "TimeSpan Too Long");
		}
		ticks = (Int64)totalMilliSeconds * TicksPerMillisecond;
	}

	Int32 TimeSpan::GetDays() const
	{
		return (int32_t)(ticks / TicksPerDay);
	}

	Int32 TimeSpan::GetMilliseconds() const
	{
		return (int32_t)((ticks / TicksPerMillisecond) % 1000);
	}

	Int32 TimeSpan::GetSeconds() const
	{
		return (int32_t)((ticks / TicksPerSecond) % 60);
	}

	Int32 TimeSpan::GetMinutes() const
	{
		return (int32_t)((ticks / TicksPerMinute) % 60);
	}

	Int32 TimeSpan::GetHours() const
	{
		return (int32_t)((ticks / TicksPerHour) % 24);
	}

	Int64 TimeSpan::GetTicks() const
	{
		return ticks;
	}

	Double TimeSpan::GetTotalDays() const
	{
		return ((double)ticks) * DaysPerTick;
	}

	Double TimeSpan::GetTotalHours() const
	{
		return (double)ticks * HoursPerTick;
	}

	Double TimeSpan::GetTotalSeconds() const
	{
		return (double)ticks * SecondsPerTick;
	}

	Double TimeSpan::GetTotalMinutes() const
	{
		return (double)ticks * MinutesPerTick;
	}

	Double TimeSpan::GetTotalMilliseconds() const
	{
		Double temp = (double)ticks * MillisecondsPerTick;
		if (temp > MaxMilliSeconds)
			return (double)MaxMilliSeconds;

		if (temp < MinMilliSeconds)
			return (double)MinMilliSeconds;

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

	static TimeSpan Interval(Double value, Int32 scale)
	{
		if (Double::IsNaN(value)) throw ArgumentException("Can not Be NaN");

		double tmp = value * scale;
		auto millis = tmp + (value >= 0 ? 0.5 : -0.5);
		if ((millis > Int64::MaxValue / TicksPerMillisecond) || (millis < Int64::MinValue / TicksPerMillisecond))
		{
			throw OverflowException("TimeSpan Too Long");
		}
		return TimeSpan((int64_t)millis * TicksPerMillisecond);
	}

	TimeSpan TimeSpan::FromMilliseconds(Double value)
	{
		return Interval(value, 1);
	}

	TimeSpan TimeSpan::FromSeconds(Double value)
	{
		return Interval(value, MillisPerSecond);
	}

	TimeSpan TimeSpan::FromMinutes(Double value)
	{
		return Interval(value, MillisPerMinute);
	}

	TimeSpan TimeSpan::FromHours(Double value)
	{
		return Interval(value, MillisPerHour);
	}

	TimeSpan TimeSpan::FromDays(Double value)
	{
		return Interval(value, MillisPerDay);
	}

	Int32 TimeSpan::CompareTo(const TimeSpan& value) const
	{
		if (ticks > value.ticks) return 1;
		if (ticks < value.ticks) return -1;
		return 0;
	}

	Boolean TimeSpan::Equals(const TimeSpan& span) const
	{
		return ticks == span.ticks;
	}

	Int32 TimeSpan::GetHashCode() const
	{
		return (int32_t)ticks ^ (int32_t)(ticks >> 32);
	}

	/////////////////////////////////////////////////////////////////////////
	// Implementation of DateTimeOffset

	const Int64 MaxOffset = TicksPerHour * 14;
	const Int64 MinOffset = -MaxOffset;

	static DateTime ValidateDate(DateTime dateTime, TimeSpan offset)
	{
		// The key validation is that both the UTC and clock times fit. The clock time is validated
		// by the DateTime constructor.
		if (!(offset.GetTicks() >= MinOffset && offset.GetTicks() <= MaxOffset))
		{
			throw ArgumentOutOfRangeException("offset", "Offset not validated.");
		}
		// This operation cannot overflow because offset should have already been validated to be within
		// 14 hours and the DateTime instance is more than that distance from the boundaries of Int64.
		Int64 utcTicks = dateTime.GetTicks() - offset.GetTicks();
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
		Int64 ticks = offset.GetTicks();
		if (ticks % TicksPerMinute != 0)
		{
			throw ArgumentException("Offset Precision", "offset");
		}
		if (ticks < MinOffset || ticks > MaxOffset)
		{
			throw ArgumentOutOfRangeException("offset", "Offset Out Of Range");
		}
		return (int16_t)(offset.GetTicks() / TicksPerMinute);
	}

	DateTimeOffset::DateTimeOffset(Int64 ticks, TimeSpan offset)
		: dateTime(ValidateDate(DateTime(ticks), offset)), offset(ValidateOffset(offset))
	{
	}

	DateTimeOffset::DateTimeOffset(DateTime dateTime, TimeSpan offset)
		: offset(ValidateOffset(offset)), dateTime(ValidateDate(dateTime, offset))
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

	DateTimeOffset::DateTimeOffset(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, TimeSpan offset)
		: offset(ValidateOffset(offset)), dateTime(ValidateDate(DateTime(year, month, day, hour, minute, second), offset))
	{
		
	}

	DateTimeOffset::DateTimeOffset(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, Int32 millisecond, TimeSpan offset)
		: offset(ValidateOffset(offset)), dateTime(ValidateDate(DateTime(year, month, day, hour, minute, second, millisecond), offset))
	{

	}
}