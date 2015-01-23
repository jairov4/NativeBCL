#pragma once

#include "BCL.h"

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
	listOfCO.Add(new_ref<SimpleTestClass>());
	listOfCO.Add(new_ref<SimpleTestClass>());
	listOfCO.Add(new_ref<SimpleTestClass>());

	auto i1 = sizeof(Int64);
	auto i2 = sizeof(Int32);
	auto i3 = sizeof(Char);
	
	for (auto& item : listOfCO)
	{
		
	}

	IReadOnlyCollection<ref<SimpleTestClass>>& noCast = listOfCO;

	Dictionary<String, Int32> dict;
	dict.Add("hola", 23);
	dict.Add("mundo", 24);

	for (auto& pair : dict)
	{
		
	}

	return a + str.GetLength() + listOfStrings.GetCount();
}
