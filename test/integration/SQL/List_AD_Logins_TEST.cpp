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
	LoginnReadStruct	data;   /* структура входных данных. В данном случае содежит лишь callback */
	Loginn				loginn; /* экземпляр данных */
	LoginnReader		reader; /* структура, предназначенная для разбора полученных данных */

	data.cb			= &reader;  /* связываем callback input-данных */
	
	EXPECT_EQ( SQL_SUCCESS,	loginn.Read(data)); /* запускаем метод чтения данных */
	EXPECT_LE( 0,			reader.counter);	/* дополнительная проверка факта получения данных (кол-во строк) */
}


