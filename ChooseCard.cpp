// ChooseCard.cpp : implementation file
//

#include "stdafx.h"
#include "802_1X Connector.h"
#include "ChooseCard.h"
#include "IPHlpApi.h"
extern IP_ADAPTER_INFO  *pAdapterInfo;
extern FIXED_INFO *pFixedInfo;
extern unsigned char LocalMAC[6];
extern char compile[100];
extern char LocalIP[4];
extern char LocalDNS[4];
extern char LocalNetmask[4];
extern char LocalGateway[4];
extern void FormatCompileMAC(unsigned char*,char *);
extern void FormatIP(unsigned char*,unsigned char*);
extern void GetDNS();
IP_ADAPTER_INFO	*pCurAdapterinfo;
extern int SelectIndex;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseCard dialog


CChooseCard::CChooseCard(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseCard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseCard)
	m_index = -1;
	//}}AFX_DATA_INIT
}


void CChooseCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseCard)
	DDX_LBIndex(pDX, IDC_CARDLIST, m_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseCard, CDialog)
	//{{AFX_MSG_MAP(CChooseCard)
	ON_LBN_SELCHANGE(IDC_CARDLIST, OnSelchangeCardlist)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseCard message handlers
static char descript[100];
BOOL CChooseCard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//MessageBox("进入网卡选择窗口");
		pCurAdapterinfo=pAdapterInfo;
		for(;pAdapterInfo;pAdapterInfo=pAdapterInfo->Next)
		{
		
			strcpy(descript,pAdapterInfo->Description);
			strcat(descript+5,(const char *)pAdapterInfo->IpAddressList.IpAddress.String);
			((CListBox*)GetDlgItem(IDC_CARDLIST))->AddString(descript);
	//((CListBox*)GetDlgItem(IDC_LIST1))->AddString((pAdapterInfo->Description));
		}
	//	MessageBox("显示网卡成功");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseCard::OnOK() 
{
	// TODO: Add extra validation here
	//SelectIndex获取当前选取的Network Card 通过索引来绑定制定的设备
	//if(SelectIndex=((CListBox*)GetDlgItem(IDC_CARDLIST))->GetCurSel()==-1)
	if(SelectIndex==-1)
	{
		MessageBox("没有选择网络适配器!");
	
	}
	else
	{
		//SelectIndex++;
		
		for(pAdapterInfo=pCurAdapterinfo;SelectIndex!=0;SelectIndex--,pAdapterInfo=pAdapterInfo->Next);
		//Copy Network Card MAC To LocalMAC
		memcpy(LocalMAC,pAdapterInfo->Address,6);

		//Copy IP TO LocalIP
		FormatIP((unsigned char *)pAdapterInfo->IpAddressList.IpAddress.String,(unsigned char *)LocalIP);

		//Copy Gateway To LocalGateway
		FormatIP((unsigned char*)pAdapterInfo->GatewayList.IpAddress.String,(unsigned char*)LocalGateway);

		//Copy DNS To LocalDNS
		GetDNS();
		FormatIP((unsigned char*)pFixedInfo->DnsServerList.IpAddress.String,(unsigned char*)LocalDNS);

		//Copy Netmask To LocalNetmask
		FormatIP((unsigned char*)pAdapterInfo->GatewayList.IpAddress.String,(unsigned char*)LocalNetmask);

		FormatCompileMAC(LocalMAC,compile+0xc);
		FormatCompileMAC(LocalMAC,compile+0x49);
		CDialog::OnOK();
	}
	
}

void CChooseCard::OnSelchangeCardlist() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	SelectIndex=((CListBox*)GetDlgItem(IDC_CARDLIST))->GetCurSel();
	
}

void CChooseCard::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	ExitThread(2);
	
	CDialog::OnClose();
}
