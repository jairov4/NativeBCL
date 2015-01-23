#include "BCL.h"

namespace System
{
	const UInt32 UInt32::MaxValue = UINT32_MAX;
	const UInt32 UInt32::MinValue = 0;

	UInt32::UInt32(UInt32::uint32 value) : value(value)
	{
	}

	UInt32::UInt32(const UInt32& copy) : value(copy.value)
	{
	}


	UInt32::UInt32()
	{
	}

	UInt32::operator UInt32::uint32() const
	{
		return value;
	}


	String UInt32::ToString() const
	{
		String str;
		return str;
	}

	Int32 UInt32::GetHashCode() const
	{
		return value;
	}

	Boolean UInt32::Equals(const Object& obj) const
	{
		auto b = static_cast<const UInt32&>(obj);
		return value == b.value;
	}

	Boolean UInt32::Equals(const UInt32& obj) const
	{
		return value == obj.value;
	}

	Int32 UInt32::CompareTo(const Object& obj) const
	{
		auto b = static_cast<const UInt32&>(obj);
		if (value < b.value) return -1;
		else if (value > b.value) return 1;
		return 0;
	}

	Int32 UInt32::CompareTo(const UInt32& obj) const
	{		
		if (value < obj.value) return -1;
		else if (value > obj.value) return 1;
		return 0;
	}
}