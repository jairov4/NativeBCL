#include "BCL.h"

namespace System
{
	using namespace std;

	Type::Type(const type_info& info) : info(info)
	{	
	}

	Type::Type(const Type& info) : info(info.info)
	{
	}

	String Type::GetName() const
	{
		return info.name();
	}

	String Type::ToString() const
	{
		return GetName();
	}

	Int32 Type::GetHashCode() const
	{
		return (std::int32_t)info.hash_code();
	}
	
	Boolean Type::Equals(const Type& other) const
	{
		return info == other.info;
	}

	Boolean Type::operator==(const Type& other) const
	{
		return info == other.info;
	}

}