#include "BCL.h"

namespace System
{
	const UInt64 UInt64::MaxValue = UINT64_MAX;
	const UInt64 UInt64::MinValue = 0;

	UInt64::UInt64(UInt64::uint64 value) : value(value)
	{
	}

	UInt64::UInt64(const UInt64& copy) : value(copy.value)
	{
	}

	UInt64::UInt64()
	{
	}

	UInt64::operator UInt64::uint64() const
	{
		return value;
	}


	String UInt64::ToString() const
	{
		String str;
		return str;
	}

	Int32 UInt64::GetHashCode() const
	{
		return static_cast<UInt32>(value & 0xFFFFFFFF) ^ static_cast<UInt32>(value >> 32);
	}

	Boolean UInt64::Equals(const Object& obj) const
	{
		auto b = static_cast<const UInt64&>(obj);
		return value == b.value;
	}

	Boolean UInt64::Equals(const UInt64& obj) const
	{
		return value == obj.value;
	}

	Int32 UInt64::CompareTo(const Object& obj) const
	{
		auto b = static_cast<const UInt64&>(obj);
		if (value < b.value) return -1;
		else if (value > b.value) return 1;
		return 0;
	}

	Int32 UInt64::CompareTo(const UInt64& obj) const
	{		
		if (value < obj.value) return -1;
		else if (value > obj.value) return 1;
		return 0;
	}
}