/**
 * @file Delopr.SQL library interface
 * $Id: Delopr.SQL.h 66 2013-09-17 07:23:48Z russkinnv $
 */
#pragma once

#ifdef DELOPRSQL_EXPORTS
#define DELOPRSQL_API __declspec(dllexport)
#else
#define DELOPRSQL_API __declspec(dllimport)
#endif


#ifdef DELOPR
extern DELOPRSQL_API HSTMT hstmt;	// TODO: migrate to SQLQuery class
#endif


#ifdef _CUP_VSTO
	#define SERVER_NAME			_T("10.217.1.13")
	#define SQL_SERVER_DATABASE	_T("OIT")
	#define SQL_DSN_DESCRIPTION _T("DB03-VSTO-OIT")
#else// _CUP_VSTO

	#define SERVER_NAME			_T("db01-dsd")
	#ifdef _DEBUG
		#define SQL_SERVER_DATABASE _T("TEST")
		#define SQL_DSN_DESCRIPTION _T("DB01-DSD-TEST")
	#else
		#define SQL_SERVER_DATABASE _T("DSD")
		#define SQL_DSN_DESCRIPTION _T("DB01-DSD-DSD")
	#endif
#endif// _CUP_VSTO

typedef long SQL_ID;
typedef int tSQLResult;

