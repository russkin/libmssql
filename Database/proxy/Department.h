/**
 * @file Department database proxy class
 */
#pragma once

#include "database/proxy/DBObject.h"
#include "database/proxy/DepartmentTypes.h"

/**
 *	@class Department CRUD function implementation
 *	Department database serialization
 */
class DELOPRSQL_API Department : public DBObject
{
public:
	Department(){}

	tSQLResult List		(DepartmentListParam& data);
	tSQLResult Create	(DepartmentCreateParam& data);
	tSQLResult Purge 	(DepartmentPurgeParam& data);
	tSQLResult Read		(DepartmentReadParam& data);
/*
	tSQLResult Update	(EmployeeUpdateStruct& data);
	tSQLResult Delete	(EmployeeDeleteStruct& data);
*/
};