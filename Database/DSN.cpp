/**
$Id: DSN.cpp 46 2013-09-09 01:50:07Z russkinnv $
*/

#include "stdafx.h"
#include <atlstr.h>
#include <ODBCINST.H>
#include "dsn.h"

#define DRIVER "SQL Server"

LPCTSTR DSN::GetName()	const
{
	return m_description;
}

void DSN::prepareConnectionString(CString& connectionString) const
{
	LPSTR szAttributes = connectionString.GetBuffer();
	for(int i = 0; i < connectionString.GetLength(); ++i)
		if(*(szAttributes+i)==(int) '/')
			*(szAttributes+i)=NULL;
}

tSQLResult	DSN::Create() const
{
	CString tmpStr;
	tmpStr.Format( m_format, m_description, m_description, m_server, m_database);
	prepareConnectionString(tmpStr);

	if(!SQLConfigDataSource(NULL, ODBC_ADD_DSN, DRIVER, tmpStr.GetBuffer()))
		if(!SQLConfigDataSource(NULL, ODBC_CONFIG_DSN, DRIVER, tmpStr.GetBuffer()))
			return SQL_ERROR;

	return SQL_SUCCESS;
}

tSQLResult DSN::Delete() const
{
	CString str;
	str.Format( "%s%c", m_description, 0);
	return SQLConfigDataSource(NULL,ODBC_REMOVE_DSN,DRIVER,str) ? SQL_SUCCESS : SQL_ERROR;
}

LPCTSTR DSN::GetDatabase()	const
{
	return m_database;
}
