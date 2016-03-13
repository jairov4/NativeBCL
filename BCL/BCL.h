#pragma once

#include <stdint.h>
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
	struct Object;
	struct Int16;
	struct UInt16;
	struct Int32;
	struct UInt32;
	struct Int64;
	struct UInt64;
	struct SByte;
	struct Byte;
	struct String;
	struct String;
	struct Boolean;
	struct Exception;
	
	template <typename T>
	using ref = std::shared_ptr<T>;

	template<typename T, typename... TArgs>
	inline ref<T> new_ref(TArgs&&... args) { return std::make_shared<T>(std::forward<TArgs>(args)...); }

	struct Object
	{
	public:
		virtual ~Object() = default;

		virtual String ToString() = 0;
		virtual Int32 GetHashCode() = 0;
		virtual Boolean Equals(Object& obj) = 0;
	};

	struct String final : Object
	{
	private:
		ref<std::u16string> value;

	public:
		String();
		String(const String& str);
		String(String&& str);
		String(const std::u16string& str);

		Int32 GetLength();
		Int32 CompareTo(String& b);
		Boolean Equals(String& b);

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;

		Boolean operator==(const String& b) const;
	};

	struct SByte final : Object
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

		Int32 CompareTo(const Object& obj);
		Int32 CompareTo(const SByte& obj);
		Boolean Equals(const SByte& obj);

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct Byte final : public Object
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const Byte& obj) const;
		Boolean Equals(const Byte& obj) const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct Int16 final : public Object
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const Int16& obj) const;
		Boolean Equals(const Int16& obj) const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct UInt16 final : public Object
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const UInt16& obj) const;
		Boolean Equals(const UInt16& obj) const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct Int32 final : public Object
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const Int32& obj) const;
		Boolean Equals(const Int32& obj) const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct UInt32 final : public Object
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const UInt32& obj) const;
		Boolean Equals(const UInt32& obj) const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct Int64 final : public Object
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const Int64& obj) const;
		Boolean Equals(const Int64& obj) const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct UInt64 final : public Object
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const UInt64& obj) const;
		Boolean Equals(const UInt64& obj) const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct Char final : public Object
	{
		char16_t value;
	public:
		Char();
		Char(char16_t value);

		operator char16_t() const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct Float final : public Object
	{
		float value;
	public:
		Float();
		Float(float value);

		operator float() const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct Double final : public Object
	{
		double value;
	public:
		Double();
		Double(double value);
		Double(const double& value);

		operator double() const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct Boolean final : public Object
	{
		bool value;
	public:
		Boolean();
		Boolean(bool value);
		Boolean(const Boolean& copy);

		operator bool() const;

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const Boolean& obj) const;
		Boolean Equals(const Boolean& obj) const;

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	struct Decimal final : public Object
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
		Decimal(Decimal& copy);
		Decimal(Int32 lo, Int32 mid, Int32 hi, Int32 flags);
		Decimal(Int32 lo, Int32 mid, Int32 hi, Boolean isNegative, Byte scale);
		Decimal::Decimal(Int64 p, Byte point);
		Decimal::Decimal(UInt64 p, Byte point);

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const Boolean& obj) const;
		Boolean Equals(const Decimal& obj) const;

		static Decimal Add(const Decimal& a, const Decimal& b);

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	BCLAPIOBJ enum struct DateTimeKind : uint8_t
	{
		Unspecified = 0, Utc = 1, Local = 2
	};

	BCLAPIOBJ enum struct DayOfWeek : uint8_t
	{
		Sunday = 0,
		Monday = 1,
		Tuesday = 2,
		Wednesday = 3,
		Thursday = 4,
		Friday = 5,
		Saturday = 6,
	};

	BCLAPIOBJ struct DateTime final : Object
	{
	private:
		UInt64 value;

		Int64 GetInternalTicks();
		UInt64 GetInternalKind();

		Int32 GetDatePart(Int32 part);

		DateTime Add(Double value, Int32 scale);

		DateTime(UInt64 t);
		DateTime(Int64 ticks, DateTimeKind kind, Boolean isAmbiguousDst);

	public:
		explicit DateTime(Int64 ticks);
		DateTime(Int64 ticks, DateTimeKind kind);
		DateTime(Int32 year, Int32 month, Int32 day);
		DateTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second);
		DateTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, Int32 millisecond);
		DateTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, DateTimeKind kind);

		Boolean operator>(const DateTime& ts);
		Boolean operator<(const DateTime& ts);
		Boolean operator>=(const DateTime& ts);
		Boolean operator<=(const DateTime& ts);
		Boolean operator==(const DateTime& ts);
		Boolean operator!=(const DateTime& ts);

		static bool IsLeapYear(Int32 year);
		static Int32 DaysInMonth(Int32 year, Int32 month);
		static DateTime GetNow();
		static DateTime GetUtcNow();
		static DateTime GetToday();

		static const DateTime MinValue;
		static const DateTime MaxValue;

		DateTime operator+(const TimeSpan& value);
		DateTime operator-(const TimeSpan& other);

		DateTime AddTicks(Int64 value);
		DateTime AddYears(Int32 value);
		DateTime AddSeconds(Double value);
		DateTime AddMonths(Int32 value);
		DateTime AddMinutes(Double value);
		DateTime AddMilliseconds(Double value);
		DateTime AddHours(Double value);
		DateTime AddDays(Double value);
		DateTime Add(const TimeSpan& value);
		DateTime Subtract(const TimeSpan& value);

		Int32 GetDayOfYear();
		DayOfWeek GetDayOfWeek();
		Int32 GetDay();
		Int32 GetMonth();
		Int32 GetYear();
		Int32 GetMillisecond();
		Int32 GetSecond();
		Int32 GetMinute();
		Int32 GetHour();
		Int64 GetTicks();
		DateTime GetDate();

		DateTimeKind GetKind();

		Int32 CompareTo(const DateTime& value);
		Boolean Equals(const DateTime& obj);

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	BCLAPIOBJ struct TimeSpan final : Object
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

		Int32 GetDays();
		Int32 GetMilliseconds();
		Int32 GetSeconds();
		Int32 GetMinutes();
		Int32 GetHours();

		Int64 GetTicks();

		Double GetTotalDays();
		Double GetTotalHours();
		Double GetTotalSeconds();
		Double GetTotalMinutes();
		Double GetTotalMilliseconds();

		TimeSpan Duration();
		TimeSpan Negate();

		TimeSpan Add(const TimeSpan& ts);
		TimeSpan Subtract(const TimeSpan& ts);

		TimeSpan operator+(const TimeSpan& ts);
		TimeSpan operator-(const TimeSpan& ts);

		Boolean operator>(const TimeSpan& ts);
		Boolean operator<(const TimeSpan& ts);
		Boolean operator>=(const TimeSpan& ts);
		Boolean operator<=(const TimeSpan& ts);
		Boolean operator==(const TimeSpan& ts);
		Boolean operator!=(const TimeSpan& ts);

		Int32 CompareTo(const TimeSpan& value);
		Boolean Equals(const TimeSpan& obj);

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	BCLAPIOBJ struct DateTimeOffset final : Object
	{
	private:
		DateTime dateTime;
		Int16 offset;

		DateTime GetClockDateTime();

		DateTimeOffset(DateTime value, Int16 offset);

	public:
		DateTimeOffset(Int64 ticks, TimeSpan offset);
		DateTimeOffset(DateTime value, TimeSpan offset);
		DateTimeOffset(DateTime value);
		DateTimeOffset(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, TimeSpan offset);
		DateTimeOffset(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, Int32 millisecond, TimeSpan offset);

		static const DateTimeOffset MinValue;
		static const DateTimeOffset MaxValue;

		static DateTimeOffset GetNow();
		static DateTimeOffset GetUtcNow();

		DateTimeOffset AddTicks(Int64 value);
		DateTimeOffset AddYears(Int32 value);
		DateTimeOffset AddSeconds(Double value);
		DateTimeOffset AddMonths(Int32 value);
		DateTimeOffset AddMinutes(Double value);
		DateTimeOffset AddMilliseconds(Double value);
		DateTimeOffset AddHours(Double value);
		DateTimeOffset AddDays(Double value);
		DateTimeOffset Add(const TimeSpan& value);
		DateTimeOffset Subtract(const TimeSpan& value);

		Int32 GetDayOfYear();
		DayOfWeek GetDayOfWeek();
		Int32 GetDay();
		Int32 GetMonth();
		Int32 GetYear();
		Int32 GetMillisecond();
		Int32 GetSecond();
		Int32 GetMinute();
		Int32 GetHour();
		Int64 GetTicks();
		Int64 GetUtcTicks();
		DateTime GetDate();
		TimeSpan GetOffset();
		DateTime GetDateTime();
		DateTime GetUtcDateTime();

		Boolean Equals(const DateTimeOffset& obj);

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	template<typename T>
	struct Nullable final : Object
	{
	private:
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

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	BCLAPIOBJ struct Exception : Object
	{
	private:
		ref<Exception> innerException;
		String message;

	public:
		Exception();
		explicit Exception(String message);
		Exception(String message, ref<Exception> innerException);

		Int32 GetHashCode() override;
		String ToString() override;
		Boolean Equals(Object& obj) override;
	};

	BCLAPIOBJ struct NotImplementedException : public Exception
	{
	public:
		NotImplementedException();
		explicit NotImplementedException(String message);
		NotImplementedException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ struct InvalidOperationException : public Exception
	{
	public:
		InvalidOperationException();
		explicit InvalidOperationException(String message);
		InvalidOperationException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ struct SystemException : public Exception
	{
	public:
		SystemException();
		explicit SystemException(String message);
		SystemException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ struct OverflowException : public SystemException
	{
	public:
		OverflowException();
		explicit OverflowException(String message);
		OverflowException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ struct ArgumentException : public SystemException
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

	BCLAPIOBJ struct ArgumentOutOfRangeException : public ArgumentException
	{
	public:
		ArgumentOutOfRangeException();
		explicit ArgumentOutOfRangeException(String paramName);
		ArgumentOutOfRangeException(String paramName, String message);
		ArgumentOutOfRangeException(String message, ref<Exception> innerException);
	};

	namespace Collections
	{
		struct IEnumerator : public Object
		{
		public:
			virtual Boolean MoveNext() = 0;
			virtual Boolean HasNext() = 0;
		};

		template<typename T>
		struct IGenericEnumerator : public IEnumerator
		{
		public:
			virtual T GetCurrent() = 0;
		};

		struct IEnumerable : public Object
		{
		public:
			virtual ref<IEnumerator> GetEnumerator() = 0;
		};

		template<struct T>
		struct IGenericEnumerable : public IEnumerable
		{
		public:
			virtual ref<IGenericEnumerator<T>> GetGenericEnumerator() = 0;
		};

		struct IReadOnlyCollection : public IEnumerable
		{
		public:
			virtual Int32 GetCount() = 0;
		};

		template<struct T>
		struct IGenericReadOnlyCollection : public IReadOnlyCollection, public IGenericEnumerable<T>
		{
		public:
			virtual Boolean Contains(T item) = 0;
		};

		struct ICollection : public IReadOnlyCollection
		{
		public:
			virtual void Clear() = 0;
		};

		template<struct T>
		struct IGenericCollection : public IGenericReadOnlyCollection<T>, public ICollection
		{
		public:
			virtual void Add(const T& item) = 0;
			virtual void Add(T&& item) = 0;
			virtual void Remove(T item) = 0;
		};

		template<struct T>
		struct IGenericIReadOnlyList : public IGenericReadOnlyCollection<T>
		{
			virtual T operator[] (Int32 index) = 0;
			virtual Int32 IndexOf(T item) = 0;
		};

		struct IList : public ICollection
		{
		public:
			virtual void RemoveAt(Int32 index) = 0;
		};

		template<struct T>
		struct IGenericList : public IGenericIReadOnlyList<T>, public IGenericCollection<T>, public IList
		{
		public:
			virtual void SetAt(Int32 index, T item) = 0;
			virtual void Insert(Int32 index, T item) = 0;
		};

		template<struct T>
		struct List : public IGenericList<T>
		{
		private:
			typedef std::vector<T> TVector;
			typedef typename TVector::iterator TVectorIterator;
			TVector storage;

			struct ListEnumerator final : public IGenericEnumerator<T>
			{
				TVectorIterator begin, end;

			public:
				explicit ListEnumerator(TVectorIterator begin, TVectorIterator end)
				{
					this->begin = begin;
					this->end = end;
				}

				Boolean MoveNext() override
				{
					++begin;
					return HasNext();
				}

				T GetCurrent() override
				{
					return *begin;
				}

				Boolean HasNext() override
				{
					return begin != end;
				}
			};

		public:

			List() = default;

			explicit List(int capacity) : storage(capacity)
			{
			}

			List(List<T>& cp) : storage(cp.storage)
			{
			}

			virtual void Add(const T& item) override
			{
				storage.push_back(item);
			}

			virtual void Add(T&& item) override
			{
				storage.push_back(std::forward<T>(item));
			}

			virtual void Clear() override
			{
				storage.clear();
			}

			virtual void Remove(T value) override
			{
				for (auto i = 0; i < storage.size(); i++)
				{
					if (storage[i] == value)
					{
						RemoveAt(i);
						i--;
					}
				}
			}

			virtual Int32 GetCapacity()
			{
				return int32_t(storage.capacity());
			}

			virtual Int32 GetCount() override
			{
				return int32_t(storage.size());
			}

			virtual Boolean Contains(T value) override
			{
				return std::find(storage.begin(), storage.end(), value) != storage.end();
			}

			virtual T operator[] (Int32 index) override
			{
				return storage[index];
			}

			virtual Int32 IndexOf(T value) override
			{
				auto it = std::find(storage.begin(), storage.end(), value);
				if (it == storage.end()) return -1;
				return int32_t(it - storage.begin());
			}

			virtual void SetAt(Int32 index, T value) override
			{
				storage[index] = value;
			}

			virtual void Insert(Int32 index, T value) override
			{
				storage.insert(storage.begin() + index, value);
			}

			virtual void RemoveAt(Int32 index) override
			{
				std::copy(storage.begin() + index + 1, storage.end(), storage.begin() + index);
				storage.pop_back();
			}

			ref<IGenericEnumerator<T>> GetGenericEnumerator() override
			{
				return new_ref<ListEnumerator>(storage.begin(), storage.end());
			}

			ref<IEnumerator> GetEnumerator() override
			{
				return new_ref<ListEnumerator>(storage.begin(), storage.end());
			}
		};

		template<struct TKey, struct TValue>
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

		template<struct TKey, struct TValue>
		struct Dictionary : public Object
		{
		private:

			struct KeyHasher
			{
			public:
				size_t operator()(const TKey& obj) const
				{
					return obj.GetHashCode();
				}
			};

			typedef std::unordered_map<TKey, TValue, KeyHasher> Map;
			typedef typename Map::iterator TMapIterator;
			typedef KeyValuePair<TKey, TValue> TKeyValuePair;

			struct KeysCollection final : public Object
			{
			private:
				ref<Map> entries;

				struct KeysCollectionEnumerator final : public IGenericEnumerator<TKey>
				{
					TMapIterator begin, end;

				public:
					KeysCollectionEnumerator(TMapIterator begin, TMapIterator end)
					{
						this->begin = begin;
						this->end = end;
					}

					Boolean MoveNext() override
					{
						++begin;
						return begin != end;
					}

					TKey& GetCurrent() override
					{
						return begin->first;
					}
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
					return std::int32_t(entries->size());
				}
			};

			struct ValuesCollection final : public Object
			{
			private:
				ref<Map> entries;

				struct ValuesCollectionEnumerator final : public IGenericEnumerator<TValue>
				{
					TMapIterator begin, end;

				public:
					ValuesCollectionEnumerator(TMapIterator begin, TMapIterator end)
					{
						this->begin = begin;
						this->end = end;
					}

					Boolean MoveNext() override
					{
						++begin;
						return begin != end;
					}

					TValue& GetCurrent() override
					{
						return begin->second;
					}
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

				Int32 GetCount() const { return int32_t(entries->size()); }
			};

			struct DictionaryEnumerator final : public IGenericEnumerator<KeyValuePair<TKey, TValue>>
			{
				TMapIterator begin, end;

			public:
				DictionaryEnumerator(TMapIterator begin, TMapIterator end)
				{
					this->begin = begin;
					this->end = end;
				}

				Boolean MoveNext() override
				{
					++begin;
					return begin != end;
				}

				KeyValuePair<TKey, TValue> GetCurrent() override
				{
					return KeyValuePair<TKey, TValue>(begin->first, begin->second);
				}
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
		BCLAPIOBJ enum struct SeekOrigin : std::int8_t
		{
			Begin = 0,
			Current = 1,
			End = 2
		};


		BCLAPIOBJ struct IStream : public Object
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

		BCLAPIOBJ struct ITextReader : public Object
		{
		public:
			virtual void Close() = 0;
			virtual Int32 Peek() = 0;
			virtual Int32 Read() = 0;
			virtual Int32 Read(Char* buffer, Int32 index, Int32 count) = 0;
			virtual String ReadToEnd() = 0;
			virtual String ReadLine() = 0;
		};

		BCLAPIOBJ struct StreamReader : public virtual ITextReader
		{

		};
	}

	BCLAPIOBJ struct Console
	{
	public:
		static ref<IO::ITextReader> GetIn()
		{
			throw NotImplementedException();
		}
	};

}