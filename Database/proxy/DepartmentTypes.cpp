/**
 * $Id: DepartmentTypes.cpp 66 2013-09-17 07:23:48Z russkinnv $
 */
#include "stdafx.h"
#include "database/proxy/DepartmentTypes.h"

IMPLEMENT_INPUT_PARAM(DepartmentListParam,		_T("delopr_Get_Sprav_Sotrudn(?,?,?,?,?,?)"))
IMPLEMENT_INPUT_PARAM(DepartmentCreateParam,	_T("delopr_Create_Podrazd(?,?,?,?,?,?)"))
IMPLEMENT_INPUT_PARAM(DepartmentCheck,			_T("delopr_Check_Podrazd(?)"))
IMPLEMENT_INPUT_PARAM(DepartmentPurgeParam,		_T("delopr_Purge_Podrazd(?)"))
IMPLEMENT_INPUT_PARAM(DepartmentReadParam,		_T("delopr_Get_Podrazd_Load(?)"))

typedef ParameterizedRecordSet<DepartmentListParam>		ReadDepartmentList;
typedef ParameterizedRecordSet<DepartmentReadParam>		ReadDepartmentRS;
typedef ParameterizedRecordSet<DepartmentCheck>			DepartmentCheckRS;


FIELDEXCHANGE(DepartmentListParam)
{
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Int(pFX, _T("d"), data.iDay);
	RFX_Int(pFX, _T("m"), data.iMonth);
	RFX_Int(pFX, _T("y"), data.iYear);
	RFX_Long(pFX, _T("podr"), data.lDepartment);
	RFX_Long(pFX, _T("flag"), data.lFlag);
	RFX_Long(pFX, _T("organiz"), data.lOrg);
}


FIELDEXCHANGE(DepartmentCheck)
{
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Long(pFX, _T("id"), data.id);
}

FIELDEXCHANGE(DepartmentCreateParam)
{
	pFX->SetFieldType(CFieldExchange::inoutParam);
	RFX_Long(pFX,	_T("id"),		data.lID);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Long(pFX,	_T("podrazd"),	data.lParent);
	RFX_Text(pFX,	_T("name"),		data.sDepartment);
	RFX_Text(pFX,	_T("comment"),	data.sNote);
	RFX_Double(pFX, _T("w"),		data.fWeight);
	RFX_Long(pFX,	_T("organiz"),	data.lOrg);
}


FIELDEXCHANGE(DepartmentPurgeParam)
{
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Long(pFX, _T("id"), data.lID);
}


FIELDEXCHANGE(DepartmentReadParam)
{
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Long(pFX, _T("id"), data.lID);
}

READRECORDSET(DepartmentCheckRS, ErrorData)
{
	return Read(*(dynamic_cast<RecordSet*>(&rs)), data);
}

READRECORDSET(ReadDepartmentRS, DepartmentReadResult)
{
	try{
		while (!rs.IsEOF())
		{
			data.lParent	= rs.GetFieldValueT<long>(0);
			data.sParent	= rs.GetFieldValueT<CString>(1);
			data.sName		= rs.GetFieldValueT<CString>(2);
			data.fWeight	= rs.GetFieldValueT<double>(3);
			data.sNote		= rs.GetFieldValueT<CString>(4);
			data.lOrg		= rs.GetFieldValueT<long>(5);
			
			if (data.cb)
				data.cb->OnData(&data);
			rs.MoveNext();
		}
	} catch(CDBException* e) {
		rs.BuildError(e);
		return SQL_ERROR;
	}
	return SQL_SUCCESS;
}

READRECORDSET(ReadDepartmentList, DepartmentListResult)
{
	try{
		while (!rs.IsEOF())
		{
			data.lParent		= rs.GetFieldValueT<long>(0);
			data.sParent		= rs.GetFieldValueT<CString>(1);
			data.lID			= rs.GetFieldValueT<long>(2);
			data.sName			= rs.GetFieldValueT<CString>(3);
			data.bIsDepartment	= rs.GetFieldValueT<BOOL>(4);
			data.lPosition		= rs.GetFieldValueT<long>(5);
			data.sPosition		= rs.GetFieldValueT<CString>(6);
			data.lLevel			= rs.GetFieldValueT<long>(7);
			data.lOrg			= rs.GetFieldValueT<long>(8);
			
			if (data.cb)
				data.cb->OnData(&data);
			rs.MoveNext();
		}
	} catch(CDBException* e) {
		rs.BuildError(e);
		return SQL_ERROR;
	}
	return SQL_SUCCESS;
}
