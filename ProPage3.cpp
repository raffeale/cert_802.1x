// ProPage3.cpp : implementation file
//

#include "stdafx.h"
#include "802_1X Connector.h"
#include "ProPage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProPage3 property page

IMPLEMENT_DYNCREATE(CProPage3, CPropertyPage)

CProPage3::CProPage3() : CPropertyPage(CProPage3::IDD)
{
	//{{AFX_DATA_INIT(CProPage3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CProPage3::~CProPage3()
{
}

void CProPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProPage3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CProPage3)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProPage3 message handlers
