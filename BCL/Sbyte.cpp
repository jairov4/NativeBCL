#include "BCL.h"

namespace System
{
	const SByte SByte::MaxValue = INT8_MAX;
	const SByte SByte::MinValue = INT8_MIN;

	SByte::SByte(SByte::sbyte value) : value(value)
	{
	}

	SByte::SByte(const SByte& copy) : value(copy.value)
	{		
	}

	SByte::SByte()
	{
	}

	SByte::operator SByte::sbyte() const
	{
		return value;
	}

	SByte& SByte::operator= (SByte::sbyte v)
	{
		value = v;
		return *this;
	}

	SByte& SByte::operator++()
	{
		value++;
		return *this;
	}

	SByte& SByte::operator--()
	{
		value--;
		return *this;
	}

	SByte SByte::operator++(int)
	{
		auto copy = value;
		value++;
		return copy;
	}

	SByte SByte::operator--(int)
	{
		auto copy = value;
		value--;
		return copy;
	}

	SByte& SByte::operator+=(const SByte& o)
	{
		value += o.value;
		return *this;
	}

	SByte& SByte::operator-=(const SByte& o)
	{
		value -= o.value;
		return *this;
	}

	SByte& SByte::operator*=(const SByte& o)
	{
		value *= o.value;
		return *this;
	}
	SByte& SByte::operator/=(const SByte& o)
	{
		value /= o.value;
		return *this;
	}
	
	String SByte::ToString() const
	{
		throw NotImplementedException();
	}

	Int32 SByte::GetHashCode() const
	{
		return value ^ (value << 8);
	}
	
	Boolean SByte::Equals(const SByte& obj) const
	{		
		return value == obj.value;
	}
	
	Int32 SByte::CompareTo(const SByte& obj) const
	{
		return value - obj.value;
	}
}