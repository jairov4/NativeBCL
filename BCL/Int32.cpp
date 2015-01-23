#include "BCL.h"

namespace System
{
	const Int32 Int32::MaxValue = INT32_MAX;
	const Int32 Int32::MinValue = INT32_MIN;

	Int32::Int32(Int32::int32 value) : value(value)
	{
	}

	Int32::Int32(const Int32& copy) : value(copy.value)
	{
	}

	Int32::Int32()
	{
	}

	Int32::operator Int32::int32() const
	{
		return value;
	}

	Int32& Int32::operator= (Int32::int32 v)
	{
		value = v;
		return *this;
	}

	String Int32::ToString() const
	{
		String str;
		return str;
	}

	Int32 Int32::GetHashCode() const
	{
		return value;
	}

	Boolean Int32::Equals(const Object& obj) const
	{
		auto b = static_cast<const Int32&>(obj);
		return value == b.value;
	}

	Boolean Int32::Equals(const Int32& obj) const
	{
		return value == obj.value;
	}

	Int32 Int32::CompareTo(const Object& obj) const
	{
		auto b = static_cast<const Int32&>(obj);
		if (value < b.value) return -1;
		else if (value > b.value) return 1;
		return 0;
	}

	Int32 Int32::CompareTo(const Int32& obj) const
	{		
		if (value < obj.value) return -1;
		else if (value > obj.value) return 1;
		return 0;
	}
}