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

	UInt64& UInt64::operator= (UInt64::uint64 v)
	{
		value = v;
		return *this;
	}

	UInt64& UInt64::operator++()
	{
		value++;
		return *this;
	}

	UInt64& UInt64::operator--()
	{
		value--;
		return *this;
	}

	UInt64 UInt64::operator++(int)
	{
		auto copy = value;
		value++;
		return copy;
	}

	UInt64 UInt64::operator--(int)
	{
		auto copy = value;
		value--;
		return copy;
	}

	UInt64& UInt64::operator+=(const UInt64& o)
	{
		value += o.value;
		return *this;
	}

	UInt64& UInt64::operator-=(const UInt64& o)
	{
		value -= o.value;
		return *this;
	}

	UInt64& UInt64::operator*=(const UInt64& o)
	{
		value *= o.value;
		return *this;
	}

	UInt64& UInt64::operator/=(const UInt64& o)
	{
		value /= o.value;
		return *this;
	}

	String UInt64::ToString() const
	{
		throw NotImplementedException();
	}

	Int32 UInt64::GetHashCode() const
	{
		return static_cast<UInt32>(value & 0xFFFFFFFF) ^ static_cast<UInt32>(value >> 32);
	}
	
	Boolean UInt64::Equals(const UInt64& obj) const
	{
		return value == obj.value;
	}
	
	Int32 UInt64::CompareTo(const UInt64& obj) const
	{		
		if (value < obj.value) return -1;
		else if (value > obj.value) return 1;
		return 0;
	}
}