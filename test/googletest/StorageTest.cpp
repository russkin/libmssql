#include "Stdafx.h"
#include "StorageTest.h"
#include "Storage/Storage.h"
#include "Storage/StorageObject.h"
#include "storage/Builder.h"

class TestUser : public StorageObject
{
public:
	TestUser(){}
	virtual ~TestUser(){}
};

class TestUserAdapter : public Adapter
{
public:
	TestUserAdapter(){}
	virtual ~TestUserAdapter(){}


	virtual int Create	(const StorageObject* object){ return 10;}
	virtual int Read	(const StorageObject* object){ return 11;}
	virtual int Update	(const StorageObject* object){ return 12;}
	virtual int Delete	(const StorageObject* object){ return 13;}
};

TEST_F(StorageTest, RouteTest)
{
	TestUserAdapter adapter;
	TestUser user;

	EXPECT_EQ(user.Create(adapter), 10);
	EXPECT_EQ(user.Read(adapter), 11);
	EXPECT_EQ(user.Update(adapter), 12);
	EXPECT_EQ(user.Delete(adapter), 13);
}
