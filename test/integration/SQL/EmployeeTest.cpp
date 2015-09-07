/**
 * $Id: EmployeeTest.cpp 39 2013-08-20 10:37:15Z russkinnv $
 */
#include <afxdb.h>
#include "Database/Delopr.SQL/Delopr.SQL.h"
#include "employeetest.h"
#include "database/proxy/employee.h"

#define STR(x) #x
#define CONCAT(a,b) STR(a)##STR(b)

tSQLResult PurgeUser(const int id);

int gCreatedUser;


struct EmployeeReader : public EmployeeCallback<EmployeeReadResult>
{
	virtual void OnData(const EmployeeReadResult& data)
	{
		mData = data;
	}
	virtual void OnRow(const EmployeeReadResult& data)
	{
	}
	EmployeeReadResult	mData;
};

struct ErrorBuilder : public SQLCallback<ErrorData>
{
	ErrorBuilder() : mResult(SQL_SUCCESS) {}
	virtual ~ErrorBuilder(){}

	void OnData(const ErrorData* data)
	{
		mResult	= SQL_ERROR;
		mData	= *data;
	}

	ErrorData	mData;
	tSQLResult	mResult;
};

TEST_F(EmployeeTest, CreateTest)
{
	EmployeeCreateStruct	data;
	Employee				employee;
	ErrorBuilder			error;

	data.id			= -1;
	data.sName		= __FILE__;
	data.checkCb	= &error;

	EXPECT_EQ( SQL_SUCCESS,		employee.Create(data));
	EXPECT_EQ( SQL_SUCCESS,		error.mResult);
	EXPECT_LT( 0,				data.id);

	gCreatedUser	= data.id;

	EXPECT_EQ( SQL_ERROR,		employee.Create(data));	// create dublicate
	EXPECT_EQ( SQL_ERROR,		error.mResult);
	EXPECT_EQ( 1,				error.mData.iID);
	EXPECT_EQ( 2,				error.mData.type);
	EXPECT_STREQ( __FILE__,		error.mData.info[0].sValue);
}


TEST_F(EmployeeTest, ReadTest)
{
	EmployeeReadStruct		data;
	Employee				employee;
	EmployeeReader			reader;

	data.id			= gCreatedUser;
	data.cb			= &reader;
	
	EXPECT_EQ( SQL_SUCCESS,		employee.Read(data));

	EXPECT_STREQ( __FILE__,		reader.mData.sName);
}

TEST_F(EmployeeTest, UpdateTest)
{
	EmployeeUpdateStruct	data;
	Employee				employee;
	ErrorBuilder			error;

	data.id			= gCreatedUser;
	data.sName		= CONCAT(__FILE__,__FILE__);
	data.checkCb	= &error;

	EXPECT_EQ( SQL_SUCCESS,		employee.Update(data));
	EXPECT_EQ( SQL_SUCCESS,		error.mResult);
}

TEST_F(EmployeeTest, ReadUpdatedTest)
{
	EmployeeReadStruct		data;
	Employee				employee;
	EmployeeReader			reader;

	data.id			= gCreatedUser;
	data.cb			= &reader;
	
	EXPECT_EQ( SQL_SUCCESS,		employee.Read(data));

	EXPECT_STREQ( CONCAT(__FILE__,__FILE__),	reader.mData.sName);
}

TEST_F(EmployeeTest, DeleteTest)
{
	EmployeeDeleteStruct	data;
	Employee				employee;
	ErrorBuilder			error;
	
	data.id			= gCreatedUser;
	data.checkCb	= &error;

	EXPECT_EQ( SQL_SUCCESS,		employee.Delete(data));
	EXPECT_EQ( SQL_SUCCESS,		error.mResult);
	EXPECT_EQ( SQL_SUCCESS,		PurgeUser(data.id));
}

#undef STR
#undef CONCAT