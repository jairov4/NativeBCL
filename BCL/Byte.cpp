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

	Byte& Byte::operator= (Byte::byte v)
	{
		value = v;
		return *this;
	}

	Byte& Byte::operator++()
	{
		value++;
		return *this;
	}

	Byte& Byte::operator--()
	{
		value--;
		return *this;
	}

	Byte Byte::operator++(int)
	{
		auto copy = value;
		value++;
		return copy;
	}

	Byte Byte::operator--(int)
	{
		auto copy = value;
		value--;
		return copy;
	}

	Byte& Byte::operator+=(const Byte& o)
	{
		value += o.value;
		return *this;
	}

	Byte& Byte::operator-=(const Byte& o)
	{
		value -= o.value;
		return *this;
	}

	Byte& Byte::operator*=(const Byte& o)
	{
		value *= o.value;
		return *this;
	}

	Byte& Byte::operator/=(const Byte& o)
	{
		value /= o.value;
		return *this;
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