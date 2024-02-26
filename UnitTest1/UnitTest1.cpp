#include "pch.h"
#include "CppUnitTest.h"
#include "../mssqldb.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			mssqldb db;
			std::wstring login = L"sa";
			std::wstring password = L"ssl-2000";
			Assert::AreEqual(db.connect(login, password), 0);
		}
	};
}
