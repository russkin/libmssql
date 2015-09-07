#include "DatabaseTest.h"
#include "database/Database.h"
#include "Database/Delopr.SQL/Delopr.SQL.h"
#include "Database/DSN.h"

TEST_F(DatabaseTest, DSNTest)
{
	DSN	dsn( "DSNTest", "DB01-DSD", "TEST");

	EXPECT_EQ( SQL_SUCCESS, dsn.Create());
	EXPECT_EQ( SQL_SUCCESS, dsn.Delete());
	EXPECT_EQ( SQL_ERROR, dsn.Delete());
}

TEST_F(DatabaseTest, ConnectionTest)
{
	const char* server_name	= "DB01-DSD";
	const char* data_base	= "TEST";
	const char* dsn_name	= "DatabaseTest::ConnectionTest";
	DSN			dsn( dsn_name, server_name, data_base);
	Database	base;

	EXPECT_EQ( SQL_ERROR, base.Open(dsn.GetName()));

	ASSERT_EQ( SQL_SUCCESS, dsn.Create());
	ASSERT_EQ( SQL_SUCCESS, base.Open( dsn.GetName()));
	EXPECT_EQ( SQL_ERROR, base.Open( "INVALIDDSN"));
	EXPECT_EQ( SQL_ERROR, base.Open( NULL));
	EXPECT_EQ( SQL_SUCCESS, base.Close());
	EXPECT_EQ( SQL_SUCCESS, dsn.Delete());
}

TEST_F(DatabaseTest, ExecutionTest)
{
	const char* server_name	= "DB01-DSD";
	const char* data_base	= "TEST";
	const char* dsn_name	= "DatabaseTest::ConnectionTest";
	DSN			dsn( dsn_name, server_name, data_base);
	Database	base;

	ASSERT_EQ( SQL_SUCCESS, dsn.Create( ));
	ASSERT_EQ( SQL_SUCCESS, base.Open( dsn.GetName()));

	EXPECT_EQ( SQL_SUCCESS, base.Exec((const SQLCHAR*)("select top 1 * from users")));

	EXPECT_EQ( SQL_SUCCESS, base.Close());
	EXPECT_EQ( SQL_SUCCESS, dsn.Delete( ));
}
