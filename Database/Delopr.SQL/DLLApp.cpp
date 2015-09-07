#include "StdAfx.h"
#include "DLLApp.h"
#include "database/Database.h"
#include "database/DSN.h"


BEGIN_MESSAGE_MAP(DLLApp, CWinApp)
END_MESSAGE_MAP()


// CMFC_DLLApp construction
DLLApp::DLLApp(void)
{
}


// The one and only CMFC_DLLApp object
DLLApp					theApp;
DELOPRSQL_API	DSN		gDSN( SQL_DSN_DESCRIPTION, SERVER_NAME, SQL_SERVER_DATABASE);


BOOL DLLApp::InitInstance()
{
	CWinApp::InitInstance();
	tSQLResult res = gDSN.Create();
	ASSERT( SQL_SUCCESS == res);
	return TRUE;
}

int DLLApp::ExitInstance()
{
	gDSN.Delete();
	return CWinApp::ExitInstance();
}
