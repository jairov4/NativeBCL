#include "BCL.h"

namespace System
{
	const Int16 Int16::MaxValue = INT16_MAX;
	const Int16 Int16::MinValue = INT16_MIN;

	Int16::Int16(Int16::int16 value) : value(value)
	{
	}

	Int16::Int16(const Int16& copy) : value(copy.value)
	{
	}

	Int16::Int16()
	{
	}

	Int16::operator Int16::int16() const
	{
		return value;
	}
	
	String Int16::ToString() const
	{
		String str;
		return str;
	}

	Int32 Int16::GetHashCode() const
	{
		return value | (value << 16);
	}
	
	Boolean Int16::Equals(const Int16& obj) const
	{
		return value == obj.value;
	}
	
	Int32 Int16::CompareTo(const Int16& obj) const
	{
		return value - obj.value;
	}
}