#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>

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
	class String;
	class Exception;


	template <typename T>
	using ref = std::shared_ptr < T > ;

	template<typename T, typename... TArgs>
	inline ref<T> new_ref(TArgs&&... args) { return std::make_shared<T>(std::forward<TArgs>(args)...); }

	struct Object
	{
	public:
		virtual String ToString() const;
		virtual Int32 GetHashCode() const;
	};

	class String final : public Object
	{
		std::wstring value;

	public:
		String();
		String(const char* str);
		String(const wchar_t* str);
		String(const String& str);

		Int32 GetLength() const;
		operator std::wstring() const;

		Int32 GetHashCode() const override;
		String ToString() const override;

		Boolean operator==(const String& b) const;
	};

	struct SByte final
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

		Int32 CompareTo(const SByte& obj) const;
		Boolean Equals(const SByte& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct Byte final
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

		Int32 CompareTo(const Byte& obj) const;
		Boolean Equals(const Byte& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct Int16 final
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const Int16& obj) const;
		Boolean Equals(const Int16& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct UInt16 final
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const UInt16& obj) const;
		Boolean Equals(const UInt16& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct Int32 final
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

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct UInt32 final
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const UInt32& obj) const;
		Boolean Equals(const UInt32& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct Int64 final
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const Int64& obj) const;
		Boolean Equals(const Int64& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct UInt64 final
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const UInt64& obj) const;
		Boolean Equals(const UInt64& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct Char final
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
		Boolean Equals(const Object& obj) const;
	};

	struct Float final
	{
	private:
		float value;
	public:
		Float();
		Float(float value);

		operator float() const;
		Float& operator=(float val);

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct Double final
	{
	private:
		double value;
	public:
		Double();
		Double(double value);
		Double(const double& value);

		operator double() const;
		Double& operator=(double val);

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct Boolean final
	{
	private:
		bool value;
	public:
		Boolean();
		Boolean(bool value);
		Boolean(const Boolean& copy);

		operator bool() const;
		Boolean& operator=(bool val);

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const Boolean& obj) const;
		Boolean Equals(const Boolean& obj) const;

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	struct Decimal final
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

		String ToString() const;
		Int32 GetHashCode() const;
		Boolean Equals(const Object& obj) const;
	};

	class DateTime final : public Object
	{
	public:
		// Number of 100ns ticks per time unit
		const long TicksPerMillisecond = 10000;
		const long TicksPerSecond = TicksPerMillisecond * 1000;
		const long TicksPerMinute = TicksPerSecond * 60;
		const long TicksPerHour = TicksPerMinute * 60;
		const long TicksPerDay = TicksPerHour * 24;

		// Number of milliseconds per time unit
		const int MillisPerSecond = 1000;
		const int MillisPerMinute = MillisPerSecond * 60;
		const int MillisPerHour = MillisPerMinute * 60;
		const int MillisPerDay = MillisPerHour * 24;

		// Number of days in a non-leap year
		const int DaysPerYear = 365;
		// Number of days in 4 years
		const int DaysPer4Years = DaysPerYear * 4 + 1;       // 1461
		// Number of days in 100 years
		const int DaysPer100Years = DaysPer4Years * 25 - 1;  // 36524
		// Number of days in 400 years
		const int DaysPer400Years = DaysPer100Years * 4 + 1; // 146097

		// Number of days from 1/1/0001 to 12/31/1600
		const int DaysTo1601 = DaysPer400Years * 4;          // 584388
		// Number of days from 1/1/0001 to 12/30/1899
		const int DaysTo1899 = DaysPer400Years * 4 + DaysPer100Years * 3 - 367;
		// Number of days from 1/1/0001 to 12/31/9999
		const int DaysTo10000 = DaysPer400Years * 25 - 366;  // 3652059

	private:
		Int64 value;
	public:
		DateTime();
		DateTime(Int64 value);

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const DateTime& obj) const;
	};

	class TimeSpan final : public Object
	{
		Int32 ticks;

	public:
		TimeSpan();
		TimeSpan(DateTime value, TimeSpan offset);

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const TimeSpan& obj) const;
	};

	class DateTimeOffset final : public Object
	{
		DateTime dateTime;
		TimeSpan offset;

	public:
		DateTimeOffset();
		DateTimeOffset(DateTime value, TimeSpan offset);

		String ToString() const override;
		Int32 GetHashCode() const override;
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

	class Exception : public Object
	{
	private:
		ref<Exception> innerException;
		String message;

	public:
		Exception();
		Exception(String message);
		Exception(String message, ref<Exception> innerException);
	};

	class NotImplementedException : public Exception
	{
	public:
		NotImplementedException();
		NotImplementedException(String message);
		NotImplementedException(String message, ref<Exception> innerException);
	};

	class InvalidOperationException : public Exception
	{
	public:
		InvalidOperationException();
		InvalidOperationException(String message);
		InvalidOperationException(String message, ref<Exception> innerException);
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

			List(int capacity) : storage(capacity)
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
				for (int i = 0; i < storage.size(); i++)
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
				return (int)storage.capacity();
			}

			virtual Int32 GetCount() const
			{
				return (int)storage.size();
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
				return (int)(it - storage.begin());
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
					return (int)entries->size();
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

				Int32 GetCount() const { return (int)entries->size(); }
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
				return (int)entries->size();
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
		enum class SeekOrigin : std::int8_t
		{
			Begin = 0,
			Current = 1,
			End = 2
		};

		class IStream : public Object
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

		class ITextReader : public Object
		{
		public:
			virtual void Close() = 0;
			virtual Int32 Peek() = 0;
			virtual Int32 Read() = 0;
			virtual Int32 Read(Char* buffer, Int32 index, Int32 count) = 0;
			virtual String ReadToEnd() = 0;
			virtual String ReadLine() = 0;
		};

		class StreamReader : public virtual ITextReader
		{

		};
	}

	class Console
	{
	public:
		static ref<IO::ITextReader> GetIn()
		{
			throw NotImplementedException();
		}
	};

}