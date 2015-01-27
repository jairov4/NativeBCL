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
		if (!(value == expectedValue)) throw TestFailedException(String(L"Value is different of expected: ") + field);
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
			jj = ++ii;
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
			jj = ++ii;
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

		void TestString()
		{
			String str(L"Hola mundo");
			printf("%d", str.GetLength());
		}
	};

	class TestBasicList
	{
	public:
		void TestList()
		{
			List<String> listOfStrings;
			listOfStrings.Add(L"Hola mundo");
			listOfStrings.Add(L"Nunca mas");

			TestAssertEquals<Int32>(listOfStrings.GetCount(), 2, L"Bad list implementation");

			int i = 0;
			for (const auto& iter : listOfStrings)
			{
				if (i == 0) TestAssertEquals<String>(iter, L"Hola mundo", L"iteration");
				if (i == 1) TestAssertEquals<String>(iter, L"Nunca mas", L"iteration");
				i++;
			}

			TestAssertEquals<String>(listOfStrings[0], L"Hola mundo", L"iteration");
			TestAssertEquals<String>(listOfStrings[1], L"Nunca mas", L"iteration");

			TestAssertTrue(listOfStrings.Contains(L"Hola mundo"), L"bad List Contains()");
			TestAssertFalse(listOfStrings.Contains(L"Non existent item"), L"bad List Contains()");

			listOfStrings.SetAt(0, L"Nueva cadena");
			TestAssertEquals<String>(listOfStrings.GetAt(0), L"Nueva cadena", L"bad List SetAt()");
			TestAssertEquals(listOfStrings.GetAt(0), listOfStrings[0], L"bad List SetAt()");

			listOfStrings.Clear();
			TestAssertEquals<Int32>(listOfStrings.GetCount(), 0, L"Bad List Clear()");
		}
	};

	class TestBasicTypeSize
	{
	public:
		void TestSizes()
		{
			TestAssertEquals(sizeof(Char), 2ull, L"bad sizeof(Char)");
			TestAssertEquals(sizeof(Byte), 1ull, L"bad sizeof(Byte)");
			TestAssertEquals(sizeof(SByte), 1ull, L"bad sizeof(SByte)");
			TestAssertEquals(sizeof(UInt16), 2ull, L"bad sizeof(UInt16)");
			TestAssertEquals(sizeof(Int16), 2ull, L"bad sizeof(Int16)");
			TestAssertEquals(sizeof(UInt32), 4ull, L"bad sizeof(UInt32)");
			TestAssertEquals(sizeof(Int32), 4ull, L"bad sizeof(Int32)");
			TestAssertEquals(sizeof(UInt64), 8ull, L"bad sizeof(UInt64)");
			TestAssertEquals(sizeof(Int64), 8ull, L"bad sizeof(Int64)");
		}
	};

	class TestBasicDateTime
	{
	public:
		void TestBasic()
		{
			auto r = DateTime::GetNow();
			TestAssertEquals(r.GetKind(), DateTimeKind::Local, L"Bad DateTimeKind of Now");
			r = DateTime::GetUtcNow();
			TestAssertEquals(r.GetKind(), DateTimeKind::Utc, L"Bad DateTimeKind of UtcNow");
			r = DateTime(2015, 1, 12, 5, 10, 3, 145);
			TestAssertEquals(r.GetKind(), DateTimeKind::Unspecified, L"Bad DateTimeKind of ctor without Kind");
			TestAssertEquals<Int32>(r.GetYear(), 2015, L"Bad year");
			TestAssertEquals<Int32>(r.GetMonth(), 1, L"Bad month");
			TestAssertEquals<Int32>(r.GetDay(), 12, L"Bad day");
			TestAssertEquals<Int32>(r.GetHour(), 5, L"Bad hour");
			TestAssertEquals<Int32>(r.GetMinute(), 10, L"Bad minute");
			TestAssertEquals<Int32>(r.GetSecond(), 3, L"Bad second");
			TestAssertEquals<Int32>(r.GetMillisecond(), 145, L"Bad millisecond");
		}

		void TestBasicOffset()
		{
			auto r = DateTimeOffset::GetNow();
			r = DateTimeOffset::GetUtcNow();
			r = DateTimeOffset(DateTime(2015, 1, 12, 5, 10, 3, 145), TimeSpan(-5, 0, 0));			
			TestAssertEquals<Int32>(r.GetYear(), 2015, L"Bad year");
			TestAssertEquals<Int32>(r.GetMonth(), 1, L"Bad month");
			TestAssertEquals<Int32>(r.GetDay(), 12, L"Bad day");
			TestAssertEquals<Int32>(r.GetHour(), 5, L"Bad hour");
			TestAssertEquals<Int32>(r.GetMinute(), 10, L"Bad minute");
			TestAssertEquals<Int32>(r.GetSecond(), 3, L"Bad second");
			TestAssertEquals<Int32>(r.GetMillisecond(), 145, L"Bad millisecond");
		}

		void TestBasicArith()
		{
			auto r = DateTime(2015, 1, 12, 5, 10, 3, 145);

			r = r.AddYears(1);
			TestAssertEquals<Int32>(r.GetYear(), 2016, L"Bad year");

			r = r.AddMonths(1);
			TestAssertEquals<Int32>(r.GetMonth(), 2, L"Bad month");

			r = r.AddDays(1);
			TestAssertEquals<Int32>(r.GetDay(), 13, L"Bad day");

			r = r.AddHours(1);
			TestAssertEquals<Int32>(r.GetHour(), 6, L"Bad hour");

			r = r.AddMinutes(1);
			TestAssertEquals<Int32>(r.GetMinute(), 11, L"Bad minute");

			r = r.AddSeconds(1);
			TestAssertEquals<Int32>(r.GetSecond(), 4, L"Bad second");

			r = r.AddMilliseconds(1);
			TestAssertEquals<Int32>(r.GetMillisecond(), 146, L"Bad millisecond");
		}
	};
}

int main(int argc, char** argv)
{
	using namespace Test;

	TestBasicTypeSize test0;
	TestBasicList test1;
	TestBasicTypesArith test2;
	TestBasicDateTime test3;

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

	test2.TestString();

	test3.TestBasic();
	test3.TestBasicArith();

	return 0;
}