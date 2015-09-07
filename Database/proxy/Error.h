#pragma once

#include "database/RecordSet.h"

struct ErrorData;

/**
 *	Callback ��� ���������/����������� ����������� SQL �������
 */
template <typename T=ErrorData>
struct SQLCallback
{
	/**
	 *	��������� ���������� �� �� ����������
	 */
	virtual void OnData(const T*) = 0;
};

/**
 *	���������� �� ������� ��� �������� ������
 */
struct ErrorData
{
	ErrorData() : cb(NULL) {}

	enum ErrorType {DATA_WARNING = 0, DATA_ERROR = 1};		/**< ��� ���������	*/
	enum {ERROR_PARAMETER_COUNT	= 9};		/**< ���������� �������� ���������� - �������������� ���������� �� ������*/

	
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
