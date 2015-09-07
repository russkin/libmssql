/**
 *	$Id: Error.cpp 66 2013-09-17 07:23:48Z russkinnv $
 */
#include "stdafx.h"
#include "database/proxy/error.h"


template <>
int DataReader::Read(RecordSet& rs, ErrorData& data)
{
	tSQLResult result = SQL_SUCCESS;
	try{
		while (!rs.IsEOF())
		{
			result			= SQL_ERROR;
			data.iID		= rs.GetFieldValueT<long>(0);
			data.type		= (ErrorData::ErrorType)rs.GetFieldValueT<long>(1);
			data.fCount[0]	= rs.GetFieldValueT<float>(2);
			data.fCount[1]	= rs.GetFieldValueT<float>(3);

			for (int i = 0; i < ErrorData::ERROR_PARAMETER_COUNT; ++i)
			{
				data.info[i].iValue	= rs.GetFieldValueT<long>( (i<<1) + 4);
				data.info[i].sValue	= rs.GetFieldValueT<CString>( (i<<1) + 5);
			}

			if (data.cb)
				data.cb->OnData(&data);

			rs.MoveNext();
		}
	} catch(CDBException* e) {
		rs.BuildError(e);
	}
	return result;
}

template <>
int DataReader::Read(ReadErrorRS& rs, ErrorData& data)
{
	return Read(*(dynamic_cast<RecordSet*>(&rs)), data);
}