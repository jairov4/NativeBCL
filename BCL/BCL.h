#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>

#ifndef BCLAPI
#define BCLAPI
#endif

#ifndef BCLAPIOBJ
#define BCLAPIOBJ
#endif

namespace System
{
	struct Int16;
	struct UInt16;
	struct Int32;
	struct UInt32;
	struct Int64;
	struct UInt64;
	struct SByte;
	struct Byte;
	struct Boolean;
	struct String;
	struct DateTime;
	struct TimeSpan;
	struct Type;
	class Exception;


	template <typename T>
	using ref = std::shared_ptr < T > ;

	template<typename T, typename... TArgs>
	inline ref<T> new_ref(TArgs&&... args) { return std::make_shared<T>(std::forward<TArgs>(args)...); }

	BCLAPIOBJ struct Object
	{
	public:
		virtual String ToString() const;
		virtual Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Type final
	{
	private:
		const type_info& info;
	public:
		Type(const type_info& info);
		Type(const Type& info);

		String GetName() const;
		String ToString() const;
		Int32 GetHashCode() const;

		Boolean Equals(const Type& type) const;
		Type GetType() const;

		Boolean operator == (const Type& other) const;
	};

	BCLAPIOBJ struct String final
	{
	private:
		ref<std::wstring> value;

	public:
		String();
		String(const char* str);
		String(const wchar_t* str);
		String(const std::wstring& str);
		String(const String& str);
		String(String&& str);

		Int32 GetLength() const;

		Int32 CompareTo(const String& str) const;
		Boolean Equals(const String& str) const;

		Int32 GetHashCode() const;
		const String& ToString() const;
		Type GetType() const;

		operator std::wstring() const;
		Boolean operator==(const String& b) const;

		String operator+(const String& b) const;
		String operator+(const char* b) const;
		String operator+(const wchar_t* b) const;
	};

	BCLAPIOBJ struct SByte final
	{
	public:
		typedef std::int8_t sbyte;

		static const SByte MaxValue;
		static const SByte MinValue;

	private:
		sbyte value;
	public:
		SByte();
		SByte(sbyte value);
		SByte(const SByte& copy);

		operator sbyte() const;
		SByte& operator=(sbyte v);
		SByte& operator++();
		SByte& operator--();
		SByte operator++(int);
		SByte operator--(int);
		SByte& operator+=(const SByte& o);
		SByte& operator-=(const SByte& o);
		SByte& operator*=(const SByte& o);
		SByte& operator/=(const SByte& o);

		Int32 CompareTo(const SByte& obj) const;
		Boolean Equals(const SByte& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Byte final
	{
	public:
		typedef std::uint8_t byte;

		static const Byte MaxValue;
		static const Byte MinValue;

	private:
		byte value;
	public:
		Byte();
		Byte(byte value);
		Byte(const Byte& copy);

		operator byte() const;
		Byte& operator=(byte v);
		Byte& operator++();
		Byte& operator--();
		Byte operator++(int);
		Byte operator--(int);
		Byte& operator+=(const Byte& o);
		Byte& operator-=(const Byte& o);
		Byte& operator*=(const Byte& o);
		Byte& operator/=(const Byte& o);

		Int32 CompareTo(const Byte& obj) const;
		Boolean Equals(const Byte& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Int16 final
	{
	public:
		typedef std::int16_t int16;

		static const Int16 MaxValue;
		static const Int16 MinValue;

	private:
		int16 value;
	public:
		Int16();
		Int16(int16 value);
		Int16(const Int16& copy);

		operator int16() const;
		Int16& operator=(int16 v);
		Int16& operator++();
		Int16& operator--();
		Int16 operator++(int);
		Int16 operator--(int);
		Int16& operator+=(const Int16& o);
		Int16& operator-=(const Int16& o);
		Int16& operator*=(const Int16& o);
		Int16& operator/=(const Int16& o);

		Int32 CompareTo(const Int16& obj) const;
		Boolean Equals(const Int16& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct UInt16 final
	{
	public:
		typedef std::uint16_t uint16;

		static const UInt16 MaxValue;
		static const UInt16 MinValue;

	private:
		uint16 value;
	public:
		UInt16();
		UInt16(uint16 value);
		UInt16(const UInt16& copy);

		operator uint16() const;
		UInt16& operator=(uint16 v);
		UInt16& operator++();
		UInt16& operator--();
		UInt16 operator++(int);
		UInt16 operator--(int);
		UInt16& operator+=(const UInt16& o);
		UInt16& operator-=(const UInt16& o);
		UInt16& operator*=(const UInt16& o);
		UInt16& operator/=(const UInt16& o);

		Int32 CompareTo(const UInt16& obj) const;
		Boolean Equals(const UInt16& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Int32 final
	{
	public:
		typedef std::int32_t int32;

		static const Int32 MaxValue;
		static const Int32 MinValue;

	private:
		int32 value;
	public:
		Int32();
		Int32(int32 value);
		Int32(const Int32& copy);

		operator int32() const;
		Int32& operator= (int32 v);
		Int32& operator++();
		Int32& operator--();
		Int32 operator++(int);
		Int32 operator--(int);
		Int32& operator+=(const Int32& o);
		Int32& operator-=(const Int32& o);
		Int32& operator*=(const Int32& o);
		Int32& operator/=(const Int32& o);

		Int32 CompareTo(const Int32& obj) const;
		Boolean Equals(const Int32& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct UInt32 final
	{
	public:
		typedef std::uint32_t uint32;

		static const UInt32 MaxValue;
		static const UInt32 MinValue;
	private:
		uint32 value;
	public:
		UInt32();
		UInt32(uint32 value);
		UInt32(const UInt32& copy);

		operator uint32() const;
		UInt32& operator=(uint32 val);
		UInt32& operator++();
		UInt32& operator--();
		UInt32 operator++(int);
		UInt32 operator--(int);
		UInt32& operator+=(const UInt32& o);
		UInt32& operator-=(const UInt32& o);
		UInt32& operator*=(const UInt32& o);
		UInt32& operator/=(const UInt32& o);

		Int32 CompareTo(const UInt32& obj) const;
		Boolean Equals(const UInt32& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Int64 final
	{
	public:
		typedef std::int64_t int64;

		static const Int64 MaxValue;
		static const Int64 MinValue;

	private:
		int64 value;
	public:
		Int64();
		Int64(int64 value);
		Int64(const Int64& copy);

		operator int64() const;
		Int64& operator=(int64 val);
		Int64& operator++();
		Int64& operator--();
		Int64 operator++(int);
		Int64 operator--(int);
		Int64& operator+=(const Int64& o);
		Int64& operator-=(const Int64& o);
		Int64& operator*=(const Int64& o);
		Int64& operator/=(const Int64& o);

		Int32 CompareTo(const Int64& obj) const;
		Boolean Equals(const Int64& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct UInt64 final
	{
	public:
		typedef std::uint64_t uint64;

		static const UInt64 MaxValue;
		static const UInt64 MinValue;

	private:
		uint64 value;
	public:
		UInt64();
		UInt64(uint64 value);
		UInt64(const UInt64& copy);

		operator uint64() const;
		UInt64& operator=(uint64 val);
		UInt64& operator++();
		UInt64& operator--();
		UInt64 operator++(int);
		UInt64 operator--(int);
		UInt64& operator+=(const UInt64& o);
		UInt64& operator-=(const UInt64& o);
		UInt64& operator*=(const UInt64& o);
		UInt64& operator/=(const UInt64& o);

		Int32 CompareTo(const UInt64& obj) const;
		Boolean Equals(const UInt64& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Char final
	{
	public:
	private:
		char16_t value;
	public:
		Char();
		Char(char16_t value);

		operator char16_t() const;
		Char& operator=(char16_t val);

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Float final
	{
	private:
		float value;
	public:
		Float();
		Float(const Float& copy);
		Float(float value);

		static const Float MinValue;
		static const Float MaxValue;

		static const Float Epsilon;
		static const Float NegativeInfinity;
		static const Float PositiveInfinity;
		static const Float NaN;

		operator float() const;
		Float& operator=(float val);
		Float& operator+=(const Float& o);
		Float& operator-=(const Float& o);
		Float& operator*=(const Float& o);
		Float& operator/=(const Float& o);

		static Boolean IsNaN(Float d);
		static Boolean IsInfinity(Float d);

		Int32 CompareTo(const Float& obj) const;
		Boolean Equals(const Float& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Double final
	{
	private:
		double value;
	public:
		Double();
		Double(double_t value);
		Double(const Double& copy);

		static const Double MinValue;
		static const Double MaxValue;

		static const Double Epsilon;
		static const Double NegativeInfinity;
		static const Double PositiveInfinity;
		static const Double NaN;

		operator double_t() const;
		Double& operator=(double_t val);
		Double& operator+=(const Double& o);
		Double& operator-=(const Double& o);
		Double& operator*=(const Double& o);
		Double& operator/=(const Double& o);

		static Boolean IsNaN(Double d);
		static Boolean IsInfinity(Double d);

		Int32 CompareTo(const Double& obj) const;
		Boolean Equals(const Double& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Boolean final
	{
	private:
		bool value;
	public:
		Boolean();
		Boolean(bool value);
		Boolean(const Boolean& copy);

		operator bool() const;
		Boolean& operator=(bool val);

		Int32 CompareTo(const Boolean& obj) const;
		Boolean Equals(const Boolean& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ struct Decimal final
	{
	public:
		static const Decimal One;
		static const Decimal Zero;
		static const Decimal MinusOne;
		static const Decimal MaxValue;
		static const Decimal MinValue;
		static const Decimal NearNegativeZero;
		static const Decimal NearPositiveZero;
	private:
		// DO NOT change this order
		Int32 flags;
		Int32 hi;
		Int32 lo;
		Int32 mid;
	public:
		Decimal();
		Decimal(const Decimal& copy);
		Decimal(Int32 lo, Int32 mid, Int32 hi, Int32 flags);
		Decimal(Int32 lo, Int32 mid, Int32 hi, Boolean isNegative, Byte scale);
		Decimal(Int64 p, Byte point);
		Decimal(UInt64 p, Byte point);

		Int32 CompareTo(const Decimal& obj) const;
		Boolean Equals(const Decimal& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Type GetType() const;
	};

	BCLAPIOBJ enum class DateTimeKind : uint8_t
	{
		Unspecified = 0, Utc = 1, Local = 2
	};

	BCLAPIOBJ enum class DayOfWeek : uint8_t
	{
		Sunday = 0,
		Monday = 1,
		Tuesday = 2,
		Wednesday = 3,
		Thursday = 4,
		Friday = 5,
		Saturday = 6,
	};

	BCLAPIOBJ struct DateTime final
	{
	private:
		UInt64 value;

		Int64 GetInternalTicks() const;
		UInt64 GetInternalKind() const;

		Int32 GetDatePart(Int32 part) const;

		DateTime Add(Double value, Int32 scale) const;

		DateTime(UInt64 t);
		DateTime(Int64 ticks, DateTimeKind kind, Boolean isAmbiguousDst);

	public:
		explicit DateTime(Int64 ticks);
		DateTime(Int64 ticks, DateTimeKind kind);
		DateTime(Int32 year, Int32 month, Int32 day);
		DateTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second);
		DateTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, Int32 millisecond);
		DateTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, DateTimeKind kind);

		Boolean operator>(const DateTime& ts) const;
		Boolean operator<(const DateTime& ts) const;
		Boolean operator>=(const DateTime& ts) const;
		Boolean operator<=(const DateTime& ts) const;
		Boolean operator==(const DateTime& ts) const;
		Boolean operator!=(const DateTime& ts) const;

		static bool IsLeapYear(Int32 year);
		static Int32 DaysInMonth(Int32 year, Int32 month);
		static DateTime GetNow();
		static DateTime GetUtcNow();
		static DateTime GetToday();

		static const DateTime MinValue;
		static const DateTime MaxValue;

		DateTime operator+(const TimeSpan& value) const;
		DateTime operator-(const TimeSpan& other) const;

		DateTime AddTicks(Int64 value) const;
		DateTime AddYears(Int32 value) const;
		DateTime AddSeconds(Double value) const;
		DateTime AddMonths(Int32 value) const;
		DateTime AddMinutes(Double value) const;
		DateTime AddMilliseconds(Double value) const;
		DateTime AddHours(Double value) const;
		DateTime AddDays(Double value) const;
		DateTime Add(const TimeSpan& value) const;
		DateTime Subtract(const TimeSpan& value) const;

		Int32 GetDayOfYear() const;
		DayOfWeek GetDayOfWeek() const;
		Int32 GetDay() const;
		Int32 GetMonth() const;
		Int32 GetYear() const;
		Int32 GetMillisecond() const;
		Int32 GetSecond() const;
		Int32 GetMinute() const;
		Int32 GetHour() const;
		Int64 GetTicks() const;
		DateTime GetDate() const;

		DateTimeKind GetKind() const;

		Int32 CompareTo(const DateTime& value) const;
		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const DateTime& obj) const;
	};

	BCLAPIOBJ struct TimeSpan final
	{
	private:
		Int64 ticks;
	public:
		explicit TimeSpan(Int64 ticks);
		TimeSpan(Int32 hours, Int32 minutes, Int32 seconds);
		TimeSpan(Int32 days, Int32 hours, Int32 minutes, Int32 seconds, Int32 milliseconds);

		static const TimeSpan Zero;
		static const TimeSpan MaxValue;
		static const TimeSpan MinValue;

		static TimeSpan FromMilliseconds(Double value);
		static TimeSpan FromSeconds(Double value);
		static TimeSpan FromMinutes(Double value);
		static TimeSpan FromHours(Double value);
		static TimeSpan FromDays(Double value);

		Int32 GetDays() const;
		Int32 GetMilliseconds() const;
		Int32 GetSeconds() const;
		Int32 GetMinutes() const;
		Int32 GetHours() const;

		Int64 GetTicks() const;

		Double GetTotalDays() const;
		Double GetTotalHours() const;
		Double GetTotalSeconds() const;
		Double GetTotalMinutes() const;
		Double GetTotalMilliseconds() const;

		TimeSpan Duration() const;
		TimeSpan Negate() const;

		TimeSpan Add(const TimeSpan& ts) const;
		TimeSpan Subtract(const TimeSpan& ts) const;

		TimeSpan operator+(const TimeSpan& ts) const;
		TimeSpan operator-(const TimeSpan& ts) const;

		Boolean operator>(const TimeSpan& ts) const;
		Boolean operator<(const TimeSpan& ts) const;
		Boolean operator>=(const TimeSpan& ts) const;
		Boolean operator<=(const TimeSpan& ts) const;
		Boolean operator==(const TimeSpan& ts) const;
		Boolean operator!=(const TimeSpan& ts) const;

		Int32 CompareTo(const TimeSpan& value) const;
		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const TimeSpan& obj) const;
	};

	BCLAPIOBJ struct DateTimeOffset final
	{
	private:
		DateTime dateTime;
		Int16 offset;

	public:
		DateTimeOffset(Int64 ticks, TimeSpan offset);
		DateTimeOffset(DateTime value, TimeSpan offset);
		DateTimeOffset(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, TimeSpan offset);
		DateTimeOffset(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, Int32 millisecond, TimeSpan offset);

		static const DateTimeOffset MinValue;
		static const DateTimeOffset MaxValue;

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const DateTimeOffset& obj) const;
	};

	template<typename T>
	class Nullable final : public Object
	{
		T value;
		bool hasValue;

	public:

		bool HasValue() const
		{
			return hasValue;
		}

		T GetValueOrDefault() const
		{
			return value;
		}

		void SetValue(T v)
		{
			value = v;
			hasValue = true;
		}

		void SetNull()
		{
			hasValue = false;
		}

		Boolean Equals(const Nullable<T> obj) const
		{
			return hasValue == obj.hasValue ? (hasValue ? value == obj.value : true) : false;
		}
	};

	BCLAPIOBJ class Exception : public Object
	{
	private:
		ref<Exception> innerException;
		String message;

	public:
		Exception();
		explicit Exception(String message);
		Exception(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ class NotImplementedException : public Exception
	{
	public:
		NotImplementedException();
		explicit NotImplementedException(String message);
		NotImplementedException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ class InvalidOperationException : public Exception
	{
	public:
		InvalidOperationException();
		explicit InvalidOperationException(String message);
		InvalidOperationException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ class SystemException : public Exception
	{
	public:
		SystemException();
		explicit SystemException(String message);
		SystemException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ class OverflowException : public SystemException
	{
	public:
		OverflowException();
		explicit OverflowException(String message);
		OverflowException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ class ArgumentException : public SystemException
	{
	private:
		String paramName;
	public:
		ArgumentException();
		explicit ArgumentException(String message);
		ArgumentException(String message, String paramName);
		ArgumentException(String message, String paramName, ref<Exception> innerException);
		ArgumentException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ class ArgumentOutOfRangeException : public ArgumentException
	{
	public:
		ArgumentOutOfRangeException();
		explicit ArgumentOutOfRangeException(String paramName);
		ArgumentOutOfRangeException(String paramName, String message);
		ArgumentOutOfRangeException(String message, ref<Exception> innerException);
	};

	namespace Collections
	{
		template <class TEnumerator, class TIterator, class T>
		struct StlEnumerator
		{
		protected:
			TIterator i, end;
		public:
			StlEnumerator(TIterator begin, TIterator end) : i(begin), end(end) {}

			TEnumerator& operator++ () { ++i; return (TEnumerator&)(*this); }
			Boolean operator== (const TEnumerator& b) const { return i == b.i; }
			Boolean operator!= (const TEnumerator& b) const { return i != b.i; }

			Boolean MoveNext()
			{
				if (i == end) return false;
				++i;
				return true;
			}
		};

		template<class T>
		class List : public Object
		{
		private:
			typedef std::vector<T> TVector;
			typedef typename TVector::const_iterator TVectorIterator;
			TVector storage;

			struct ListEnumerator final : public StlEnumerator < ListEnumerator, TVectorIterator, T >
			{
			public:
				ListEnumerator(TVectorIterator begin, TVectorIterator end) : StlEnumerator(begin, end) {}
				const T& GetCurrent() const { return *i; }
				const T& operator* () const { return GetCurrent(); }
			};

		public:

			List()
			{
			}

			explicit List(int capacity) : storage(capacity)
			{
			}

			List(List<T>& cp) : storage(cp.storage)
			{
			}

			virtual ListEnumerator begin() const
			{
				return ListEnumerator(storage.begin(), storage.end());
			}

			virtual ListEnumerator end() const
			{
				return ListEnumerator(storage.end(), storage.end());
			}

			virtual void Add(const T& item)
			{
				storage.push_back(item);
			}

			virtual void Add(T&& item)
			{
				storage.push_back(item);
			}

			virtual void Clear()
			{
				storage.clear();
			}

			virtual void Remove(const T& value)
			{
				for (std::int32_t i = 0; i < (std::int32_t)storage.size(); i++)
				{
					if (storage[i] == value)
					{
						RemoveAt(i);
						i--;
					}
				}
			}

			virtual Int32 GetCapacity() const
			{
				return (std::int32_t)storage.capacity();
			}

			virtual Int32 GetCount() const
			{
				return (std::int32_t)storage.size();
			}

			virtual Boolean Contains(T value) const
			{
				return std::find(storage.begin(), storage.end(), value) != storage.end();
			}

			virtual const T& operator[] (Int32 index) const
			{
				return storage[index];
			}

			virtual const T& GetAt(Int32 index) const
			{
				return storage[index];
			}

			virtual Int32 IndexOf(const T& value) const
			{
				auto it = std::find(storage.begin(), storage.end(), value);
				if (it == storage.end()) return -1;
				return (std::int32_t)(it - storage.begin());
			}

			virtual void SetAt(Int32 index, const T& value)
			{
				storage[index] = value;
			}

			virtual void SetAt(Int32 index, T&& value)
			{
				storage[index] = value;
			}

			virtual void Insert(Int32 index, const T& value)
			{
				storage.insert(storage.begin() + index, value);
			}

			virtual void Insert(Int32 index, T&& value)
			{
				storage.insert(storage.begin() + index, value);
			}

			virtual void RemoveAt(Int32 index)
			{
				std::copy(storage.begin() + index + 1, storage.end(), storage.begin() + index);
				storage.pop_back();
			}
		};

		template<class TKey, class TValue>
		struct KeyValuePair final : public Object
		{
		private:
			TKey Key;
			TValue Value;

		public:
			KeyValuePair(TKey k, TValue v) : Key(k), Value(v) {}

			const TKey& GetKey() const { return Key; }
			const TValue& GetValue() const { return Value; }

			Boolean Equals(const KeyValuePair<TKey, TValue>& obj) const
			{
				return Key == obj.Key && Value == obj.Value;
			}
		};

		template<class TKey, class TValue>
		class Dictionary : public Object
		{
		private:

			class KeyHasher
			{
			public:
				size_t operator()(const TKey& obj) const
				{
					return obj.GetHashCode();
				}
			};

			typedef std::unordered_map<TKey, TValue, KeyHasher> Map;
			typedef typename Map::const_iterator TMapIterator;
			typedef KeyValuePair<TKey, TValue> TKeyValuePair;

			class KeysCollection final : public Object
			{
			private:
				ref<Map> entries;

				struct KeysCollectionEnumerator final : public StlEnumerator < KeysCollectionEnumerator, TMapIterator, TKey >
				{
				public:
					KeysCollectionEnumerator(TMapIterator begin, TMapIterator end) : StlEnumerator(begin, end) {}
					const TKey& GetCurrent() const { return i->first; }
					const TKey& operator* () const { return GetCurrent(); }
				};

			public:

				KeysCollection(ref<Map> entries) : entries(entries) { }

				KeysCollectionEnumerator begin() const
				{
					return KeyCollectionEnumerator(entries->begin(), entries->end());
				}

				KeysCollectionEnumerator end() const
				{
					return KeyCollectionEnumerator(entries->end(), entries->end());
				}

				Boolean Contains(const TKey& key) const
				{
					return entries->find(key) != entries->end();
				}

				Int32 GetCount()
				{
					return (std::int32_t)entries->size();
				}
			};

			class ValuesCollection final : public Object
			{
			private:
				ref<Map> entries;

				struct ValuesCollectionEnumerator final : public StlEnumerator < ValuesCollectionEnumerator, TMapIterator, TValue >
				{
				public:
					ValuesCollectionEnumerator(TMapIterator begin, TMapIterator end) : StlEnumerator(begin, end) {}
					const TValue& GetCurrent() const { return i->second; }
					const TValue& operator* () const { return GetCurrent(); }
				};

			public:
				ValuesCollection(ref<Map> entries) : entries(entries)
				{
				}

				ValuesCollectionEnumerator begin() const
				{
					return ValuesCollectionEnumerator(entries->begin(), entries->end());
				}

				ValuesCollectionEnumerator end() const
				{
					return ValuesCollectionEnumerator(entries->end(), entries->end());
				}

				Boolean Contains(const TValue& key) const
				{
					for (auto& i : *entries)
					{
						if (i.second == key) return true;
					}
					return false;
				}

				Int32 GetCount() const { return (std::int32_t)entries->size(); }
			};

			struct DictionaryEnumerator final : public StlEnumerator < DictionaryEnumerator, TMapIterator, TKeyValuePair >
			{
			public:
				DictionaryEnumerator(TMapIterator begin, TMapIterator end) : StlEnumerator(begin, end) {}
				TKeyValuePair GetCurrent() const { return TKeyValuePair(i->first, i->second); }
				TKeyValuePair operator* () const { return GetCurrent(); }
			};

			ref<Map> entries;
			ref<KeysCollection> keySet;
			ref<ValuesCollection> valuesCollection;

		public:

			Dictionary()
			{
				entries = new_ref<Map>();
				keySet = new_ref<KeysCollection>(entries);
				valuesCollection = new_ref<ValuesCollection>(entries);
			}

			Dictionary(const Dictionary& copy)
			{
				entries = new_ref<Map>(copy.entries.get());
				keySet = new_ref<KeysCollection>(entries);
				valuesCollection = new_ref<ValuesCollection>(entries);
			}

			Dictionary(Dictionary&& rval)
			{
				entries = rval.entries;
				keySet = rval.keySet;
				valuesCollection = rval.valuesCollection;
			}

			virtual TValue operator[](const TKey& key) const
			{
				return (*entries)[key];
			}

			virtual ref<KeysCollection> GetKeys() const
			{
				return keySet;
			}

			virtual ref<ValuesCollection> GetValues() const
			{
				return valuesCollection;
			}

			virtual void Add(const TKey& key, const TValue& value)
			{
				(*entries)[key] = value;
			}

			virtual void Add(const TKey& key, TValue&& value)
			{
				(*entries)[key] = value;
			}

			virtual void Add(TKey&& key, TValue&& value)
			{
				(*entries)[key] = value;
			}

			virtual void Remove(const TKey& key)
			{
				entries->erase(key);
			}

			virtual DictionaryEnumerator begin() const
			{
				return DictionaryEnumerator(entries->begin(), entries->end());
			}

			virtual DictionaryEnumerator end() const
			{
				return DictionaryEnumerator(entries->end(), entries->end());
			}

			virtual Boolean ContainsKey(const TKey& key) const
			{
				return GetKeys()->Contains(key);
			}

			virtual Boolean TryGetValue(const TKey& key, TValue* out_value) const
			{
				auto r = entries->find(key);
				if (r == entries->end()) return false;
				*out_value = r->second;
				return true;
			}

			virtual Int32 GetCount() const
			{
				return (std::int32_t)entries->size();
			}

			virtual Boolean Contains(const KeyValuePair<TKey, TValue>& pair) const
			{
				for (const auto& pairIt : *entries)
				{
					if (pairIt.first == pair.GetKey() && pairIt.second == pair.GetValue())
					{
						return true;
					}
				}
				return false;
			}
		};
	}

	namespace IO
	{
		BCLAPIOBJ enum class SeekOrigin : std::int8_t
		{
			Begin = 0,
			Current = 1,
			End = 2
		};


		BCLAPIOBJ class IStream : public Object
		{
		public:
			virtual Boolean CanRead() = 0;
			virtual Boolean CanWrite() = 0;
			virtual Boolean CanSeek() = 0;
			virtual Boolean CanTimeout() = 0;
			virtual Int64 GetLength() = 0;
			virtual Int64 GetPosition() = 0;
			virtual Int64 GetTimeout() = 0;
			virtual void SetTimeout(Int64 timeout) = 0;
			virtual Int32 ReadByte() = 0;
			virtual void WriteByte(Byte data) = 0;
			virtual void Read(Byte* buffer, Int32 index, Int32 count) = 0;
			virtual void Write(Byte* buffer, Int32 index, Int32 count) = 0;
			virtual Int64 Seek(Int64 offset, SeekOrigin origin) = 0;
		};

		BCLAPIOBJ class ITextReader : public Object
		{
		public:
			virtual void Close() = 0;
			virtual Int32 Peek() = 0;
			virtual Int32 Read() = 0;
			virtual Int32 Read(Char* buffer, Int32 index, Int32 count) = 0;
			virtual String ReadToEnd() = 0;
			virtual String ReadLine() = 0;
		};

		BCLAPIOBJ class StreamReader : public virtual ITextReader
		{

		};
	}

	BCLAPIOBJ class Console
	{
	public:
		static ref<IO::ITextReader> GetIn()
		{
			throw NotImplementedException();
		}
	};

}