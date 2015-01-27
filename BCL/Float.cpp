#include "BCL.h"
#include <float.h>
#include <limits>

namespace System
{
	const Float Float::MaxValue = FLT_MAX;
	const Float Float::MinValue = FLT_MIN;

	const Float Float::Epsilon = DBL_EPSILON;
	const Float Float::NegativeInfinity = -std::numeric_limits<float_t>::infinity();
	const Float Float::PositiveInfinity = std::numeric_limits<float_t>::infinity();
	const Float Float::NaN = std::numeric_limits<float_t>::quiet_NaN();
	
	Boolean Float::IsInfinity(Float d)
	{
		return isinf(d.value);
	}

	Boolean Float::IsNaN(Float d)
	{
		return isnan(d.value);
	}

	Float::Float(float_t value) : value(value)
	{
	}

	Float::Float(const Float& copy) : value(copy.value)
	{
	}

	Float::Float()
	{
	}

	Float::operator float_t() const
	{
		return value;
	}

	Float& Float::operator= (float_t v)
	{
		value = v;
		return *this;
	}

	Float& Float::operator+=(const Float& o)
	{
		value += o.value;
		return *this;
	}

	Float& Float::operator-=(const Float& o)
	{
		value -= o.value;
		return *this;
	}

	Float& Float::operator*=(const Float& o)
	{
		value *= o.value;
		return *this;
	}

	Float& Float::operator/=(const Float& o)
	{
		value /= o.value;
		return *this;
	}

	String Float::ToString() const
	{
		throw NotImplementedException();
	}

	Int32 Float::GetHashCode() const
	{
		std::hash<float_t> s;
		return (int32_t)s(value);
	}

	Boolean Float::Equals(const Float& obj) const
	{
		return value == obj.value;
	}

	Int32 Float::CompareTo(const Float& obj) const
	{
		if (value < obj.value) return -1;
		if (value > obj.value) return 1;
		if (value == obj.value) return 0;

		// At least one of the values is NaN.
		if (IsNaN(value)) return IsNaN(value) ? 0 : -1;
		
		return 1;
	}
}