#include "BCL.h"

using namespace System;

SByte::SByte() : value(0)
{
}

SByte::SByte(sbyte value) : value(value)
{
}

SByte::SByte(const SByte& obj) : value(obj.value)
{
}

SByte::operator sbyte() const
{
	return value;
}

uint32_t SByte::GetHashCode() const
{
	return value;
}


Byte::Byte() : value(0)
{
}

Byte::Byte(byte value) : value(value)
{
}

Byte::Byte(const Byte& obj) : value(obj.value)
{
}

Byte::operator byte() const
{
	return value;
}

uint32_t Byte::GetHashCode() const
{
	return value;
}
