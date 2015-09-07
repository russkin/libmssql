#pragma once

#include "database/RecordSet.h"

struct ErrorData;

/**
 *	Callback для обработки/отображения результатов SQL запроса
 */
template <typename T=ErrorData>
struct SQLCallback
{
	/**
	 *	Обработка полученной из БД информации
	 */
	virtual void OnData(const T*) = 0;
};

/**
 *	Информация об ошибках при проверке данных
 */
struct ErrorData
{
	ErrorData() : cb(NULL) {}

	enum ErrorType {DATA_WARNING = 0, DATA_ERROR = 1};		/**< Тип сообщения	*/
	enum {ERROR_PARAMETER_COUNT	= 9};		/**< Количество выходных параметров - дополнительная информация об ошибке*/

	
	struct Parameter
	{
		int		iValue;
		CString	sValue;
	};


	SQLCallback<ErrorData>*	cb;

	int			iID;
	float		fCount[2];
	ErrorType	type;
	Parameter	info[ERROR_PARAMETER_COUNT];
};


class ReadErrorRS : virtual public RecordSet
{
public:
	ReadErrorRS (CDatabase* pDatabase) 
		: RecordSet(pDatabase) {}
	virtual ~ReadErrorRS(){}

};
