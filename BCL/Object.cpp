#include "BCL.h"

namespace System
{	
	String Object::ToString() const
	{
		return typeid(*this).name();
	}

	Int32 Object::GetHashCode() const
	{
		return reinterpret_cast<int>(this);
	}

	Type Object::GetType() const
	{
		return typeid(this);
	}
}