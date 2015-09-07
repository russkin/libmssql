#include "StdAfx.h"
#include "RecordSet.h"

RecordSet::RecordSet(CDatabase* pDatabase) 
	: CRecordset(pDatabase)
	, m_bExecuteOnly(false)
{
}

RecordSet::~RecordSet()
{
}


void RecordSet::MoveNext()
{
	__super::MoveNext();
}

void RecordSet::Close()
{
	__super::Close();
}

BOOL RecordSet::IsEOF() const
{
	return __super::IsEOF();
}


void RecordSet::MoveNextRecordSet()
{
	FlushResultSet(); 
	AllocAndCacheFieldInfo();
	MoveNext(); 
}

void RecordSet::AllocAndCacheFieldInfo() 
{
	m_nResultCols = -1;
	if(m_rgODBCFieldInfos != NULL)
	{
		delete [] m_rgODBCFieldInfos;
		m_rgODBCFieldInfos = NULL;
	}

	__super::AllocAndCacheFieldInfo();
}

void RecordSet::BuildError(const CDBException* ex)
{
	m_error.Format("%s (SQLError:%d)", ex->m_strError, ex->m_nRetCode);
}										   

const CString& RecordSet::GetError() const
{
	return m_error;
}

void RecordSet::Move(long nRows, WORD wFetchType)
{
	if (!m_bExecuteOnly)
		CRecordset::Move(nRows, wFetchType);
}

