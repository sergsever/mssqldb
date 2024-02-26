#include "mssqldb.h"
#include <sstream>
#include <wchar.h>

class mssqldb;

int mssqldb::connect(wstring login, wstring password)
{
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		return mssqldb::DBERROR;
	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		return mssqldb::DBERROR;
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		return mssqldb::DBERROR;
	std::wstringstream ss;
	//ss << "DRIVER = {SQL Server}; SERVER = localhost,1433;DATABASE=master;" << "UID=" << login << ";PWD= " << password << ";";
	wstring connection_string = L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;" + wstring(L"UID=") + login + wstring(L";PWD=") + password + wstring(L";");
//	wstring connection_string = L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=sa;PWD=ssl-2000;";
	SQLWCHAR* conn_str = (SQLWCHAR*)connection_string.c_str();
	switch (SQLDriverConnect(sqlConnHandle,
		NULL, conn_str,
		//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost,1433, 1433;DATABASE=master;UID=sa;PWD=ssl-2000;",
		//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;Trusted=true;",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {
	case SQL_SUCCESS:
		cout << "Successfully connected to SQL Server";
		return 0;
		cout << "\n";
		break;
	case SQL_SUCCESS_WITH_INFO:
		cout << "Successfully connected to SQL Server";
		return 0;
		cout << "\n";
		break;
	case SQL_INVALID_HANDLE:
		cout << "Could not connect to SQL Server:invalid handle.";
		cout << "\n";
		return mssqldb::DBERROR;
	case SQL_ERROR:
		cout << "Could not connect to SQL Server:sql error.";
		cout << retconstring;
		cout << "\n";
		return mssqldb::DBERROR;
	default:
		break;
	}
	return 0;

}

int mssqldb::query(SQLHANDLE sqlStmtHandle, wstring query)
{
	SQLCHAR result[1024];
	SQLLEN counter;


	SQLWCHAR* wcquery = (SQLWCHAR*)query.c_str();
	if (SQLAllocHandle(SQL_HANDLE_STMT, this->sqlConnHandle, &sqlStmtHandle) != SQL_SUCCESS)
		return DBERROR;

	if (SQLExecDirect(sqlStmtHandle, wcquery, SQL_NTS) != SQL_SUCCESS)
	{
		return mssqldb::DBERROR;
	}
	else{
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, result, 1024, &counter);
	}

	cout << "result: " << result;


	return 0;
}
