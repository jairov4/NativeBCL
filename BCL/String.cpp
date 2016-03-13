#include "BCL.h"
#include "BCLInternal.h"

namespace System
{
	using namespace std;

	String::String() : value(nullptr)
	{
	}

	String::String(const String& str) : value(str.value)
	{
	}

	String::String(String&& str) : value(str.value)
	{
	}

	String::String(const u16string& str) : value(new_ref<u16string>(str))
	{
	}

	Int32 String::GetLength()
	{
		return this->value->size();
	}

	Int32 String::CompareTo(String& b)
	{
		return this->value->compare(*b.value);
	}

	Boolean String::Equals(String& str)
	{
		return CompareTo(str) == 0;
	}

	Int32 String::GetHashCode() override
	{
		auto buffer = static_cast<const uint8_t*>(value->c_str());
		auto hash = HashSequence32(buffer, size);
		return (Int32)hash;
	}

	String String::ToString() override
	{
		return *this;
	}

	Boolean String::operator== (const String& b) const
	{
		return Equals(b);
	}

	String String::operator+(const String& b) const
	{
		auto totalSize = size + b.size;
		auto newBuffer = new char16_t[totalSize];
		memcpy_s(&newBuffer[0], size, value, size);
		memcpy_s(&newBuffer[size], b.size, b.value, b.size);
		auto str = String(newBuffer, totalSize);
		return str;
	}
}