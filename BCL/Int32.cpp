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

	Int32& Int32::operator++()
	{
		value++;
		return *this;
	}

	Int32& Int32::operator--()
	{
		value--;
		return *this;
	}

	Int32 Int32::operator++(int)
	{
		auto copy = value;
		value++;
		return copy;
	}

	Int32 Int32::operator--(int)
	{
		auto copy = value;
		value--;
		return copy;
	}

	Int32& Int32::operator+=(const Int32& o)
	{
		value += o.value;
		return *this;
	}

	Int32& Int32::operator-=(const Int32& o)
	{
		value -= o.value;
		return *this;
	}

	Int32& Int32::operator*=(const Int32& o)
	{
		value *= o.value;
		return *this;
	}

	Int32& Int32::operator/=(const Int32& o)
	{
		value /= o.value;
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
	
	Boolean Int32::Equals(const Int32& obj) const
	{
		return value == obj.value;
	}
	
	Int32 Int32::CompareTo(const Int32& obj) const
	{		
		if (value < obj.value) return -1;
		else if (value > obj.value) return 1;
		return 0;
	}
}