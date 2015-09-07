#pragma once

#include "Delopr.SQL/Delopr.SQL.h"

class CDatabase;
/**
 *	@class CTransaction
 *  �����, �������������� �������������� ����������� �������� Delete+Check/Update+Check
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
