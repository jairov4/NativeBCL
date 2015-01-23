#include "BCL.h"

namespace System
{
	const Int64 Int64::MaxValue = INT64_MAX;
	const Int64 Int64::MinValue = INT64_MIN;

	Int64::Int64(Int64::int64 value) : value(value)
	{
	}

	Int64::Int64(const Int64& copy) : value(copy.value)
	{
	}

	Int64::Int64()
	{
	}

	Int64::operator Int64::int64() const
	{
		return value;
	}

	Int64& Int64::operator= (Int64::int64 v)
	{
		value = v;
		return *this;
	}

	String Int64::ToString() const
	{
		String str;
		return str;
	}

	Int32 Int64::GetHashCode() const
	{
		return static_cast<Int32>(value & 0xFFFFFFFF) ^ static_cast<Int32>(value >> 32);
	}
	
	Boolean Int64::Equals(const Int64& obj) const
	{
		return value == obj.value;
	}
	
	Int32 Int64::CompareTo(const Int64& obj) const
	{
		if (value < obj.value) return -1;
		else if (value > obj.value) return 1;
		return 0;
	}
}