/**
 * $Id: DataReaderTest.cpp 39 2013-08-20 10:37:15Z russkinnv $
 */

#include "DataReaderTest.h"
#include "database/Database.h"
#include "Database/RecordSet.h"
#include "Database/Delopr.SQL/Delopr.SQL.h"
#include "database/ParameterizedRecordSet.h"


DataReaderTest::DataReaderTest(){}
DataReaderTest::~DataReaderTest(){}

typedef long ID;

long	m_createdUser;


struct ReadUserResultTest
{
	ID			iOrg;
	ID			iDv;
	CString		sName;
	CString		sOrg;
	CString		sDep;
	CString		sPos;
	CString		sDate;
};

struct CreateUserResultTest
{
	ID			id;
};

typedef CreateUserResultTest DeleteUserResultTest;

DECLARE_BEGIN_INPUT_PARAM(CreateUserParamTest,2)
	DECLARE_INPUT_PARAM(id,ID)
	DECLARE_INPUT_PARAM(sName,CString)
DECLARE_END_INPUT_PARAM
IMPLEMENT_INPUT_PARAM(CreateUserParamTest,"Delopr_Create_Sotrudn(?,?)")

DECLARE_BEGIN_INPUT_PARAM(ReadUserParamTest,1)
	DECLARE_INPUT_PARAM(lID,ID)
DECLARE_END_INPUT_PARAM
IMPLEMENT_INPUT_PARAM(ReadUserParamTest,"Delopr_Get_Sotrudn_Load(?)")

DECLARE_BEGIN_INPUT_PARAM(DeleteUserParamTest,1)
	DECLARE_INPUT_PARAM(lID,ID)
DECLARE_END_INPUT_PARAM
IMPLEMENT_INPUT_PARAM(DeleteUserParamTest,"Delopr_Delete_Users(?)")

DECLARE_BEGIN_INPUT_PARAM(CleanupUserParamTest,1)
	DECLARE_INPUT_PARAM(lID,ID)
DECLARE_END_INPUT_PARAM
IMPLEMENT_INPUT_PARAM(CleanupUserParamTest,"Delopr_Purge_User(?)")


typedef ParameterizedRecordSet<CreateUserParamTest,false>	CreateUserRecordSet;
typedef ParameterizedRecordSet<ReadUserParamTest>			ReadUserRecordSet;
typedef ParameterizedRecordSet<DeleteUserParamTest,false>	DeleteUserRecordSet;
typedef ParameterizedRecordSet<CleanupUserParamTest,false>	CleanupUserRecordSet;

template <>
void FieldExchanger::DoFieldExchange(CFieldExchange* pFX, ReadUserParamTest& data)
{
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Long(pFX, _T("id"), data.lID);
}

template <>
void FieldExchanger::DoFieldExchange(CFieldExchange* pFX, DeleteUserParamTest& data)
{
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Long(pFX, _T("id"), data.lID);
}

template <>					
void FieldExchanger::DoFieldExchange(CFieldExchange* pFX, CreateUserParamTest& data)
{
	pFX->SetFieldType(CFieldExchange::inoutParam);
	RFX_Long(pFX, _T("id"), data.id);
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Text(pFX, _T("name"), data.sName);
}

template <>
void FieldExchanger::DoFieldExchange(CFieldExchange* pFX, CleanupUserParamTest& data)
{
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Long(pFX, _T("id"), data.lID);
}


template <>
int DataReader::Read(ReadUserRecordSet& rs, ReadUserResultTest& data)
{
	try{
		data.sName	= rs.GetFieldValueT<CString>(0);
		data.iOrg	= rs.GetFieldValueT<long>(1);
		data.sOrg	= rs.GetFieldValueT<CString>(2);

		rs.MoveNextRecordSet(); 

		while (!rs.IsEOF())
		{
			data.iDv	= rs.GetFieldValueT<long>(0);
			data.sDep	= rs.GetFieldValueT<CString>(1);
			data.sPos	= rs.GetFieldValueT<CString>(2);
			data.sDate	= rs.GetFieldValueT<CString>(3);
			rs.MoveNext();
		}
	} catch(CDBException* e) {
		rs.BuildError(e);
		return SQL_ERROR;
	}
	return SQL_SUCCESS;
}

template <>
int DataReader::Read(CreateUserRecordSet& rs, CreateUserResultTest& data)
{
	return SQL_SUCCESS;
}

template <>
int DataReader::Read(DeleteUserRecordSet& rs, DeleteUserResultTest& data)
{
	return SQL_SUCCESS;
}

tSQLResult PurgeUser(const int id)
{
	CleanupUserRecordSet	rs( &gDataBase.instance());
	CleanupUserParamTest	data;
	tSQLResult				result = SQL_ERROR;

	rs.m_data	= &data;
	data.lID	= id;
	
	result = rs.Query();

	return result;
}

TEST_F(DataReaderTest, CreateUserTest)
{
	CreateUserRecordSet		rs( &gDataBase.instance() );
	CreateUserParamTest		data;

	data.id		= -1;
	data.sName	= _T("Русскин Николай");
	rs.m_data	= &data;

	EXPECT_EQ( SQL_SUCCESS,	rs.Query());
	EXPECT_LT( 0,			data.id);
	
	m_createdUser = data.id;
	data.sName	= _T("Русскин Николай Updated");

	EXPECT_EQ( SQL_SUCCESS, rs.Requery());

	rs.Close( );
}


TEST_F(DataReaderTest, DeleteUserTest)
{
	DeleteUserRecordSet		rs( &gDataBase.instance());
	DeleteUserParamTest		data;
	DeleteUserResultTest	user;

	rs.m_data	= &data;
	data.lID	= m_createdUser;
	
	EXPECT_EQ( SQL_SUCCESS, rs.Query());
	EXPECT_EQ( SQL_SUCCESS, rs.Read(user));

	rs.Close( );
}

TEST_F(DataReaderTest, CleanupTest)
{
	CleanupUserRecordSet	rs( &gDataBase.instance());
	CleanupUserParamTest	data;

	rs.m_data	= &data;
	data.lID	= m_createdUser;
	
	EXPECT_EQ( SQL_SUCCESS, rs.Query());
	rs.Close();
}
