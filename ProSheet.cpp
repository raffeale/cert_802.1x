// ProSheet.cpp : implementation file
//

#include "stdafx.h"
#include "802_1X Connector.h"
#include "ProSheet.h"

//Local MAC¡¢IP¡¢Gateway¡¢DNS
extern	unsigned char LocalMAC[6];
extern	char LocalIP[4];
extern	char LocalNetmask[4];
extern	char LocalGateway[4];
extern	char LocalDNS[4];
extern	char LocalDHCP[4];
static unsigned char vmac1[2];
static unsigned char vmac2[2];
static unsigned char vmac3[2];
static unsigned char vmac4[2];
static unsigned char vmac5[2];
static unsigned char vmac6[2];
//Virtial IP and Virtual MAC Address
	static unsigned char vmac[6];

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProSheet

IMPLEMENT_DYNAMIC(CProSheet, CPropertySheet)

CProSheet::CProSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	this->AddPage(&configpage1);
	this->AddPage(&configpage2);
	this->AddPage(&configpage3);
}

CProSheet::CProSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	this->AddPage(&configpage1);
	this->AddPage(&configpage2);
	this->AddPage(&configpage3);

}

CProSheet::~CProSheet()
{
}


BEGIN_MESSAGE_MAP(CProSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CProSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProSheet message handlers
