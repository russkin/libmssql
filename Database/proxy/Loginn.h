#pragma once


#include "database/proxy/DBObject.h"
#include "database/proxy/LoginnTypes.h"


class DELOPRSQL_API Loginn : public DBObject
{
public:
	Loginn(){}

	tSQLResult Read		(LoginnReadStruct& data);
};

