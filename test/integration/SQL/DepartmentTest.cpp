/**
 * $Id: DepartmentTest.cpp 42 2013-08-21 05:29:25Z russkinnv $
 */
#include <afxdb.h>
#include "DepartmentTest.h"
#include "database/proxy/department.h"
#include "database/Database.h"
#include "Database/Delopr.SQL/Delopr.SQL.h"

TEST_F(DepartmentTest, ListTest)
{
	Department			dep;
	DepartmentListParam	param;
	CTime t = CTime::GetCurrentTime();

	param.iDay		= t.GetDay();
	param.iMonth	= t.GetMonth();
	param.iYear		= t.GetYear();

	param.cb	= NULL;

	EXPECT_EQ( SQL_SUCCESS, dep.List(param));
}

TEST_F(DepartmentTest, CreateTest)
{
	long					lDepID;
	Department				dep;
	DepartmentCreateParam	param;

	param.checkCb		= NULL;
	param.sDepartment	= __FUNCTION__;
	param.sNote			= __FUNCTION__;

	EXPECT_EQ( SQL_SUCCESS,	dep.Create(param));

	lDepID		= param.lID;
	param.lID	= -1;
	EXPECT_EQ( SQL_ERROR,	dep.Create(param));
	
	EXPECT_EQ( SQL_SUCCESS,	dep.Purge(DepartmentPurgeParam(lDepID)));
}
