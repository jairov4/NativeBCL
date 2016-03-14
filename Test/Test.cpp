// Test.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "BCL.h"

using namespace System;
using namespace System::Collections;

namespace Test
{
	class TestFailedException : public Exception
	{
	public:
		TestFailedException(String str) : Exception(str){}
	};

	void TestAssertTrue(bool expr, String msg)
	{
		if (!expr) throw TestFailedException(msg);
	}

	void TestAssertFalse(bool expr, String msg)
	{
		if (expr) throw TestFailedException(msg);
	}

	template<typename T>
	void TestAssertEquals(const T& value, const T& expectedValue, String field)
	{
		if (!(value == expectedValue)) throw TestFailedException(String(u"Value is different of expected: ") + field);
	}

	class TestBasicList
	{
	public:
		void TestList()
		{
			List<String> listOfStrings;
			listOfStrings.Add(u"Hola mundo");
			listOfStrings.Add(u"Nunca mas");
			listOfStrings.Add(u"Nunca jamas");

			TestAssertEquals<int32_t>(listOfStrings.GetCount(), 3, u"Bad list implementation");

			int i = 0;
			for (auto iter = listOfStrings.GetGenericEnumerator(); iter->IsValid(); iter->MoveNext())
			{
				if (i == 0) TestAssertEquals<String>(iter->GetCurrent(), u"Hola mundo", u"iteration");
				if (i == 1) TestAssertEquals<String>(iter->GetCurrent(), u"Nunca mas", u"iteration");
				if (i == 2) TestAssertEquals<String>(iter->GetCurrent(), u"Nunca jamas", u"iteration");
				i++;
			}

			TestAssertEquals<String>(listOfStrings[0], u"Hola mundo", u"iteration");
			TestAssertEquals<String>(listOfStrings[1], u"Nunca mas", u"iteration");

			TestAssertTrue(listOfStrings.Contains(u"Hola mundo"), u"bad List Contains()");
			TestAssertFalse(listOfStrings.Contains(u"Non existent item"), u"bad List Contains()");

			listOfStrings.SetAt(0, u"Nueva cadena");
			TestAssertEquals<String>(listOfStrings[0], u"Nueva cadena", u"bad List SetAt()");
			
			listOfStrings.Clear();
			TestAssertEquals<int32_t>(listOfStrings.GetCount(), 0, u"Bad List Clear()");
		}
	};	
}

int __cdecl main(int argc, char** argv)
{
	using namespace Test;

	TestBasicList test1;

	test1.TestList();
	
	return 0;
}