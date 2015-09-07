#pragma once


#include "database/ParameterizedRecordSet.h"
#include "database/proxy/error.h"

/**
 *	Callback ��� ���������/����������� ����������� �������
 */
template <typename T>
struct LoginnCallback
{
	virtual void OnRow(const T&){}	/**< ���������� �� ����� ������ ������������	*/
};

/**
 * @class LoginnReadResult
 */
struct LoginnReadResult
{
	LoginnReadResult() : cb(NULL){}

	typedef LoginnCallback<LoginnReadResult>	DataCallback;

	DataCallback*	cb;
	CString			sName;		/**< ��� ������������	*/
	CString			sLogin;		/**< �����				*/
	CString			sDep;		/**< �������������		*/
	CString			sPhone;		/**< �������			*/
};

struct LoginnCheckStruct;

DECLARE_BEGIN_INPUT_PARAM(LoginnReadStruct,0)
	DECLARE_FIELD(cb,LoginnReadResult::DataCallback*)
DECLARE_END_INPUT_PARAM

typedef ParameterizedRecordSet<LoginnReadStruct>			ReadLoginnRS;