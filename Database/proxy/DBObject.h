#pragma once

#include "database/Delopr.SQL/Delopr.SQL.h"
#include "database/Delopr.SQL/DBError.h"
#include "database/Database.h"
#include "database/transaction.h"
#include "database/parameterizedrecordset.h"

extern DELOPRSQL_API Database gDataBase;


class DBObject
{
public:
	DBObject(){}

	DBError::Error Error() const 
	{
		return mError.GetError();
	}

protected:

	template <typename CheckData>
	tSQLResult Check (CheckData& data, CDatabase* db)
	{
		RS<CheckData>::Type	rs(db);
		ErrorData			error;
		int					result = SQL_ERROR;

		rs.m_data	= &data;
		error.cb	= data.cb;
		if ( SQL_SUCCESS == (result = rs.Query()))
			result = rs.Read(error);
		rs.Close();

		processError( result, rs.GetError());

		return result;
	}

	/**
	 * Выполнить запрос (добавление/обновление/удаление) и провести порверку. 
	 * В случае ошибки откатить операцию.
	 * @param data Входные данные
	 */
	template <typename InputData>
	tSQLResult ExecuteAndCheck(InputData& data)
	{
		CDatabase*					db = &gDataBase.instance();
		RS<InputData,false>::Type	rs(db);
		CTransaction				trans(db);
		int							result = SQL_ERROR;

		trans.Begin();

		rs.m_data	= &data;
		result		= rs.Query();
		rs.Close();

		if ( SQL_SUCCESS == result)
		{
			InputData::CheckType check(data);
			result		= Check(check, db);
		}

		if ( SQL_SUCCESS == result)
			trans.Commit();
		else
			trans.Rollback();

		processError( result, rs.GetError());

		return result;
	}

	/**
	 * Выполнить запрос и прочитать результат. 
	 */
	template <typename InputData, typename OutputData>
	tSQLResult ExecuteAndRead(InputData& input, OutputData& output)
	{
		RS<InputData>::Type	rs( &gDataBase.instance() );
		int					result = SQL_ERROR;

		output.cb		= input.cb;
		rs.m_data		= &input;
		if ( SQL_SUCCESS == (result = rs.Query()))
			result = rs.Read(output);
		rs.Close();

		processError( result, rs.GetError());

		return result;
	}

protected:
	void processError(tSQLResult res, const DBError::Error& err)
	{
		if (SQL_ERROR == res)
			mError.Add(err);
	}
private:
	DBError	mError;
};
