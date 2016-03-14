#include "BCL.h"
#include <locale>
#include <codecvt>

namespace System
{
	using namespace std;

	template <typename T>
	void fromUTF8(const string& source, basic_string<T, char_traits<T>, allocator<T>>& result)
	{
		wstring_convert<codecvt_utf8_utf16<T>, T> convertor;
		result = convertor.from_bytes(source);
	}

	String Object::ToString() const
	{
		auto str = string(typeid(*this).name());
		u16string res;
		fromUTF8(str, res);
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