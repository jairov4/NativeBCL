// Test.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include "BCL.h"
#include <iostream>

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
		if (!(value == expectedValue)) throw TestFailedException(String("Value is different of expected: ") + field);
	}

	class TestBasicTypesArith
	{
	public:

		template<typename T>
		void TestUnsigned()
		{			
			auto typeName = typeid(T).name();

			T a = 2;
			T b = 3;
			T c = a + b;
			T d = a + 5;
			T e = b - a;
			T f = a - 1;
			T g = a - b;
			T h = a * b;
			T i = a / b;
			T j = b / a;

			TestAssertTrue(a.Equals(2), String(L"Bad ") + typeName + " assigment or Equals");
			TestAssertTrue(b.Equals(3), String(L"Bad ") + typeName + " assigment or Equals");
			TestAssertTrue(c.Equals(5), String(L"Bad ") + typeName + " addition");
			TestAssertTrue(d.Equals(7), String(L"Bad ") + typeName + " addition");
			TestAssertTrue(e.Equals(1), String(L"Bad ") + typeName + " subtract");
			TestAssertTrue(f.Equals(1), String(L"Bad ") + typeName + " subtract");
			TestAssertTrue(g.Equals(T::MaxValue), String(L"Bad") + typeName + " subtract");
			TestAssertTrue(h.Equals(6), String(L"Bad ") + typeName + " multiply");
			TestAssertTrue(i.Equals(0), String(L"Bad ") + typeName + " divide");
			TestAssertTrue(j.Equals(1), String(L"Bad ") + typeName + " divide");

			T ii = 10;
			T jj = ii++;
			TestAssertTrue(ii.Equals(11), String(L"Bad ") + typeName + " post-increment");
			TestAssertTrue(jj.Equals(10), String(L"Bad ") + typeName + " post-increment");

			ii = 20;
			j = ++ii;
			TestAssertTrue(ii.Equals(21), String(L"Bad ") + typeName + " pre-increment");
			TestAssertTrue(jj.Equals(21), String(L"Bad ") + typeName + " pre-increment");

			ii = 20;
			ii += 2;
			TestAssertTrue(ii.Equals(22), String(L"Bad ") + typeName + " special addition");
			ii -= 2;
			TestAssertTrue(ii.Equals(20), String(L"Bad ") + typeName + " special subtract");
			ii *= 2;
			TestAssertTrue(ii.Equals(40), String(L"Bad ") + typeName + " special multiply");
			ii /= 2;
			TestAssertTrue(ii.Equals(20), String(L"Bad ") + typeName + " special divide");
		}

		template<typename T>
		void TestSigned()
		{			
			auto typeName = typeid(T).name();

			T a = 2;
			T b = 3;
			T c = a + b;
			T d = a + 5;
			T e = b - a;
			T f = a - 1;
			T g = a - b;
			T h(-1);
			T i = h + h;
			T j = a * b;
			T k = a / b;
			T l = b / a;

			TestAssertTrue(a.Equals(2), String(L"Bad ") + typeName + " assigment or Equals");
			TestAssertTrue(b.Equals(3), String(L"Bad ") + typeName + " assigment or Equals");
			TestAssertTrue(c.Equals(5), String(L"Bad ") + typeName + " addition");
			TestAssertTrue(d.Equals(7), String(L"Bad ") + typeName + " addition");
			TestAssertTrue(e.Equals(1), String(L"Bad ") + typeName + " subtract");
			TestAssertTrue(f.Equals(1), String(L"Bad ") + typeName + " subtract");
			TestAssertTrue(g.Equals(-1), String(L"Bad ") + typeName + " subtract");
			TestAssertTrue(h.Equals(-1), String(L"Bad ") + typeName + " subtract");
			TestAssertTrue(i.Equals(-2), String(L"Bad ") + typeName + " subtract");
			TestAssertTrue(j.Equals(6), String(L"Bad ") + typeName + " multiply");
			TestAssertTrue(k.Equals(0), String(L"Bad ") + typeName + " divide");
			TestAssertTrue(l.Equals(1), String(L"Bad ") + typeName + " divide");

			T ii = 10;
			T jj = ii++;
			TestAssertTrue(ii.Equals(11), String(L"Bad ") + typeName + " post-increment");
			TestAssertTrue(jj.Equals(10), String(L"Bad ") + typeName + " post-increment");

			ii = 20;
			j = ++ii;
			TestAssertTrue(ii.Equals(21), String(L"Bad ") + typeName + " pre-increment");
			TestAssertTrue(jj.Equals(21), String(L"Bad ") + typeName + " pre-increment");

			ii = 20;
			ii += 2;
			TestAssertTrue(ii.Equals(22), String(L"Bad ") + typeName + " special addition");
			ii -= 2;
			TestAssertTrue(ii.Equals(20), String(L"Bad ") + typeName + " special subtract");
			ii *= 2;
			TestAssertTrue(ii.Equals(40), String(L"Bad ") + typeName + " special multiply");
			ii /= 2;
			TestAssertTrue(ii.Equals(20), String(L"Bad ") + typeName + " special divide");
		}

		void TestByte()	{ TestUnsigned<Byte>(); }

		void TestSByte() { TestSigned<SByte>(); }

		void TestUInt16() { TestUnsigned<UInt16>(); }

		void TestInt16() { TestSigned<Int16>(); }

		void TestUInt32() { TestUnsigned<UInt32>(); }

		void TestInt32() { TestSigned<Int32>(); }

		void TestUInt64() { TestUnsigned<UInt64>(); }

		void TestInt64() { TestSigned<Int64>(); }
	};

	class TestBasicList
	{
	public:
		void TestList()
		{
			List<String> listOfStrings;
			listOfStrings.Add("Hola mundo");
			listOfStrings.Add("Nunca mas");

			TestAssertEquals<Int32>(listOfStrings.GetCount(), 2, "Bad list implementation");

			int i = 0;
			for (const auto& iter : listOfStrings)
			{
				if (i == 0) TestAssertEquals<String>(iter, "Hola mundo", "iteration");
				if (i == 1) TestAssertEquals<String>(iter, "Nunca mas", "iteration");
				i++;
			}

			TestAssertEquals<String>(listOfStrings[0], "Hola mundo", "iteration");
			TestAssertEquals<String>(listOfStrings[1], "Nunca mas", "iteration");

			TestAssertTrue(listOfStrings.Contains("Hola mundo"), "bad List Contains()");
			TestAssertFalse(listOfStrings.Contains("Non existent item"), "bad List Contains()");

			listOfStrings.SetAt(0, "Nueva cadena");
			TestAssertEquals<String>(listOfStrings.GetAt(0), "Nueva cadena", "bad List SetAt()");
			TestAssertEquals(listOfStrings.GetAt(0), listOfStrings[0], "bad List SetAt()");

			listOfStrings.Clear();
			TestAssertEquals<Int32>(listOfStrings.GetCount(), 0, "Bad List Clear()");
		}
	};

	class TestBasicTypeSize
	{
	public:
		void TestSizes()
		{
			TestAssertEquals(sizeof(Char), 2ull, "bad sizeof(Char)");
			TestAssertEquals(sizeof(Byte), 1ull, "bad sizeof(Byte)");
			TestAssertEquals(sizeof(SByte), 1ull, "bad sizeof(SByte)");
			TestAssertEquals(sizeof(UInt16), 2ull, "bad sizeof(UInt16)");
			TestAssertEquals(sizeof(Int16), 2ull, "bad sizeof(Int16)");
			TestAssertEquals(sizeof(UInt32), 4ull, "bad sizeof(UInt32)");
			TestAssertEquals(sizeof(Int32), 4ull, "bad sizeof(Int32)");
			TestAssertEquals(sizeof(UInt64), 8ull, "bad sizeof(UInt64)");
			TestAssertEquals(sizeof(Int64), 8ull, "bad sizeof(Int64)");
		}
	};
}

int main(int argc, char** argv)
{
	using namespace Test;
		
	TestBasicTypeSize test0;
	TestBasicList test1;
	TestBasicTypesArith test2;

	test0.TestSizes();
	test1.TestList();
	
	test2.TestSByte();
	test2.TestInt16();
	test2.TestInt32();
	test2.TestInt64();

	test2.TestByte();
	test2.TestUInt16();
	test2.TestUInt32();
	test2.TestUInt64();

	return 0;
}