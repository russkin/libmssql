/**
 * $Id: EmployeeTypes.cpp 70 2013-09-19 01:08:28Z maltsevao $
 */
#include "stdafx.h"
#include "database/proxy/EmployeeTypes.h"

IMPLEMENT_INPUT_PARAM(EmployeeCreateStruct,	_T("Delopr_Create_Sotrudn(?,?)"))
IMPLEMENT_INPUT_PARAM(EmployeeReadStruct,	_T("Delopr_Get_Sotrudn_Load(?)"))
IMPLEMENT_INPUT_PARAM(EmployeeDeleteStruct,	_T("Delopr_Delete_Users(?)"))
IMPLEMENT_INPUT_PARAM(EmployeeCheckStruct,	_T("Delopr_Check_Users(?)"))


FIELDEXCHANGE(EmployeeCreateStruct)
{
	pFX->SetFieldType(CFieldExchange::inoutParam);
	RFX_Long(pFX, _T("id"), data.id);
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Text(pFX, _T("name"), data.sName);
}

FIELDEXCHANGE(EmployeeReadStruct)
{
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Long(pFX, _T("id"), data.id);
}

FIELDEXCHANGE(EmployeeDeleteStruct)
{
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Long(pFX, _T("id"), data.id);
}

FIELDEXCHANGE(EmployeeCheckStruct)
{
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Long(pFX, _T("id"), data.id);
}



template <> int DataReader::Read(ReadEmployeeRS& rs, EmployeeReadResult& data)
//READRECORDSET(ReadEmployeeRS, EmployeeReadResult)
{
	try{
		data.sName	= rs.GetFieldValueT<CString>(0);
		data.lOrg	= rs.GetFieldValueT<long>(1);
		data.sOrg	= rs.GetFieldValueT<CString>(2);

		if (data.cb)
			data.cb->OnData(data);

		rs.MoveNextRecordSet(); 

		while (!rs.IsEOF())
		{
			data.lDv		= rs.GetFieldValueT<long>(0);
			data.sDep		= rs.GetFieldValueT<CString>(1);
			data.sPos		= rs.GetFieldValueT<CString>(2);
			data.sDateStart	= rs.GetFieldValueT<CString>(3);
			data.sDateEnd	= rs.GetFieldValueT<CString>(4);
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

READRECORDSET(ParameterizedRecordSet<EmployeeCheckStruct>, ErrorData)
{
	return DataReader::Read<ReadErrorRS,ErrorData>( reinterpret_cast<ReadErrorRS&>(rs), data);
}


