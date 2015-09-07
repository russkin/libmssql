/**
 * @file Employee database proxy class
 */
#pragma once

#include "database/proxy/DBObject.h"
#include "database/proxy/EmployeeTypes.h"


/**
 *	@class Employee CRUD function implementation
 *	Employee database serialization
 */
class DELOPRSQL_API Employee : public DBObject
{
public:
	Employee(){}

	tSQLResult Create	(EmployeeCreateStruct& data);
	tSQLResult Read		(EmployeeReadStruct& data);
	tSQLResult Update	(EmployeeUpdateStruct& data);
	tSQLResult Delete	(EmployeeDeleteStruct& data);
};

