/**
 * @file SQL record set with input/output parameters
 * $Id: ParameterizedRecordSet.h 68 2013-09-18 01:23:51Z russkinnv $
 */

#pragma once

#include "define.h"
#include "RecordSet.h"


template <typename Params, bool WithResult = true>
class ParameterizedRecordSet : virtual public RecordSet
{
public:
	ParameterizedRecordSet (CDatabase* pDatabase = NULL) 
		: RecordSet(pDatabase)
		, m_data(NULL)
	{
		m_nParams = Params::nCount;
		m_bExecuteOnly = !WithResult;
	}

	virtual ~ParameterizedRecordSet(){}

	tSQLResult Query()
	{
		TRY_CATCH_EXECUTE_SQL( Open( CRecordset::forwardOnly, Params::sQuery, CRecordset::readOnly) );
	}

	virtual BOOL Requery()
	{
		TRY_CATCH_EXECUTE_SQL(__super::Requery());
	}

	/**
	 *	@TODO  будут проблемы с классами-наследниками, т.к. происходит св€звание типов на этапе компил€ции, а не на этапе выполенни€.
	 * ¬ этом случае можно использовать следующий код:
	 * @code
	 *	Datareader reader;
	 *	reader.Read(recordset,data);
	 * @endcode
	 * либо пересмотреть подход к решению данной проблемы
	 */
	template <typename Result>
	tSQLResult Read(Result& result)
	{
		DataReader	reader;
		return reader.Read( *this, result);
	}

protected:
	/**
	 *	ѕередача параметров запроса
	 */
	virtual void DoFieldExchange(CFieldExchange* pFX)
	{
		ASSERT(m_data);
		FieldExchanger fe;
		fe.DoFieldExchange<Params>(pFX, *m_data);
	}
public:
	Params*	m_data;
};

/**
 *	ƒл€ компактного определени€ типа ParameterizedRecordSet<DataType>
 * @code
 * RS<DataType>::Type recordset(database);
 * @endcode
 */
template <typename T, bool Out=true>
struct RS{
	typedef ParameterizedRecordSet<T,Out> Type;
};
