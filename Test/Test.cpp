// Test.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include "BCL.h"
#include <iostream>

using namespace System;
using namespace System::Collections;

class SimpleTestClass : public Object
{
public:
	int algo;
};

int main(int argc, char** argv)
{
	SByte s = argc;
	SByte a = s + s;
	// internal unicode strings
	String str("hola");
	String str2(L"hola");
	String str3 = "sdsdf";
	Int32 srr = (Byte)4;
	Int32 srr2 = (short)22;
	Int32 srr3 = a;
	String hh = argv[0];

	List<String> listOfStrings;
	listOfStrings.Add("Hola mundo");
	listOfStrings.Add("Nunca mas");

	// automatic but deterministic garbage collection
	List<ref<SimpleTestClass>> listOfCO;
	listOfCO.Add(std::make_shared<SimpleTestClass>());
	listOfCO.Add(std::make_shared<SimpleTestClass>());
	listOfCO.Add(new_ref<SimpleTestClass>());

	auto i1 = sizeof(Int64);
	auto i2 = sizeof(Int32);
	auto i3 = sizeof(Char);

	for (auto& item : listOfCO)
	{
		std::wcout << (std::wstring)item->ToString() << std::endl;
	}

	Dictionary<String, Int32> dict;
	dict.Add("hola", 23);
	dict.Add("mundo", 24);

	for (auto& pair : dict)
	{
		std::wcout << (std::wstring)pair.GetKey() << " " << pair.GetValue() << std::endl;
	}

	return a + str.GetLength() + listOfStrings.GetCount();
}
