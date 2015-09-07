#include "stdafx.h"
#include "Environment.h"
#include "database/dsn.h"
#include "database/database.h"

extern DELOPRSQL_API DSN gDSN;

Environment::Environment()
{
}

Environment::~Environment()
{
}


void Environment::SetUp()
{
	gDataBase.Open(gDSN.GetName());
}
void Environment::TearDown()
{
	gDataBase.Close();
}
