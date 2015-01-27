#include "BCL.h"

namespace System
{
	static const Int32 SignMask = 0x80000000;

	// Scale mask for the flags field. This byte in the flags field contains
	// the power of 10 to divide the Decimal value by. The scale byte must
	// contain a value between 0 and 28 inclusive.
	static const Int32 ScaleMask = 0x00FF0000;

	// Number of bits scale is shifted by.
	static const Int32 ScaleShift = 16;

	// The maximum power of 10 that a 32 bit integer can store
	static const Int32 MaxInt32Scale = 9;

	Decimal::Decimal()
	{
	}

	Decimal::Decimal(const Decimal& copy) : lo(copy.lo), mid(copy.mid), hi(copy.hi), flags(copy.flags)
	{
	}

	
	Decimal::Decimal(Int32 lo, Int32 mid, Int32 hi, Int32 flags) : lo(lo), mid(mid), hi(hi), flags(flags)
	{
	}

	Decimal::Decimal(Int32 lo, Int32 mid, Int32 hi, Boolean isNegative, Byte scale) : lo(lo), mid(mid), hi(hi)
	{
		flags = scale;
		if (isNegative) flags = flags | SignMask;
	}

	Decimal::Decimal(Int64 p, Byte point)
	{
		bool isNegative = p < 0;
		p = isNegative ? -p : p;
		lo = p & 0xFFFFFFFF;
		mid = p >> 32;
		hi = 0;
		flags = point << ScaleShift;
		if (isNegative) flags = flags | SignMask;
	}

	Decimal::Decimal(UInt64 p, Byte point)
	{
		lo = p & 0xFFFFFFFF;
		mid = p >> 32;
		hi = 0;
		flags = point << ScaleShift;
	}
	
	Int32 Decimal::CompareTo(const Decimal& obj) const
	{
		// TODO Fix it
		throw NotImplementedException();
	}

	Boolean Decimal::Equals(const Decimal& obj) const
	{
		// TODO Fix it
		throw NotImplementedException();
	}

	String Decimal::ToString() const
	{
		throw NotImplementedException();
	}

	Int32 Decimal::GetHashCode() const
	{
		return static_cast<Int32>(flags ^ hi ^ lo ^ mid);
	}

}