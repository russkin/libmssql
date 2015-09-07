#pragma once

#include "database/ParameterizedRecordSet.h"
#include "database/proxy/error.h"

/**
 *	Callback ��� ���������/����������� ����������� �������
 */
template <typename T>
struct EmployeeCallback
{
	virtual void OnData(const T&){}	/**< ����� ���������� � ������������				*/
	virtual void OnRow(const T&){}	/**< ���������� �� ����� ����������� ������������	*/
};

/**
 * @class EmployeeReadResult
 * ���������� � ������������� ������������ ����� ������������ ���������������
 */
struct EmployeeReadResult
{
	EmployeeReadResult() : cb(NULL){}

	typedef EmployeeCallback<EmployeeReadResult>	DataCallback;

	DataCallback*	cb;
	long			lOrg;		/**< ID �����������		*/
	long			lDv;		/**< ID "��������"		*/
	CString			sName;		/**< ��� ������������	*/
	CString			sDep;		/**< �������������		*/
	CString			sPos;		/**< ���������			*/
	CString			sOrg;		/**< ������������		*/
	CString			sDateStart;	/**< ������ ������ "�"	*/
	CString			sDateEnd;	/**< ������ ������ "��"	*/
};

struct EmployeeCheckStruct;

DECLARE_BEGIN_INPUT_PARAM(EmployeeCreateStruct,2)
	DECLARE_INPUT_PARAM(id,SQL_ID)
	DECLARE_INPUT_PARAM(sName,CString)
	DECLARE_FIELD(checkCb,SQLCallback<ErrorData>*)
	typedef EmployeeCheckStruct	CheckType;
DECLARE_END_INPUT_PARAM

DECLARE_BEGIN_INPUT_PARAM(EmployeeReadStruct,1)
	DECLARE_INPUT_PARAM(id,SQL_ID)
	DECLARE_FIELD(cb,EmployeeReadResult::DataCallback*)
DECLARE_END_INPUT_PARAM

DECLARE_BEGIN_INPUT_PARAM(EmployeeDeleteStruct,1)
	DECLARE_INPUT_PARAM(id,SQL_ID)
	DECLARE_FIELD(checkCb,SQLCallback<ErrorData>*)
	typedef EmployeeCheckStruct	CheckType;
DECLARE_END_INPUT_PARAM

DECLARE_BEGIN_INPUT_PARAM(EmployeeCheckStruct,1)
	DECLARE_INPUT_PARAM(id,SQL_ID)
	DECLARE_FIELD(cb,SQLCallback<ErrorData>*)

	EmployeeCheckStruct(const EmployeeDeleteStruct& data)
		: id(data.id)
		, cb(data.checkCb)
	{}
	EmployeeCheckStruct(const EmployeeCreateStruct& data)
		: id(data.id)
		, cb(data.checkCb)
	{}
DECLARE_END_INPUT_PARAM



typedef EmployeeCreateStruct	EmployeeUpdateStruct;

typedef ParameterizedRecordSet<EmployeeCreateStruct,false>	CreateEmployeeRS;
typedef ParameterizedRecordSet<EmployeeReadStruct>			ReadEmployeeRS;
typedef ParameterizedRecordSet<EmployeeUpdateStruct,false>	UpdateEmployeeRS;
typedef ParameterizedRecordSet<EmployeeDeleteStruct,false>	DeleteEmployeeRS;
