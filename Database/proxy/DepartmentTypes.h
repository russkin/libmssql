#pragma once

#include "database/ParameterizedRecordSet.h"
#include "database/proxy/error.h"

struct DepartmentCheck;

/**
 * @struct DepartmentListResult ����������, ����������� ������� ������� ��������� �����������
 */
struct DepartmentListResult
{
	DepartmentListResult() : cb(NULL){}

	typedef SQLCallback<DepartmentListResult>	DataCallback;

	DataCallback*	cb;
	long	lParent;		/**< ID "��������" � ������			*/
	CString	sParent;		/**< ������������ "��������"		*/
	long	lID;			/**< ID ����������/�������������	*/
	CString	sName;			/**< ���/������������ �������������	*/
	bool	bIsDepartment;	/**< �������������/������������		*/
	long	lPosition;		/**< ID ���������					*/
	CString	sPosition;		/**< ������������ ���������			*/
	long	lLevel;			/**< ������� �����������			*/
	long	lOrg;			/**< ID �����������					*/
};

struct DepartmentReadResult
{
	typedef SQLCallback<DepartmentReadResult>	DataCallback;

	DataCallback*	cb;
	long	lParent;		/**< ID "��������" � ������			*/
	CString	sParent;		/**< ������������ "��������"		*/
	CString	sName;			/**< ������������ �������������		*/
	double	fWeight;		/**< "���" �������������			*/
	CString	sNote;			/**< ����������						*/
	long	lOrg;			/**< ID �����������					*/
};

// @todo Use system DATETIME struct
DECLARE_BEGIN_INPUT_PARAM(DepartmentListParam,6)
	DECLARE_INPUT_PARAM(iDay,int)
	DECLARE_INPUT_PARAM(iMonth,int)
	DECLARE_INPUT_PARAM(iYear,int)
	DECLARE_INPUT_PARAM(lDepartment,long)
	DECLARE_INPUT_PARAM(lFlag,long)
	DECLARE_INPUT_PARAM(lOrg,long)
	DECLARE_FIELD(cb,DepartmentListResult::DataCallback*)

	DepartmentListParam() 
		: iDay(0)
		, iMonth(0)
		, iYear(0)
		, lDepartment(0)
		, lFlag(0)
		, lOrg(0)
		, cb(NULL)
	{}
DECLARE_END_INPUT_PARAM

DECLARE_BEGIN_INPUT_PARAM(DepartmentCreateParam,6)
	DECLARE_INPUT_PARAM(lID,long)
	DECLARE_INPUT_PARAM(lParent,long)
	DECLARE_INPUT_PARAM(sDepartment,CString)
	DECLARE_INPUT_PARAM(sNote,CString)
	DECLARE_INPUT_PARAM(fWeight,double)
	DECLARE_INPUT_PARAM(lOrg,long)
	DECLARE_FIELD(checkCb,SQLCallback<ErrorData>*)

	typedef DepartmentCheck	CheckType;

	DepartmentCreateParam()
		: lID(-1)
		, lParent(-1)
		, fWeight(0)
		, lOrg(-1)
	{}
DECLARE_END_INPUT_PARAM

DECLARE_BEGIN_INPUT_PARAM(DepartmentPurgeParam,1)
	DECLARE_INPUT_PARAM(lID,SQL_ID)
	typedef DepartmentCheck	CheckType;
	DepartmentPurgeParam(SQL_ID id) : lID(id) {}
DECLARE_END_INPUT_PARAM

DECLARE_BEGIN_INPUT_PARAM(DepartmentReadParam,1)
	DECLARE_INPUT_PARAM(lID,SQL_ID)
	DECLARE_FIELD(cb,DepartmentReadResult::DataCallback*);
	DepartmentReadParam(SQL_ID id) 
		: lID(id)
		, cb(NULL)
	{}
DECLARE_END_INPUT_PARAM

DECLARE_BEGIN_INPUT_PARAM(DepartmentCheck,1)
	DECLARE_INPUT_PARAM(id,SQL_ID)
	DECLARE_FIELD(cb,SQLCallback<ErrorData>*)

	DepartmentCheck(const DepartmentCreateParam& data)
		: id(data.lID)
		, cb(data.checkCb)
	{}
	DepartmentCheck(const DepartmentPurgeParam& data)
		: id(data.lID)
		, cb(NULL)
	{}
DECLARE_END_INPUT_PARAM

