#include <afxdb.h>
#include "Database/Delopr.SQL/Delopr.SQL.h"
#include "List_AD_Logins_TEST.h"
#include "Database/proxy/Loginn.h"
#include "Database/proxy/LoginnTypes.h"




struct LoginnReader : public LoginnCallback<LoginnReadResult>
{
	LoginnReader() : counter(0){}
	virtual void OnRow(const LoginnReadResult& data)
	{
		++counter;
	}
	int counter;
};




TEST_F(List_LoginsTest, LoginTest)
{
	LoginnReadStruct	data;   /* ��������� ������� ������. � ������ ������ ������� ���� callback */
	Loginn				loginn; /* ��������� ������ */
	LoginnReader		reader; /* ���������, ��������������� ��� ������� ���������� ������ */

	data.cb			= &reader;  /* ��������� callback input-������ */
	
	EXPECT_EQ( SQL_SUCCESS,	loginn.Read(data)); /* ��������� ����� ������ ������ */
	EXPECT_LE( 0,			reader.counter);	/* �������������� �������� ����� ��������� ������ (���-�� �����) */
}


