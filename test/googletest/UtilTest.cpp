#include "Stdafx.h"
#include "UtilTest.h"
#include "Database/Delopr.SQL/util.h"

struct ConvTest
{
	long id;

	ConvTest(long val=0)
	{
		id = val;
	}
};

template <> ConvTest Converter::GetData(const CDBVariant& varValue) const { return ConvTest(varValue.m_lVal);}

TEST_F(UtilTest, ConverterTest)
{
	Converter	conv;
	CDBVariant	varValue;
	ConvTest	val;

	EXPECT_EQ(0, val.id);

	varValue.m_lVal = 101;
	val = conv.GetData<ConvTest>(varValue);
	EXPECT_EQ(101, val.id);
}
