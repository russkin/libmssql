#pragma once

#include <list>
#include <string>
#include <algorithm>
#include "database/Delopr.SQL/Delopr.SQL.h"

class DBError
{
public:
	DBError(){}

	typedef CString Error;
	typedef std::list<Error> ErrorList;

	void Add(const Error& err);

	DBError::Error GetError() const
	{
		return std::for_each(m_Error.begin(), m_Error.end(), Concat()).mResult;
	}

private:
	struct Concat
	{
		void operator() (const DBError::Error& err)
		{
			mResult += err + "\n";
		}

		DBError::Error	mResult;
	};

private:
	ErrorList	m_Error;
};
