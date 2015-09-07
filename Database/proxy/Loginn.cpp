#include "stdafx.h"
#include "database/proxy/Loginn.h"



extern DELOPRSQL_API Database gDataBase;

tSQLResult Loginn::Read(LoginnReadStruct& data)
{
	LoginnReadResult	user;
	return ExecuteAndRead(data, user);
}
