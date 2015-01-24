#include "BCL.h"

namespace System
{
	String::String()
	{
	}

	String::String(const char*str)
	{
		size_t len = strlen(str);
		wchar_t* buffer = new wchar_t[len+1];
		size_t len2;
		mbstowcs_s(&len2, buffer, len+1, str, len+1);
		value = buffer;
		delete [] buffer;
	}

	String::String(const wchar_t* str) : value(str)
	{
	}

	String::String(const String& str) : value(str.value)
	{
	}

	String::operator std::wstring() const
	{
		return value;
	}
	
	Int32 String::GetLength() const
	{
		return (int)value.length();
	}

	Int32 String::GetHashCode() const
	{
		return 0;
	}
	
	String String::ToString() const
	{
		return *this;
	}

	Boolean String::operator== (const String& b) const
	{
		return value == b.value;
	}
}