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

	String::String(const char16_t* str) : value(new_ref<u16string>(str))
	{
	}

	int32_t String::GetLength() const
	{
		return int32_t(this->value->size());
	}

	int32_t String::CompareTo(const String& b) const
	{
		return this->value->compare(*b.value);
	}

	bool String::Equals(const String& str) const
	{
		return CompareTo(str) == 0;
	}

	uint32_t String::GetHashCode() const
	{
		auto hash = HashSequence32(reinterpret_cast<const uint8_t*>(value->c_str()), value->size() * sizeof(char16_t));
		return hash;
	}

	String String::ToString() const
	{
		return *this;
	}

    bool String::Equals(const Object& obj) const
    {
        auto str = dynamic_cast<const String*>(&obj);
        if (str == nullptr) 
        {
            return false;
        }

        return Equals(*str);
    }

	bool String::operator== (const String& b) const
	{
		return Equals(b);
	}

	String String::operator+(const String& b) const
	{
		return String(*value + *b.value);
	}

    String::operator std::u16string() const
    {
        return *value;
    }
}