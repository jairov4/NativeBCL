#include "BCL.h"
#include <limits>
#include <float.h>

namespace System
{
	const Double Double::MaxValue = DBL_MAX;
	const Double Double::MinValue = DBL_MIN;

	const Double Double::Epsilon = DBL_EPSILON;
	const Double Double::NegativeInfinity = -std::numeric_limits<double_t>::infinity();
	const Double Double::PositiveInfinity = std::numeric_limits<double_t>::infinity();
	const Double Double::NaN = std::numeric_limits<double_t>::quiet_NaN();

	Boolean Double::IsInfinity(Double d) 
	{
		return isinf(d.value);
	}

	Boolean Double::IsNaN(Double d)
	{
		return isnan(d.value);
	}

	Double::Double(double_t value) : value(value)
	{
	}

	Double::Double(const Double& copy) : value(copy.value)
	{
	}

	Double::Double()
	{
	}

	Double::operator double_t() const
	{
		return value;
	}

	Double& Double::operator= (double_t v)
	{
		value = v;
		return *this;
	}
	
	Double& Double::operator+=(const Double& o)
	{
		value += o.value;
		return *this;
	}

	Double& Double::operator-=(const Double& o)
	{
		value -= o.value;
		return *this;
	}

	Double& Double::operator*=(const Double& o)
	{
		value *= o.value;
		return *this;
	}

	Double& Double::operator/=(const Double& o)
	{
		value /= o.value;
		return *this;
	}

	String Double::ToString() const
	{
		throw NotImplementedException();
	}

	Int32 Double::GetHashCode() const
	{
		std::hash<double_t> s;
		return (int32_t)s(value);
	}

	Boolean Double::Equals(const Double& obj) const
	{
		return value == obj.value;
	}

	Int32 Double::CompareTo(const Double& obj) const
	{
		if (value < obj.value) return -1;
		if (value > obj.value) return 1;
		if (value == obj.value) return 0;

		// At least one of the values is NaN.
		if (IsNaN(value)) return IsNaN(value) ? 0 : -1;

		return 1;
	}
}