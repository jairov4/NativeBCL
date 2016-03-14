#include "BCL.h"

using namespace System;

SByte::SByte() : value(0)
{
}

System::SByte::SByte(sbyte value) : value(value)
{
}

SByte::SByte(const SByte& obj) : value(obj.value)
{
}

System::SByte::operator sbyte()
{
    return value;
}

uint32_t System::SByte::GetHashCode()
{
    return value;
}

String System::SByte::ToString()
{
    return u"";
}
