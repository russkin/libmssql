#include "stdafx.h"
#include "database/Delopr.SQL/DBError.h"

void DBError::Add(const DBError::Error& err)
{
	m_Error.push_back(err);
}

