// 802_1X Connector.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "802_1X Connector.h"
#include "802_1X ConnectorDlg.h"
#include<IPHlpApi.h>



/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// CMy802_1XConnectorApp

BEGIN_MESSAGE_MAP(CMy802_1XConnectorApp, CWinApp)
	//{{AFX_MSG_MAP(CMy802_1XConnectorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy802_1XConnectorApp construction

CMy802_1XConnectorApp::CMy802_1XConnectorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMy802_1XConnectorApp object

CMy802_1XConnectorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMy802_1XConnectorApp initialization

BOOL CMy802_1XConnectorApp::InitInstance()
{
//	if (!InitATL())
//		return FALSE;

	AfxEnableControlContainer();


	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}



	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMy802_1XConnectorDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

	
//CMy802_1XConnectoModule _Module;

//BEGIN_OBJECT_MAP(ObjectMap)
//END_OBJECT_MAP()

/*LONG CMy802_1XConnectoModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CMy802_1XConnectoModule::Lock()
{
	AfxOleLockApp();
	return 1;
}

LPCTSTR CMy802_1XConnectoModule::FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1++;
	}
	return NULL;
}

*/
int CMy802_1XConnectorApp::ExitInstance()
{
/*	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
		CoUninitialize();
	}*/

	return CWinApp::ExitInstance();

}

//DEL BOOL CMy802_1XConnectorApp::InitATL()
//DEL {
//DEL 	m_bATLInited = TRUE;
//DEL 
//DEL #if _WIN32_WINNT >= 0x0400
//DEL 	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
//DEL #else
//DEL 	HRESULT hRes = CoInitialize(NULL);
//DEL #endif
//DEL 
//DEL 	if (FAILED(hRes))
//DEL 	{
//DEL 		m_bATLInited = FALSE;
//DEL 		return FALSE;
//DEL 	}
//DEL 
//DEL 	_Module.Init(ObjectMap, AfxGetInstanceHandle());
//DEL 	_Module.dwThreadID = GetCurrentThreadId();
//DEL 
//DEL 	LPTSTR lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
//DEL 	TCHAR szTokens[] = _T("-/");
//DEL 
//DEL 	BOOL bRun = TRUE;
//DEL 	LPCTSTR lpszToken = _Module.FindOneOf(lpCmdLine, szTokens);
//DEL 	while (lpszToken != NULL)
//DEL 	{
//DEL 		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
//DEL 		{
//DEL 			_Module.UpdateRegistryFromResource(IDR_MY802_1XCONNECTO, FALSE);
//DEL 			_Module.UnregisterServer(TRUE); //TRUE means typelib is unreg'd
//DEL 			bRun = FALSE;
//DEL 			break;
//DEL 		}
//DEL 		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
//DEL 		{
//DEL 			_Module.UpdateRegistryFromResource(IDR_MY802_1XCONNECTO, TRUE);
//DEL 			_Module.RegisterServer(TRUE);
//DEL 			bRun = FALSE;
//DEL 			break;
//DEL 		}
//DEL 		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
//DEL 	}
//DEL 
//DEL 	if (!bRun)
//DEL 	{
//DEL 		m_bATLInited = FALSE;
//DEL 		_Module.Term();
//DEL 		CoUninitialize();
//DEL 		return FALSE;
//DEL 	}
//DEL 
//DEL 	hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
//DEL 		REGCLS_MULTIPLEUSE);
//DEL 	if (FAILED(hRes))
//DEL 	{
//DEL 		m_bATLInited = FALSE;
//DEL 		CoUninitialize();
//DEL 		return FALSE;
//DEL 	}	
//DEL 
//DEL 	return TRUE;
//DEL 
//DEL }
