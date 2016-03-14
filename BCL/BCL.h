#pragma once

#include <stdint.h>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#ifndef BCLAPI
#define BCLAPI
#endif

#ifndef BCLAPIOBJ
#define BCLAPIOBJ
#endif

#define interface struct

namespace System
{
	struct Object;
	struct String;
	struct Exception;

	template <typename T>
	using ref = std::shared_ptr<T>;

	template<typename T, typename... TArgs>
	inline ref<T> new_ref(TArgs&&... args) { return std::make_shared<T>(std::forward<TArgs>(args)...); }

	struct Object
	{
		virtual ~Object() = default;

		virtual uint32_t GetHashCode() const;
		virtual String ToString() const;
		virtual bool Equals(const Object& obj) const;
	};

	struct String final : Object
	{
	private:
		ref<std::u16string> value;

	public:
		String();
		String(const String& str);
		String(String&& str);
		String(const char16_t* str);
		String(const std::u16string& str);

		int32_t GetLength() const;
		int32_t CompareTo(const String& b) const;
		bool Equals(const String& b) const;

		// Object impl
		uint32_t GetHashCode() const override;
		String ToString() const override;
		bool Equals(const Object& b) const override;

		// operators
		String& operator=(const String& b);
		bool operator==(const String& b) const;
		String operator+(const String& right) const;
		operator std::u16string() const;
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
	};

	BCLAPIOBJ struct NotImplementedException : Exception
	{
		NotImplementedException();
		explicit NotImplementedException(String message);
		NotImplementedException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ struct InvalidOperationException : Exception
	{
		InvalidOperationException();
		explicit InvalidOperationException(String message);
		InvalidOperationException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ struct SystemException : Exception
	{
		SystemException();
		explicit SystemException(String message);
		SystemException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ struct OverflowException : SystemException
	{
		OverflowException();
		explicit OverflowException(String message);
		OverflowException(String message, ref<Exception> innerException);
	};

	BCLAPIOBJ struct ArgumentException : SystemException
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
		ArgumentOutOfRangeException();
		explicit ArgumentOutOfRangeException(String paramName);
		ArgumentOutOfRangeException(String paramName, String message);
		ArgumentOutOfRangeException(String message, ref<Exception> innerException);
	};

	namespace Collections
	{
		interface IEnumerator : Object
		{
			virtual bool MoveNext() = 0;
			virtual bool IsValid() = 0;
		};

		template<typename T>
		interface IGenericEnumerator : IEnumerator
		{
			virtual T GetCurrent() = 0;
		};

		interface IEnumerable : Object
		{
			virtual ref<IEnumerator> GetEnumerator() = 0;
		};

		template<typename T>
		interface IGenericEnumerable : IEnumerable
		{
			virtual ref<IGenericEnumerator<T>> GetGenericEnumerator() = 0;
		};

		interface IReadOnlyCollection : IEnumerable
		{
			virtual int32_t GetCount() = 0;
		};

		template<typename T>
		interface IGenericReadOnlyCollection : IReadOnlyCollection, IGenericEnumerable<T>
		{
			virtual bool Contains(T item) = 0;
		};

		interface ICollection : IReadOnlyCollection
		{
			virtual void Clear() = 0;
		};

		template<typename T>
		interface IGenericCollection : IGenericReadOnlyCollection<T>, ICollection
		{
			virtual void Add(T item) = 0;
			virtual void Remove(T item) = 0;
		};

		template<typename T>
		interface IGenericIReadOnlyList : IGenericReadOnlyCollection<T>
		{
			virtual T operator[] (int32_t index) = 0;
			virtual T GetAt(int32_t index) = 0;
			virtual int32_t IndexOf(T item) = 0;
		};

		interface IList : ICollection
		{
			virtual void RemoveAt(int32_t index) = 0;
		};

		template<typename T>
		interface IGenericList : IGenericIReadOnlyList<T>, IGenericCollection<T>, IList
		{
			virtual void SetAt(int32_t index, T item) = 0;
			virtual void Insert(int32_t index, T item) = 0;
		};

		template<typename T>
		struct List : IGenericList<T>
		{
		private:
			typedef std::vector<T> TVector;
			typedef typename TVector::iterator TVectorIterator;
			TVector storage;

			struct ListEnumerator final : IGenericEnumerator<T>
			{
			private:
				TVectorIterator begin, end;

			public:
				ListEnumerator(TVectorIterator begin, TVectorIterator end)
				{
					this->begin = begin;
					this->end = end;
				}

				bool MoveNext() override
				{
					++begin;
					return begin != end;
				}

				bool IsValid() override
				{
					return begin != end;
				}

				T GetCurrent() override
				{
					return *begin;
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
				for (auto i = 0; i < storage.size(); i++)
				{
					if (storage[i] == value)
					{
						RemoveAt(i);
						i--;
					}
				}
			}

			virtual int32_t GetCapacity()
			{
				return int32_t(storage.capacity());
			}

			virtual int32_t GetCount() override
			{
				return int32_t(storage.size());
			}

			virtual bool Contains(T value) override
			{
				return std::find(storage.begin(), storage.end(), value) != storage.end();
			}

			virtual T operator[] (int32_t index) override
			{
				return storage[index];
			}

			virtual T GetAt(int32_t index) override
			{
				return storage[index];
			}

			virtual int32_t IndexOf(T value) override
			{
				auto it = std::find(storage.begin(), storage.end(), value);
				if (it == storage.end()) return -1;
				return int32_t(it - storage.begin());
			}

			virtual void SetAt(int32_t index, T value) override
			{
				storage[index] = value;
			}

			virtual void Insert(int32_t index, T value) override
			{
				storage.insert(storage.begin() + index, value);
			}

			virtual void RemoveAt(int32_t index) override
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

		template<typename TKey, typename TValue>
		struct KeyValuePair final : Object
		{
		private:
			TKey Key;
			TValue Value;

		public:
			KeyValuePair(TKey k, TValue v) : Key(k), Value(v) {}

			TKey GetKey() { return Key; }
			TValue GetValue() { return Value; }

			bool Equals(KeyValuePair<TKey, TValue> obj)
			{
				return Key == obj.Key && Value == obj.Value;
			}
		};

		template<typename TKey, typename TValue>
		struct Dictionary : Object
		{
		private:

			struct KeyHasher
			{
				size_t operator()(TKey obj)
				{
					return obj.GetHashCode();
				}
			};

			typedef std::unordered_map<TKey, TValue, KeyHasher> Map;
			typedef typename Map::iterator TMapIterator;
			typedef KeyValuePair<TKey, TValue> TKeyValuePair;

			struct KeysCollection final : IGenericReadOnlyCollection<TKey>
			{
			private:
				ref<Map> entries;

				struct KeysCollectionEnumerator final : IGenericEnumerator<TKey>
				{
				private:
					TMapIterator begin, end;

				public:
					KeysCollectionEnumerator(TMapIterator begin, TMapIterator end)
					{
						this->begin = begin;
						this->end = end;
					}

					bool MoveNext() override
					{
						++begin;
						return begin != end;
					}

					bool IsValid() override
					{
						return begin != end;
					}

					TKey GetCurrent() override
					{
						return begin->first;
					}
				};

			public:

				explicit KeysCollection(ref<Map> entries) : entries(entries) { }

				bool Contains(TKey key) const
				{
					return entries->find(key) != entries->end();
				}

				int32_t GetCount() override
				{
					return std::int32_t(entries->size());
				}
			};

			struct ValuesCollection final : IGenericReadOnlyCollection<TValue>
			{
			private:
				ref<Map> entries;

				struct ValuesCollectionEnumerator final : IGenericEnumerator<TValue>
				{
				private:
					TMapIterator begin, end;

				public:
					ValuesCollectionEnumerator(TMapIterator begin, TMapIterator end)
					{
						this->begin = begin;
						this->end = end;
					}

					bool MoveNext() override
					{
						++begin;
						return begin != end;
					}

					bool IsValid() override
					{
						return begin != end;
					}

					TValue GetCurrent() override
					{
						return begin->second;
					}
				};

			public:
				ValuesCollection(ref<Map> entries) : entries(entries)
				{
				}

				bool Contains(const TValue& key) const
				{
					for (auto& i : *entries)
					{
						if (i.second == key) return true;
					}

					return false;
				}

				int32_t GetCount() const { return int32_t(entries->size()); }
			};

			struct DictionaryEnumerator final : IGenericEnumerator<KeyValuePair<TKey, TValue>>
			{
			private:
				TMapIterator begin, end;

			public:
				DictionaryEnumerator(TMapIterator begin, TMapIterator end)
				{
					this->begin = begin;
					this->end = end;
				}

				bool MoveNext() override
				{
					++begin;
					return begin != end;
				}

				bool IsValid() override
				{
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

			virtual bool ContainsKey(const TKey& key) const
			{
				return GetKeys()->Contains(key);
			}

			virtual bool TryGetValue(const TKey& key, TValue* out_value) const
			{
				auto r = entries->find(key);
				if (r == entries->end()) return false;
				*out_value = r->second;
				return true;
			}

			virtual int32_t GetCount() const
			{
				return int32_t(entries->size());
			}

			virtual bool Contains(const KeyValuePair<TKey, TValue>& pair) const
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
		BCLAPIOBJ enum struct SeekOrigin : int8_t
		{
			Begin = 0,
			Current = 1,
			End = 2
		};

		BCLAPIOBJ interface IStream : Object
		{
			virtual bool CanRead() = 0;
			virtual bool CanWrite() = 0;
			virtual bool CanSeek() = 0;
			virtual bool CanTimeout() = 0;
			virtual int64_t GetLength() = 0;
			virtual int64_t GetPosition() = 0;
			virtual int64_t GetTimeout() = 0;
			virtual void SetTimeout(int64_t timeout) = 0;
			virtual int32_t ReadByte() = 0;
			virtual void WriteByte(uint8_t data) = 0;
			virtual void Read(uint8_t* buffer, int32_t index, int32_t count) = 0;
			virtual void Write(uint8_t* buffer, int32_t index, int32_t count) = 0;
			virtual int64_t Seek(int64_t offset, SeekOrigin origin) = 0;
		};

		BCLAPIOBJ interface ITextReader : Object
		{
			virtual void Close() = 0;
			virtual int32_t Peek() = 0;
			virtual int32_t Read() = 0;
			virtual int32_t Read(char16_t* buffer, int32_t index, int32_t count) = 0;
			virtual String ReadToEnd() = 0;
			virtual String ReadLine() = 0;
		};

		BCLAPIOBJ struct StreamReader : ITextReader
		{
		};
	}

	BCLAPIOBJ struct Console
	{
		static ref<IO::ITextReader> GetIn()
		{
			throw NotImplementedException();
		}
	};
}