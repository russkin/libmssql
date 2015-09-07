#pragma once

#include "Delopr.SQL/Delopr.SQL.h"

class CDatabase;
/**
 *	@class CTransaction
 *  Класс, обеспечивающий транзакционную целостность операций Delete+Check/Update+Check
 */
class DELOPRSQL_API CTransaction
{
public:
	CTransaction(CDatabase* base);
	~CTransaction();

	int Begin();
	int	Commit();
	int Rollback();

private:
	CDatabase*	m_database;
};
