// ProPage2.cpp : implementation file
//

#include "stdafx.h"
#include "802_1X Connector.h"
#include "ProPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProPage2 property page

IMPLEMENT_DYNCREATE(CProPage2, CPropertyPage)

CProPage2::CProPage2() : CPropertyPage(CProPage2::IDD)
{
	//{{AFX_DATA_INIT(CProPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CProPage2::~CProPage2()
{
}

void CProPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProPage2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CProPage2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProPage2 message handlers
