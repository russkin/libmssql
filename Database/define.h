#pragma once 

#define FIELDEXCHANGE(Type) template <> void FieldExchanger::DoFieldExchange(CFieldExchange* pFX, Type& data)
#define READRECORDSET(RecordSet,Data) template <> int DataReader::Read(RecordSet& rs, Data& data)

#define CALL(sql) _T("{call "##sql##"}")

#define DECLARE_BEGIN_INPUT_PARAM(classname,params) struct classname {\
		static const TCHAR* sQuery;\
		static const UINT	nCount = params;\

#define DECLARE_INPUT_PARAM(name,type) type name;
#define DECLARE_FIELD(name,type) type name;
#define DECLARE_END_INPUT_PARAM };
#define IMPLEMENT_INPUT_PARAM(classname,query) const TCHAR* classname::sQuery = CALL(query);

#define TRY_CATCH_EXECUTE_SQL(command) \
	tSQLResult result = SQL_SUCCESS; \
	try{ \
	command; \
	} catch (CDBException* e) { \
			result = SQL_ERROR; \
			BuildError(e);		\
	}							\
	return result;				\

