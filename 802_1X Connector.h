// 802_1X Connector.h : main header file for the 802_1X CONNECTOR application
//

#if !defined(AFX_802_1XCONNECTOR_H__A2FB7474_D883_4C62_A210_064D478E126A__INCLUDED_)
#define AFX_802_1XCONNECTOR_H__A2FB7474_D883_4C62_A210_064D478E126A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
//#include "802_1X Connector_i.h"

/////////////////////////////////////////////////////////////////////////////
// CMy802_1XConnectorApp:
// See 802_1X Connector.cpp for the implementation of this class
//

class CMy802_1XConnectorApp : public CWinApp
{
public:
	CMy802_1XConnectorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy802_1XConnectorApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy802_1XConnectorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
//	BOOL m_bATLInited;
private:
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_802_1XCONNECTOR_H__A2FB7474_D883_4C62_A210_064D478E126A__INCLUDED_)
