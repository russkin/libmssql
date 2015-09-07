/**
 * $Id: Employee.cpp 41 2013-08-21 04:54:33Z russkinnv $
 */
#include "stdafx.h"
#include "Employee.h"

extern DELOPRSQL_API Database gDataBase;

tSQLResult Employee::Create(EmployeeCreateStruct& data)
{
	data.id		= -1;
	return ExecuteAndCheck(data);
}

tSQLResult Employee::Read(EmployeeReadStruct& data)
{
	EmployeeReadResult	user;
	return ExecuteAndRead(data, user);
}

tSQLResult Employee::Update(EmployeeUpdateStruct& data)
{
	return ExecuteAndCheck(data);
}

tSQLResult Employee::Delete(EmployeeDeleteStruct& data)
{
	return ExecuteAndCheck(data);
}


