#pragma once

class DLLApp : public CWinApp
{
public:
	DLLApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance(); // return app exit code

	DECLARE_MESSAGE_MAP()
};
