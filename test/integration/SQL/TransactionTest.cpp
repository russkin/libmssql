/**
 *	$Id$
 */
#include "TransactionTest.h"
#include "database/transaction.h"
#include "database/Database.h"
#include "database/ParameterizedRecordSet.h"

extern DELOPRSQL_API Database gDataBase;

TransactionTest::TransactionTest(void)
{
}

TransactionTest::~TransactionTest(void)
{
}

DECLARE_BEGIN_INPUT_PARAM(ReadRecordCount,1)
	DECLARE_INPUT_PARAM(count,long)
DECLARE_END_INPUT_PARAM
IMPLEMENT_INPUT_PARAM(ReadRecordCount,"TEST.sp_count_values(?)")

DECLARE_BEGIN_INPUT_PARAM(AddRecord,2)
	DECLARE_INPUT_PARAM( count, long)
	DECLARE_INPUT_PARAM( value, CString)
DECLARE_END_INPUT_PARAM
IMPLEMENT_INPUT_PARAM(AddRecord,"TEST.sp_add_value(?,?)")

template <>
void FieldExchanger::DoFieldExchange(CFieldExchange* pFX, ReadRecordCount& data)
{
	pFX->SetFieldType(CFieldExchange::inoutParam);
	RFX_Long(pFX, _T("count"), data.count);
}

template <>
void FieldExchanger::DoFieldExchange(CFieldExchange* pFX, AddRecord& data)
{
	pFX->SetFieldType(CFieldExchange::inoutParam);
	RFX_Long(pFX, _T("count"), data.count);
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Text(pFX, _T("value"), data.value);
}

typedef ParameterizedRecordSet<ReadRecordCount,false>	RecordCountQuery;
typedef ParameterizedRecordSet<AddRecord,false>			AddRecordQuery;

TEST_F(TransactionTest, RollbackTest)
{
	CTransaction		trans(&gDataBase.instance());
	RecordCountQuery	count(&gDataBase.instance());
	AddRecordQuery		queryAdd(&gDataBase.instance());
	AddRecord			addData;
	ReadRecordCount		countData;

	count.m_data		= &countData;
	queryAdd.m_data		= &addData;
	addData.value		= "RollbackTest";

	EXPECT_EQ( SQL_SUCCESS, trans.Begin());

	EXPECT_EQ( SQL_SUCCESS, count.Query());
	EXPECT_EQ( 0,			countData.count);

	EXPECT_EQ( SQL_SUCCESS, queryAdd.Query());
	EXPECT_EQ( SQL_SUCCESS, count.Requery());
	EXPECT_EQ( 1,			countData.count);

	EXPECT_EQ( SQL_SUCCESS, queryAdd.Requery());
	EXPECT_EQ( SQL_SUCCESS, count.Requery());
	EXPECT_EQ( 2,			countData.count);

	EXPECT_EQ( SQL_SUCCESS, trans.Rollback());
}