#include "BCL.h"

namespace System
{	
	#include <stdint.h>

	String Object::ToString() const
	{
		return typeid(*this).name();
	}

	Int32 Object::GetHashCode() const
	{
		return reinterpret_cast<intptr_t>(this) & 0xFFFFFFFF;
	}

	Type Object::GetType() const
	{
		return typeid(this);
	}
}