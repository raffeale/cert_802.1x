// ProPage1.cpp : implementation file
//

#include "stdafx.h"
#include "802_1X Connector.h"
#include "ProPage1.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProPage1 property page

IMPLEMENT_DYNCREATE(CProPage1, CPropertyPage)

CProPage1::CProPage1() : CPropertyPage(CProPage1::IDD)
{
	//{{AFX_DATA_INIT(CProPage1)
	m_mac1 = _T("");
	m_mac2 = _T("");
	m_mac3 = _T("");
	m_mac4 = _T("");
	m_mac5 = _T("");
	m_mac6 = _T("");
	//}}AFX_DATA_INIT
}

CProPage1::~CProPage1()
{
}

void CProPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProPage1)
	DDX_Control(pDX, IDC_GATEWAY, m_vgateway);
	DDX_Control(pDX, IDC_NETMASK, m_vnetmask);
	DDX_Control(pDX, IDC_IP, m_vip);
	DDX_Text(pDX, IDC_MAC1, m_mac1);
	DDV_MaxChars(pDX, m_mac1, 2);
	DDX_Text(pDX, IDC_MAC2, m_mac2);
	DDV_MaxChars(pDX, m_mac2, 2);
	DDX_Text(pDX, IDC_MAC3, m_mac3);
	DDV_MaxChars(pDX, m_mac3, 2);
	DDX_Text(pDX, IDC_MAC4, m_mac4);
	DDV_MaxChars(pDX, m_mac4, 2);
	DDX_Text(pDX, IDC_MAC5, m_mac5);
	DDV_MaxChars(pDX, m_mac5, 2);
	DDX_Text(pDX, IDC_MAC6, m_mac6);
	DDV_MaxChars(pDX, m_mac6, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CProPage1)
	ON_EN_CHANGE(IDC_MAC1, OnChangeMac1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProPage1 message handlers

void CProPage1::OnChangeMac1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	
}
