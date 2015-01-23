#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>

namespace System
{
	class Object;
	class Int16;
	class UInt16;
	class Int32;
	class UInt32;
	class Int64;
	class UInt64;
	class SByte;
	class Byte;
	class String;
	class String;
	class Boolean;
	class Exception;


	template <typename T>
	using ref = std::shared_ptr < T > ;

	template<typename T, typename... TArgs>
	ref<T> new_ref(TArgs&&... args) { return std::make_shared<T>(std::forward<TArgs>(args)...); }

	class Object
	{
	public:
		virtual String ToString() const;
		virtual Int32 GetHashCode() const;
		virtual Boolean Equals(const Object& obj) const;
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

		Int32 GetHashCode() const override;
		String ToString() const override;
		Boolean Equals(const Object& obj) const override;

		Boolean operator==(const String& b) const;
	};

	class SByte final : public Object
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

		Int32 CompareTo(const Object& obj) const;
		Int32 CompareTo(const SByte& obj) const;
		Boolean Equals(const SByte& obj) const;

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class Byte final : public Object
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

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class Int16 final : public Object
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

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class UInt16 final : public Object
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

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class Int32 final : public Object
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

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class UInt32 final : public Object
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

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class Int64 final : public Object
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

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class UInt64 final : public Object
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

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class Char final : public Object
	{
		char16_t value;
	public:
		Char();
		Char(char16_t value);

		operator char16_t() const;

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class Float final : public Object
	{
		float value;
	public:
		Float();
		Float(float value);

		operator float() const;

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class Double final : public Object
	{
		double value;
	public:
		Double();
		Double(double value);
		Double(const double& value);

		operator double() const;

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class Boolean final : public Object
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

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
	};

	class Decimal final : public Object
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

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
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
		Boolean Equals(const Object& obj) const override;
	};

	class TimeSpan final : public Object
	{
		Int32 ticks;

	public:
		TimeSpan();
		TimeSpan(DateTime value, TimeSpan offset);

		String ToString() const override;
		Int32 GetHashCode() const override;
		Boolean Equals(const Object& obj) const override;
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
		Boolean Equals(const Object& obj) const override;
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

		template<class T>
		class IEnumerator : public Object
		{
		public:
			virtual Boolean MoveNext() = 0;
			virtual T GetCurrent() const = 0;
			virtual T operator*() const = 0;
		};

		template<class T>
		class IReadOnlyCollection : public Object
		{
		public:
			virtual Boolean Contains(T item) = 0;
			virtual Int32 GetCount() = 0;
		};

		template<class T>
		class ICollection : public virtual IReadOnlyCollection < T >
		{
		public:
			virtual void Add(T item) = 0;
			virtual void Remove(T value) = 0;
			virtual void Clear() = 0;
		};

		template<class T>
		class IReadOnlyList : public virtual IReadOnlyCollection < T >
		{
		public:
			virtual T operator[] (Int32 index) = 0;
			virtual T GetAt(Int32 index) = 0;
			virtual Int32 IndexOf(T value) = 0;
		};

		template<class T>
		class IList : public virtual ICollection<T>, public virtual IReadOnlyList < T >
		{
		public:
			virtual void SetAt(Int32 index, T value) = 0;
			virtual void Insert(Int32 index, T value) = 0;
			virtual void RemoveAt(Int32 index) = 0;
		};

		template <class TEnumerator, class TIterator, class T>
		class StlEnumerator : public virtual IEnumerator < T >
		{
		protected:
			TIterator i, end;
		public:
			StlEnumerator(TIterator begin, TIterator end) : i(begin), end(end) {}
			T operator* () const override { return GetCurrent(); }
			TEnumerator& operator++ () { ++i; return (TEnumerator&)(*this); }
			Boolean operator== (const TEnumerator& b) const { return i == b.i; }
			Boolean operator!= (const TEnumerator& b) const { return i != b.i; }

			virtual Boolean MoveNext() override
			{
				if (i == end) return false;
				++i;
				return true;
			}
		};

		template<class T>
		class List : public virtual IList < T >
		{
		private:
			typedef std::vector<T> TVector;
			typedef typename TVector::const_iterator TVectorIterator;
			TVector storage;

			class ListEnumerator : public StlEnumerator < ListEnumerator, TVectorIterator, T >
			{
			public:
				ListEnumerator(TVectorIterator begin, TVectorIterator end) : StlEnumerator(begin, end) {}
				virtual T GetCurrent() const override { return *i; }
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

			ListEnumerator begin() const
			{
				return ListEnumerator(storage.begin(), storage.end());
			}

			ListEnumerator end() const
			{
				return ListEnumerator(storage.end(), storage.end());
			}

			virtual void Add(T item) override
			{
				storage.push_back(item);
			}

			virtual void Clear() override
			{
				storage.clear();
			}

			virtual void Remove(T value) override
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

			virtual Int32 GetCount() override
			{
				return (int)storage.size();
			}

			virtual Boolean Contains(T value) override
			{
				return std::find(storage.begin(), storage.end(), value) != storage.end();
			}

			virtual T operator[] (Int32 index) override
			{
				return storage[index];
			}

			virtual T GetAt(Int32 index) override
			{
				return storage[index];
			}

			virtual Int32 IndexOf(T value) override
			{
				auto it = std::find(storage.begin(), storage.end(), value);
				if (it == storage.end()) return -1;
				return (int)(it - storage.begin());
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
		};

		template<class T>
		class IComparer : public Object
		{
		public:
			Int32 Compare(T x, T y);
		};

		template<class TKey, class TValue>
		class KeyValuePair : public Object
		{
		public:
			TKey Key;
			TValue Value;

			KeyValuePair(TKey k, TValue v) : Key(k), Value(v) {}
		};

		template<class TKey, class TValue>
		class IReadOnlyDictionary : public virtual IReadOnlyCollection < KeyValuePair<TKey, TValue> >
		{
			virtual TValue operator[](TKey key) = 0;
			virtual ref<IReadOnlyCollection<TKey>> GetKeys() = 0;
			virtual ref<IReadOnlyCollection<TValue>> GetValues() = 0;
			virtual Boolean ContainsKey(TKey key) = 0;
			virtual Boolean TryGetValue(TKey key, TValue& out_value) = 0;
		};

		template<class TKey, class TValue>
		class IDictionary : public virtual IReadOnlyDictionary < TKey, TValue >
		{
		public:
			virtual void Add(TKey key, TValue value) = 0;
			virtual void Remove(TKey key) = 0;
		};

		template<class TKey, class TValue>
		class Dictionary : public virtual IDictionary < TKey, TValue >
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

			class KeyCollection : public virtual IReadOnlyCollection < TKey >
			{
			private:
				ref<Map> entries;

				class KeyCollectionEnumerator : public StlEnumerator < KeyCollectionEnumerator, TMapIterator, TKey >
				{
				public:
					KeyCollectionEnumerator(TMapIterator begin, TMapIterator end) : StlEnumerator(begin, end) {}
					virtual TKey GetCurrent() const override { return i->first; }
				};

			public:

				KeyCollection(ref<Map> entries) : entries(entries) { }

				KeyCollectionEnumerator begin() const
				{
					return KeyCollectionEnumerator(entries->begin(), entries->end());
				}

				KeyCollectionEnumerator end() const
				{
					return KeyCollectionEnumerator(entries->end(), entries->end());
				}

				virtual Boolean Contains(TKey key) override
				{
					return entries->find(key) != entries->end();
				}

				virtual Int32 GetCount() override
				{
					return (int)entries->size();
				}
			};

			class ValuesCollection : public virtual IReadOnlyCollection < TValue >
			{
			private:
				ref<Map> entries;

				class ValuesCollectionEnumerator : public StlEnumerator < ValuesCollectionEnumerator, TMapIterator, TValue >
				{
				public:
					ValuesCollectionEnumerator(TMapIterator begin, TMapIterator end) : StlEnumerator(begin, end) {}
					virtual TValue GetCurrent() const override { return i->second; }
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

				virtual Boolean Contains(TValue key) override
				{
					for (auto& i : *entries)
					{
						if (i.second == key) return true;
					}
					return false;
				}

				virtual Int32 GetCount() override { return (int)entries->size(); }
			};

			class DictionaryEnumerator : public StlEnumerator < DictionaryEnumerator, TMapIterator, TKeyValuePair >
			{
			public:
				DictionaryEnumerator(TMapIterator begin, TMapIterator end) : StlEnumerator(begin, end) {}
				virtual TKeyValuePair GetCurrent() const override { return TKeyValuePair(i->first, i->second); }
			};

			ref<Map> entries;
			ref<IReadOnlyCollection<TKey>> keySet;
			ref<IReadOnlyCollection<TValue>> valuesCollection;

		public:

			Dictionary()
			{
				entries = new_ref<Map>();
				keySet = ref<IReadOnlyCollection<TKey>>(new KeyCollection(entries));
				valuesCollection = ref<IReadOnlyCollection<TValue>>(new ValuesCollection(entries));
			}

			Dictionary(const Dictionary& copy)
			{
				entries = new_ref<Map>(copy.entries.get());
				keySet = ref<IReadOnlyCollection<TKey>>(new KeyCollection(entries));
				valuesCollection = ref<IReadOnlyCollection<TValue>>(new ValuesCollection(entries));
			}

			Dictionary(Dictionary&& rval)
			{
				entries = rval.entries;
				keySet = rval.keySet;
				valuesCollection = rval.valuesCollection;
			}

			virtual TValue operator[](TKey key) override
			{
				return (*entries)[key];
			}

			virtual ref<IReadOnlyCollection<TKey>> GetKeys() override
			{
				return keySet;
			}

			virtual ref<IReadOnlyCollection<TValue>> GetValues() override
			{
				return valuesCollection;
			}

			virtual void Add(TKey key, TValue value) override
			{
				(*entries)[key] = value;
			}

			virtual void Remove(TKey key) override
			{
				entries->erase(key);
			}

			DictionaryEnumerator begin() const
			{
				return DictionaryEnumerator(entries->begin(), entries->end());
			}

			DictionaryEnumerator end() const
			{
				return DictionaryEnumerator(entries->end(), entries->end());
			}

			virtual Boolean ContainsKey(TKey key) override
			{
				return GetKeys()->Contains(key);
			}

			virtual Boolean TryGetValue(TKey key, TValue& out_value) override
			{
				auto r = entries->find(key);
				if (r == entries->end()) return false;
				out_value = r->second;
				return true;
			}

			virtual Int32 GetCount() override
			{
				return (int)entries->size();
			}

			virtual Boolean Contains(KeyValuePair<TKey, TValue> pair)
			{
				for (auto& pairIt : *entries)
				{
					if (pairIt.first == pair.Key && pairIt.second == pair.Value)
					{
						return true;
					}
				}
				return false;
			}
		};
	}

}