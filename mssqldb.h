#pragma once
#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <string>

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

using namespace std;

class mssqldb
{
private:
	SQLHANDLE sqlConnHandle = NULL;
	SQLHANDLE sqlStmtHandle = NULL;
	SQLHANDLE sqlEnvHandle = NULL;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
	int query(SQLHANDLE sqlStmtHandle, wstring query);


public:
	const int DBERROR = 1;
	int connect(wstring login, wstring password);
	int doquery(wstring query)
	{
		return this->query(sqlStmtHandle, query);
	}
};

