#include "BCL.h"

namespace System
{
	const UInt16 UInt16::MaxValue = UINT16_MAX;
	const UInt16 UInt16::MinValue = 0;

	UInt16::UInt16(UInt16::uint16 value) : value(value)
	{
	}

	UInt16::UInt16(const UInt16& copy) : value(copy.value)
	{
	}

	UInt16::UInt16()
	{
	}

	UInt16::operator UInt16::uint16() const
	{
		return value;
	}

	UInt16& UInt16::operator= (UInt16::uint16 v)
	{
		value = v;
		return *this;
	}

	UInt16& UInt16::operator++()
	{
		value++;
		return *this;
	}

	UInt16& UInt16::operator--()
	{
		value--;
		return *this;
	}

	UInt16 UInt16::operator++(int)
	{
		auto copy = value;
		value++;
		return copy;
	}

	UInt16 UInt16::operator--(int)
	{
		auto copy = value;
		value--;
		return copy;
	}

	UInt16& UInt16::operator+=(const UInt16& o)
	{
		value += o.value;
		return *this;
	}

	UInt16& UInt16::operator-=(const UInt16& o)
	{
		value -= o.value;
		return *this;
	}

	UInt16& UInt16::operator*=(const UInt16& o)
	{
		value *= o.value;
		return *this;
	}

	UInt16& UInt16::operator/=(const UInt16& o)
	{
		value /= o.value;
		return *this;
	}
	
	String UInt16::ToString() const
	{
		String str;
		return str;
	}

	Int32 UInt16::GetHashCode() const
	{
		return value | (value << 16);
	}

	Boolean UInt16::Equals(const UInt16& obj) const
	{
		return value == obj.value;
	}
	
	Int32 UInt16::CompareTo(const UInt16& obj) const
	{
		return value - obj.value;
	}
}