/**
 * $Id: Department.cpp 43 2013-09-04 22:14:56Z russkinnv $
 */
#include "stdafx.h"
#include "database/proxy/department.h"

tSQLResult Department::List(DepartmentListParam& data)
{
	DepartmentListResult output;
	return ExecuteAndRead(data, output);
}

tSQLResult Department::Create(DepartmentCreateParam& data)
{
	return ExecuteAndCheck(data);
}

tSQLResult Department::Purge(DepartmentPurgeParam& data)
{
	return ExecuteAndCheck(data);
}

tSQLResult Department::Read	(DepartmentReadParam& data)
{
	DepartmentReadResult out;
	return ExecuteAndRead(data,out);
}
