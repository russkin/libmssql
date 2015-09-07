#pragma once

#include "Delopr.SQL/Delopr.SQL.h"

/**
 * @class DSN
 * Data source name manipulation
 */
class DELOPRSQL_API DSN
{
public:
	DSN(const CString& description, const CString& server, const CString& database)
		: m_description	("DSN="+description)
		, m_server		(server)
		, m_database	(database)
		, m_format		("%s/DESCRIPTION=%s/SERVER=%s/DATABASE=%s/Trusted_Connection=Yes/")
		{}

	tSQLResult	Create()		const;	/**< Create DSN			*/
	tSQLResult	Delete()		const;	/**< Delete DSN			*/
	LPCTSTR		GetName()		const;	/**< Build DSN name "DSN=%description"*/
	LPCTSTR		GetDatabase()	const;	/**< return m_database	*/

protected:
	void prepareConnectionString(CString& connectionString) const;	/**< change double slashes to terminate symbol */

private:
	CString	m_description;
	CString	m_server;
	CString	m_database;
	CString	m_format;

};
