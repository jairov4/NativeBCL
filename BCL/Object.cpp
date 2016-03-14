#include "BCL.h"
#include <cuchar>

namespace System
{
	using namespace std;

	u16string string_to_u16string(const string& str)
	{
		u16string result;
		auto ptr = str.data();
		auto end = str.data() + str.size();
		char16_t c16;
		mbstate_t state {};
		while (auto rc = mbrtoc16(&c16, ptr, end - ptr, &state))
		{
			if (rc <= 0) 
			{
				break;
			}

			result.push_back(c16);
			ptr += rc;
		}

		return result;
	}

	String Object::ToString() const
	{
		auto str = string(typeid(*this).name());
		auto res = string_to_u16string(str);
		return res;
	}

	bool Object::Equals(const Object & obj) const
	{
		return this == &obj;
	}

	uint32_t Object::GetHashCode() const
	{
		return reinterpret_cast<intptr_t>(this) & 0xFFFFFFFF;
	}
}