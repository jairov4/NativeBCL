#include "BCL.h"

namespace System
{
	Boolean::Boolean(bool value) : value(value)
	{
	}

	Boolean::Boolean(const Boolean& copy) : value(copy.value)
	{
	}
		
	Boolean::Boolean()
	{
	}

	Boolean::operator bool() const
	{
		return value;
	}
	
	String Boolean::ToString() const
	{
		String str;
		return str;
	}

	Int32 Boolean::GetHashCode() const
	{
		return value ? 1 : 0;
	}

	Boolean Boolean::Equals(const Object& obj) const
	{
		auto b = static_cast<const Boolean&>(obj);
		return value == b.value;
	}

	Boolean Boolean::Equals(const Boolean& obj) const
	{
		return value == obj.value;
	}

	Int32 Boolean::CompareTo(const Object& obj) const
	{
		auto b = static_cast<const Boolean&>(obj);
		if (value == b.value) return 0;
		else if(!value) return -1;
		return 1;
	}

	Int32 Boolean::CompareTo(const Boolean& obj) const
	{
		if (value == obj.value) return 0;
		else if (!value) return -1;
		return 1;
	}
}