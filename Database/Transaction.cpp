/**
 *	$Id: Transaction.cpp 66 2013-09-17 07:23:48Z russkinnv $
 */

#include "StdAfx.h"
#include "Transaction.h"

CTransaction::CTransaction(CDatabase* base) : m_database(base)
{
	ASSERT(m_database);
}

CTransaction::~CTransaction()
{
}

int CTransaction::Begin()
{
	ASSERT(0 != m_database->CanTransact());
	return m_database->BeginTrans() != 0 ? SQL_SUCCESS : SQL_ERROR;
}

int CTransaction::Commit()
{
	return m_database->CommitTrans() != 0 ? SQL_SUCCESS : SQL_ERROR;
}

int CTransaction::Rollback()
{
	return m_database->Rollback() != 0 ? SQL_SUCCESS : SQL_ERROR;
}
