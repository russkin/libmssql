#pragma once


#include "database/ParameterizedRecordSet.h"
#include "database/proxy/error.h"

/**
 *	Callback для обработки/отображения результатов запроса
 */
template <typename T>
struct LoginnCallback
{
	virtual void OnRow(const T&){}	/**< Информация об одном логине пользователя	*/
};

/**
 * @class LoginnReadResult
 */
struct LoginnReadResult
{
	LoginnReadResult() : cb(NULL){}

	typedef LoginnCallback<LoginnReadResult>	DataCallback;

	DataCallback*	cb;
	CString			sName;		/**< Имя пользователя	*/
	CString			sLogin;		/**< Логин				*/
	CString			sDep;		/**< Подразделение		*/
	CString			sPhone;		/**< Телефон			*/
};

struct LoginnCheckStruct;

DECLARE_BEGIN_INPUT_PARAM(LoginnReadStruct,0)
	DECLARE_FIELD(cb,LoginnReadResult::DataCallback*)
DECLARE_END_INPUT_PARAM

typedef ParameterizedRecordSet<LoginnReadStruct>			ReadLoginnRS;