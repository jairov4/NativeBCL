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

	int32_t String::GetLength()
	{
		return this->value->size();
	}

	int32_t String::CompareTo(String& b)
	{
		return this->value->compare(*b.value);
	}

	bool String::Equals(String& str)
	{
		return CompareTo(str) == 0;
	}

	uint32_t String::GetHashCode()
	{
		auto hash = HashSequence32((const uint8_t*)value->c_str(), value->size());
		return hash;
	}

	String String::ToString()
	{
		return *this;
	}

    bool String::Equals(Object& obj)
    {
        auto str = dynamic_cast<String*>(&obj);
        if (str == nullptr) 
        {
            return false;
        }

        return Equals(*str);
    }

	bool String::operator== (String& b)
	{
		return Equals(b);
	}

	String String::operator+(String& b)
	{
		return String(*value + *b.value);
	}

    String::operator std::u16string()
    {
        return *value;
    }
}