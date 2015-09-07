/**
 * @file database connection interface
 * $Id: Database.cpp 47 2013-09-09 04:00:40Z russkinnv $
 */
#include "stdafx.h"
#include "Database.h"

DELOPRSQL_API Database gDataBase;
// TODO : migrate to Database class or create new instance for each SQL query
DELOPRSQL_API HSTMT hstmt;

Database::Database(void)
{
}

Database::~Database(void)
{
}


tSQLResult Database::Open(LPCTSTR lpszConnectString)
{
	int result = SQL_ERROR;
	try
	{
		result = SQL_SUCCESS == m_base.OpenEx(lpszConnectString,CDatabase::noOdbcDialog);
		if ( SQL_SUCCESS == result)
			result = SQL_SUCCESS != SQLAllocStmt(m_base.m_hdbc,&hstmt);
	}
	catch(CDBException* e)
	{
		result = SQL_ERROR;
	}
		
	return result;
}

tSQLResult Database::Close()
{
	m_base.Close();
	return SQL_SUCCESS;
}

CDatabase& Database::instance()
{
	return m_base;
}


tSQLResult Database::Exec(const SQLCHAR* StatementText) const
{
	return SQLExecDirect(hstmt,const_cast<SQLCHAR*>(StatementText), SQL_NTS);
}