#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "mssqldb.h"

BOOST_AUTO_TEST_SUITE(mssqldb_test)

namespace unit
{
	BOOST_AUTO_TEST_CASE(mssqldb_connect) {
		mssqldb db;
		std::wstring login = L"sa";
		std::wstring password = L"ssl-2000";
		BOOST_TEST(db.connect(login, password) == 0);
		BOOST_TEST(db.doquery(wstring(L"SELECT @@VERSION")) == 0);

	}
/*
	BOOST_AUTO_TEST_CASE(mssqldb_query) {
		mssqldb db;
		std::wstring login = L"sa";
		std::wstring password = L"ssl-2000";
		db.connect(login, password);
		BOOST_TEST(db.doquery(wstring(L"SELECT @@VERSION")) == 0);
	}*/
}
}