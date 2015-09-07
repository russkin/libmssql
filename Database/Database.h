/**
 * @file Database connection
 * $Id: Database.h 33 2013-08-15 06:33:35Z russkinnv $
 */

#pragma once

#include <afxdb.h>
#include "Delopr.SQL/Delopr.SQL.h"

class DELOPRSQL_API Database
{
public:
	Database();
	~Database();

	tSQLResult Open(LPCTSTR lpszConnectString);
	tSQLResult Close();
	tSQLResult Exec(const SQLCHAR* StatementText) const;

	CDatabase& instance(); // TODO: remove this after migration

private:
	CDatabase m_base;
};


extern DELOPRSQL_API Database gDataBase;