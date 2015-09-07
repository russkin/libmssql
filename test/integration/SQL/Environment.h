#pragma once

#include "gtest/gtest.h"

class Environment :	public ::testing::Environment
{
public:
	Environment();
	virtual ~Environment();

	virtual void SetUp();
	virtual void TearDown();

};
