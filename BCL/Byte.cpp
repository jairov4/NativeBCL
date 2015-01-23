#include "BCL.h"

namespace System
{
	const Byte Byte::MaxValue = UINT8_MAX;
	const Byte Byte::MinValue = 0;

	Byte::Byte(Byte::byte value) : value(value)
	{
	}

	Byte::Byte(const Byte& copy) : value(copy.value)
	{
	}

	Byte::Byte()
	{
	}

	Byte::operator Byte::byte() const
	{
		return value;
	}
	
	String Byte::ToString() const
	{
		String str;
		return str;
	}

	Int32 Byte::GetHashCode() const
	{
		return value ^ (value << 8);
	}


	Boolean Byte::Equals(const Byte& obj) const
	{
		return value == obj.value;
	}


	Int32 Byte::CompareTo(const Byte& obj) const
	{
		return value - obj.value;
	}
}