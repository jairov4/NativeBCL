#include "BCL.h"

namespace System
{
	Boolean Object::Equals(const Object& obj) const
	{
		return this == &obj;
	}

	String Object::ToString() const
	{
		return typeid(*this).name();
	}

	Int32 Object::GetHashCode() const
	{
		return reinterpret_cast<int>(this);
	}
}