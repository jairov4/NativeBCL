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

	UInt32& UInt32::operator= (UInt32::uint32 v)
	{
		value = v;
		return *this;
	}

	UInt32& UInt32::operator++()
	{
		value++;
		return *this;
	}

	UInt32& UInt32::operator--()
	{
		value--;
		return *this;
	}

	UInt32 UInt32::operator++(int)
	{
		auto copy = value;
		value++;
		return copy;
	}

	UInt32 UInt32::operator--(int)
	{
		auto copy = value;
		value--;
		return copy;
	}

	UInt32& UInt32::operator+=(const UInt32& o)
	{
		value += o.value;
		return *this;
	}

	UInt32& UInt32::operator-=(const UInt32& o)
	{
		value -= o.value;
		return *this;
	}

	UInt32& UInt32::operator*=(const UInt32& o)
	{
		value *= o.value;
		return *this;
	}

	UInt32& UInt32::operator/=(const UInt32& o)
	{
		value /= o.value;
		return *this;
	}

	String UInt32::ToString() const
	{
		throw NotImplementedException();
	}

	Int32 UInt32::GetHashCode() const
	{
		return value;
	}

	Boolean UInt32::Equals(const UInt32& obj) const
	{
		return value == obj.value;
	}

	Int32 UInt32::CompareTo(const UInt32& obj) const
	{
		if (value < obj.value) return -1;
		else if (value > obj.value) return 1;
		return 0;
	}
}