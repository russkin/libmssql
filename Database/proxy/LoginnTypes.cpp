#include "stdafx.h"
#include "database/proxy/LoginnTypes.h"

IMPLEMENT_INPUT_PARAM(LoginnReadStruct,	_T("sp_show_list_ad_logins"))

FIELDEXCHANGE(LoginnReadStruct)
{
}

template <> int DataReader::Read(ReadLoginnRS& rs, LoginnReadResult& data)
//READRECORDSET(ReadEmployeeRS, EmployeeReadResult)
{
	try{
		while (!rs.IsEOF())
		{
			data.sName		= rs.GetFieldValueT<CString>(0);
			data.sLogin		= rs.GetFieldValueT<CString>(1);
			data.sDep		= rs.GetFieldValueT<CString>(2);
			data.sPhone		= rs.GetFieldValueT<CString>(3);
			if (data.cb)
				data.cb->OnRow(data);
			rs.MoveNext();
		}
	} catch(CDBException* e) {
		rs.BuildError(e);
		return SQL_ERROR;
	}
	return SQL_SUCCESS;
}

READRECORDSET(ParameterizedRecordSet<LoginnCheckStruct>, ErrorData)
{
	return DataReader::Read<ReadErrorRS,ErrorData>( reinterpret_cast<ReadErrorRS&>(rs), data);
}
