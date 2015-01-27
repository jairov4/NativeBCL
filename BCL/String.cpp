#include "BCL.h"

namespace System
{
	using namespace std;

	static wstring CharArrayToWstring(const char* str)
	{
		size_t len = strlen(str);
		wchar_t* buffer = new wchar_t[len + 1];
		size_t len2;
		mbstowcs_s(&len2, buffer, len + 1, str, len + 1);
		wstring strOut(buffer);
		delete[] buffer;
		return strOut;
	}

	String::String() : value(new_ref<wstring>())
	{
	}

	String::String(const wstring& str) : value(new_ref<wstring>(str))
	{
	}

	String::String(const char*str) : value(new_ref<wstring>(CharArrayToWstring(str)))
	{
	}

	String::String(const wchar_t* str) : value(new_ref<wstring>(str))
	{
	}

	String::String(const String& str) : value(new_ref<wstring>(*str.value))
	{
	}

	String::String(String&& str) : value(str.value)
	{
	}

	String::operator wstring() const
	{
		return *value;
	}

	Int32 String::GetLength() const
	{
		return (std::int32_t)value->length();
	}

	Int32 String::GetHashCode() const
	{
		return (std::int32_t)hash<wstring>()(*value);
	}

	const String& String::ToString() const
	{
		return *this;
	}

	Boolean String::operator== (const String& b) const
	{
		return value == b.value;
	}

	String String::operator+(const String& b) const
	{
		return String(*value + *b.value);
	}

	String String::operator+(const char* b) const
	{
		return String(*value + CharArrayToWstring(b));
	}

	String String::operator+(const wchar_t* b) const
	{
		return String(*value + b);
	}
}