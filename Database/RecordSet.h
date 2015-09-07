/**
 * @file SQL record set 
 * $Id: RecordSet.h 72 2013-09-20 04:34:01Z russkinnv $
 */
#pragma once

#include "Delopr.SQL/Delopr.SQL.h"
#include "Delopr.SQL/util.h"

/**
 * Extended CRecordset
 * @see MoveNextRecordSet
 * @see GetFieldValueT
 */
class DELOPRSQL_API RecordSet : protected CRecordset
{
public:
	RecordSet(CDatabase* pDatabase = NULL);
	virtual ~RecordSet();

	/**	Go to next recordset (for multiple recordset result) */
	void MoveNextRecordSet();
	void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE);
	void MoveNext();
	virtual void Close();
	BOOL IsEOF() const;

	/** Get field value by field index
	 *	@return field value by field sequence number
	 */
	template <typename T>
	T GetFieldValueT(short nIndex)
	{
		Converter	converter;
		CDBVariant	varValue;

		CRecordset::GetFieldValue((short)nIndex, varValue);
		return converter.GetData<T>(varValue);
	}

	const CString& GetError() const;
	void BuildError(const CDBException* ex);

protected:
	/**
	 * Custom allocator
	 * @see MoveNextRecordSet
	 */
	void AllocAndCacheFieldInfo();


protected:
	CString	m_error;
	bool	m_bExecuteOnly;
};

