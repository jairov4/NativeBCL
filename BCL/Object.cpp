#include "BCL.h"

namespace System
{	
	#include <stdint.h>
	#include <cuchar>
	#include <string>

	static std::u16string StringtoU16(std::string str)
	{
		const size_t si = strlen(str.c_str());
		char16_t cstr[si + 1];
		memset(cstr, 0, (si + 1)*sizeof(char16_t));
		const char* constSTR = str.c_str();
		mbstate_t mbs;
		memset(&mbs, 0, sizeof(mbs));//set shift state to the initial state
		size_t ret = mbrtoc16(cstr, constSTR, si, &mbs);
		std::u16string wstr(cstr);
		return wstr;
	}

	String Object::ToString() override
	{
		return StringtoU16(typeid(*this).name());
	}

    bool Object::Equals(Object & obj)
    {
        return this == &obj;
    }

	Int32 Object::GetHashCode() override
	{
		return reinterpret_cast<intptr_t>(this) & 0xFFFFFFFF;
	}
}