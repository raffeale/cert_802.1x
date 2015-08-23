// 802_1X ConnectorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "802_1X Connector.h"
#include "802_1X ConnectorDlg.h"
#include "Choosecard.h"
#include"IPHlpApi.h"
#include "ProSheet.h"


const unsigned int  WaitTimeoutCount=10000;
const unsigned int WaitCheckUserInfo=8000;
const unsigned int WaitCheckPassword=8001;
const unsigned int WaitLoginSucessMsg=8002;
const unsigned int WaitReserveMsg=8003;



extern IP_ADAPTER_INFO  *pAdapterInfo;


	//EAP_Packet RType1;
	//EAP_Packet RType4;

/*	EAP_Packet _connect;
	EAP_Packet *ptr=&_connect;*/
	CString netcardname;
	struct bpf_program fcode;
	u_int netmask;


/*idnumber ids[8]
		=
	{
	{0,"bkzhoujj","\x00\xe0\x4c\xab\x43\x50"},
	{1,"JB","\x00\xe0\x4d\x77\x8d\xfa"},
	{2,"YLS","\x00\xe0\x4c\xe7\xfb\x56"},
	{3,"GYQ","\x00\xe0\x4c\x00\x87\x8c"},
//	{4,"WWW_HZ0752_COM","\x00\x88\x78\x68\x58\x48"},
	{4,"bkyudawei","\x00\x0c\x29\x0b\x6c\x53"},
	{5,"bkleilei","\x00\x11\xd8\x6e\x1b\xab"},
	{6,"Wizard","\x00\xe0\x4d\x21\x13\x7b"},
	{7,"LXY","\x00\x01\x6c\xca\xfb\x23"},
	}; 

*/
	EAP_Packet CurPacket;		//当前将要发送的Packet
	EAP_Packet StartPacket;		//EAP-OL Start Packet
	EAP_Packet LogonPacket;		//EAP Logon Packet
	//EAP_Packet * ptrPacket=&CurPacket;


	IP_ADAPTER_INFO  *pAdapterInfo;
	ULONG            ulOutBufLen=0;
	DWORD            dwRetVal;

//802.1x BroadCast MAC ＝MultiCasting Address
	char BroadCastMAC[6]={'\x01','\x80','\xc2','\x00','\x00','\x03'};
//SWITCH MAC Address
	unsigned char switchmac[6]={'\x00','\x0f','\x3d','\xcb','\x22','\x63'};
//Local MAC、IP、Gateway、DNS
	unsigned char LocalMAC[6];
	char LocalIP[4]={0};
	char LocalNetmask[4]={'\xff','\xff','\xff','\xff'};
	char LocalGateway[4]={0};
	char LocalDNS[4]={0};
	char LocalDHCP[4]={0};
//Virtial IP and Virtual MAC Address
	static unsigned char vmac[6];

//UserName And Password	
	char UserNameBuf[10]={0};
	char PasswordBuf[10]={0};
	
//NetworkCard of Index by user selected	
	int SelectIndex=-1;
//Connected Flag and Disconnect FLag
	bool Connected=false;
	BOOL DisconnectFlag=false;
	bool authorserverflag=false;
	bool FoundServerFlag=false;

//pcap_compile string
	char compile[]="ether dst ( 00:00:00:00:00:00 or 01:80:C2:00:00:03 ) and ( not ether src 00:00:00:00:00:00 )  and ether proto 0x888E";
	
//MD5 Challenge Key
	unsigned char md5key[50]={'\x03'};
	char md5string[10]={'\x78','\x78','\x67','\x68','\x6C','\x6D','\x78','\x68','\x7A','\x62'};
//CButton pointer
	CButton *_discon=NULL;
	CButton *_connect=NULL;
//HWND 
	HWND dlghwnd=0;

	CListCtrl *pDlg=NULL;
//Registry 
	HKEY hKEY;
	LPCTSTR data_Set="Software\\D-Link\\8021X\\LinkName\\Name1";
	LPCTSTR data_Username="Software\\D-Link\\8021X\\LinkName\\Name1\\UserName";
	LPCTSTR data_Password="Software\\D-Link\\8021X\\LinkName\\Name1\\Password";
	LPCTSTR data_SaveFlag="Software\\D-Link\\8021X\\LinkName\\Name1\\SaveFlag";
	LPBYTE username=new BYTE[20]; 
	LPBYTE password=new BYTE[20]; 
	LPBYTE FLAG=new BYTE[20]; 

	
	DWORD type_1=REG_SZ ; 
	DWORD cbData_1=20;
	BOOL SaveFlag;
	BOOL FoundReserveMsg=false;
//Virtual MAC Address Setting
	BOOL vmaccheck=false;
	BOOL vipcheck=false;






//	Clear MD5Key Buffer
	void ClearMD5Key()
	{
		for(int i=1;i<49;i++)
			md5key[i]=0x0;
	}
	void InitPacket(EAP_Packet *ptr_Packet)		//Init CurPacket；
	{
		//ptrPacket=&CurPacket;
			ptr_Packet->EAP_Data_Type=0x0;
			ptr_Packet->EAPheader_code=0x0;
			ptr_Packet->EAPheader_id=0x0;
			ptr_Packet->EAPheader_len=0x0;
			ptr_Packet->EType[0]=0x88;
			ptr_Packet->EType[1]=0x8e;
			ptr_Packet->EType[2]=0x00;
			ptr_Packet->EType[3]=0x00;

		for (int i=0;i<6;i++)	//init LocalMAC and BroadcastMAC
		{
			ptr_Packet->MAC_DEST[i]=BroadCastMAC[i];
			ptr_Packet->MAC_SRC[i]=LocalMAC[i];
		}
		for(i=0;i<16;i++)
			ptr_Packet->msgs.md5_msg.md5challenge[i]=0x0;
		for(i=0;i<18;i++)
			ptr_Packet->msgs.md5_msg.username[i]=0x0;
		ptr_Packet->msgs.md5_msg.value_size=0x0;

	}
//Convert HEX MAC to MAC string
	void FormatCompileMAC(unsigned char *srcmac, char *dest)
	{
		unsigned int i=0,j=0;
		for(;i<3*6;i=i+3,j++)
		{
		sprintf(&dest[i],"%.2x",srcmac[j]);
		dest[i+2]=':';
		}
		dest[i-1]=' ';
	}


	
//convert IP String to hex IP 
	void FormatIP(unsigned char * srcbuf,unsigned char *destbuf)
	{
		static char point[3];
		unsigned int i=0,j=0;
		for(i=0;i<strlen((const char *)srcbuf);i++)
		{
			if(srcbuf[i]=='.') 
			{
				point[j]=i;
				j++;
			}
		}
		for(i=0;i<4;i++)
		{
			if(i==0)
			{
				destbuf[i]=(unsigned char)atoi((const char*)srcbuf);
			}
			else
			{
				destbuf[i]=(unsigned char)atoi((const char *)srcbuf+((unsigned char)point[i-1])+0x1);
			}
			
		}
	}
//Get DNS Address
	FIXED_INFO  *pFixedInfo;
	void GetDNS()
	{
		
		ULONG       ulOutBufLen;
		DWORD       dwRetVal;
		pFixedInfo = (FIXED_INFO *) malloc( sizeof( FIXED_INFO ) );
		ulOutBufLen = sizeof( FIXED_INFO );
		if ( GetNetworkParams( pFixedInfo, &ulOutBufLen ) == ERROR_BUFFER_OVERFLOW ) 
		{
			GlobalFree( pFixedInfo );
		pFixedInfo = (FIXED_INFO *) malloc( ulOutBufLen );
		}
		if ( dwRetVal = GetNetworkParams( pFixedInfo, &ulOutBufLen ) != NO_ERROR) 
		{
			::MessageBox(NULL,"Call to GetNetworkParams failed","802.1X",MB_OK);
		}

	}


	void InitStartPackt()
	{
		InitPacket(&StartPacket);
		StartPacket.EType[2]=0x01;		//Version 1
		StartPacket.EType[3]=0x01;	//Packet Type 1=EAP-OL Start

	}

	void InitUserPacket()
	{
		CurPacket.msgs.user.VerHighWord[0]='0';
		CurPacket.msgs.user.VerHighWord[1]='4';
		CurPacket.msgs.user.VerLowWord[0]='0';
		CurPacket.msgs.user.VerLowWord[1]='6';
		CurPacket.msgs.user.VerMiddleWord[0]='0';
		CurPacket.msgs.user.VerMiddleWord[1]='2';
		CurPacket.msgs.user.flag=1;
		CurPacket.msgs.user.chart1=(unsigned char)'.';
		CurPacket.msgs.user.chart2=(unsigned char)'.';
		CurPacket.EType[2]='\x01';
		CurPacket.EType[3]='\x00';
		CurPacket.packlen=39<<8;
		memcpy(CurPacket.msgs.user.gateway,LocalGateway,4);
		memcpy(CurPacket.msgs.user.ipaddr,LocalIP,4);
		memcpy(CurPacket.msgs.user.netmask,LocalNetmask,4);
		for(unsigned int i=0;UserNameBuf[i];i++)
			CurPacket.msgs.user.username[i]=UserNameBuf[i];
		short int len=strlen(UserNameBuf);
		CurPacket.EAPheader_len=(0x27-(unsigned char)(9-len))<<8;
		CurPacket.packlen=(0x27-(unsigned char)(9-len))<<8;
				
	}

	void InitMD5Key()
	{
		for(int i=1;i<49;i++)
			md5key[i]=0x0;
	}
//为Password Packet赋初始值

	void InitPasswordPacket()
	{
	
		CurPacket.msgs.md5_msg.value_size=0x10;
		memcpy(CurPacket.msgs.md5_msg.username,UserNameBuf,strlen(UserNameBuf)-1);
		CurPacket.EAPheader_code=0x2;
		short int len=strlen(UserNameBuf);
		CurPacket.EAPheader_len=(0x1f-(unsigned char)(9-len))<<8;
		CurPacket.packlen=(0x1f-(unsigned char)(9-len))<<8;
		//CurPacket.EAPheader_len=0x1f<<8;
		CurPacket.EAP_Data_Type=0x4;
		//CurPacket.EAPheader_code=0x1;
		CurPacket.EType[2]=0x1;
		//InitMD5Key();
		//ClearMD5Key();
		strcat((char *)md5key,PasswordBuf);
		strcat((char *)md5key,md5string);
	}

//为Logon Packet赋初始值

	void InitLogonPacket()
	{
		InitPacket(&LogonPacket);
		LogonPacket.EType[2]=0x01;	//Version 1
		LogonPacket.EType[3]=0x02;	//Packet Type 1=EAP-OL Start
	}


	void InitBuffer(char * ptrBuf,unsigned int i)
	{
		for(unsigned int j=0;j<i;j++)
			ptrBuf[j]=0x0;


	}



	void InitNetworkInfo()
	{
		//	MessageBox("只有一个网卡启用中！");
		//Copy Network Card MAC To LocalMAC
		memcpy(LocalMAC,pAdapterInfo->Address,6);

		//Copy IP TO LocalIP
		FormatIP((unsigned char *)pAdapterInfo->IpAddressList.IpAddress.String,(unsigned char *)LocalIP);

		//Copy Gateway To LocalGateway
		FormatIP((unsigned char*)pAdapterInfo->GatewayList.IpAddress.String,(unsigned char*)LocalGateway);

		//Copy DNS To LocalDNS
		GetDNS();
		FormatIP((unsigned char*)pFixedInfo ->DnsServerList.IpAddress.String,(unsigned char*)LocalDNS);

		//Copy Netmask To LocalNetmask
		//FormatIP((unsigned char*)pAdapterInfo->GatewayList.IpAddress.String,(unsigned char*)LocalNetmask);
		FormatIP((unsigned char*)pAdapterInfo->IpAddressList.IpMask.String,(unsigned char*)LocalNetmask);

		FormatCompileMAC(LocalMAC,compile+0xc);
		FormatCompileMAC(LocalMAC,compile+0x49);
	//	MessageBox("初始化网卡参数完成");
	}

	//unsigned int m_nIndex;
	pcap_if_t *alldevs;
	pcap_if_t *d;
	pcap_if_t *curcard;
	pcap_t* adhandle;
	char errbuf[PCAP_ERRBUF_SIZE]; 
	
/*

	void initRType1()
	{
	RType1.msgs.user.flag=1;
	RType1.msgs.user.chart1=(unsigned char)'.';
	RType1.msgs.user.chart2=(unsigned char)'.';
	RType1.msgs.user.gateway[0]=(char)219;
	RType1.msgs.user.gateway[1]=(char)242;
	RType1.msgs.user.gateway[2]=(char)90;
	RType1.msgs.user.gateway[3]=(char)1;
	RType1.msgs.user.ipaddr[0]=(char)219;
	RType1.msgs.user.ipaddr[1]=(char)242;
	RType1.msgs.user.ipaddr[2]=(char)90;
	RType1.msgs.user.ipaddr[3]=(char)204;
	RType1.msgs.user.VerHighWord[0]='0';
	RType1.msgs.user.VerHighWord[1]='4';
	RType1.msgs.user.VerLowWord[0]='0';
	RType1.msgs.user.VerLowWord[1]='6';
	RType1.msgs.user.VerMiddleWord[0]='0';
	RType1.msgs.user.VerMiddleWord[1]='2';
	RType1.msgs.user.netmask[0]=(unsigned char)255;
	RType1.msgs.user.netmask[1]=(unsigned char)255;
	RType1.msgs.user.netmask[2]=(unsigned char)255;
	RType1.msgs.user.netmask[3]=(unsigned char)0;
	RType1.MAC_DEST[0]='\x01';
	RType1.MAC_DEST[1]='\x80';
	RType1.MAC_DEST[2]='\xc2';
	RType1.MAC_DEST[3]='\x00';
	RType1.MAC_DEST[4]='\x00';
	RType1.MAC_DEST[5]='\x03';
	RType1.MAC_SRC[0]='\x00';
	RType1.MAC_SRC[1]='\x0c';
	RType1.MAC_SRC[2]='\x29';
	RType1.MAC_SRC[3]='\x0b';
	RType1.MAC_SRC[4]='\x6c';
	RType1.MAC_SRC[5]='\x53';
	RType1.EType[0]='\x88';
	RType1.EType[1]='\x8e';
	RType1.EType[2]='\x01';
	RType1.EType[3]='\x00';
	RType1.packlen=39<<8;
	for(unsigned int i=0;i<strlen(ids[4].name);i++)
	RType1.msgs.user.username[i]=ids[4].name[i];
	}

	void initRType4()
	{	
	RType4.MAC_DEST[0]='\x01';
	RType4.MAC_DEST[1]='\x80';
	RType4.MAC_DEST[2]='\xc2';
	RType4.MAC_DEST[3]='\x00';
	RType4.MAC_DEST[4]='\x00';
	RType4.MAC_DEST[5]='\x03';
	RType4.MAC_SRC[0]='\x00';
	RType4.MAC_SRC[1]='\x0c';
	RType4.MAC_SRC[2]='\x29';
	RType4.MAC_SRC[3]='\x0b';
	RType4.MAC_SRC[4]='\x6c';
	RType4.MAC_SRC[5]='\x53';
	RType4.EType[0]='\x88';
	RType4.EType[1]='\x8e';
	RType4.EType[2]='\x01';
	RType4.EType[3]='\x00';
	RType4.packlen=0x1f<<8;			//长度必须正确，否则无反馈
		for(unsigned int i=0;i<strlen(ids[4].name);i++)
	RType1.msgs.md5_msg.username[i]=ids[4].name[i];
	
	}
*/



	void CALLBACK MyTimerProc(
HWND hwnd, 
UINT uMsg, 
UINT idEvent, 
DWORD dwTime )
{
					::KillTimer(dlghwnd,1);
					::KillTimer(dlghwnd,5);
					_connect->EnableWindow();
					_discon->EnableWindow(false);
					DisconnectFlag=false;
					authorserverflag=false;
					FoundServerFlag=false;
					Connected=false;
					
					pcap_freecode(&fcode);
					pcap_close(adhandle);
					RegCloseKey(hKEY);

					pDlg->InsertItem(201,"成功与服务器断开连接!");
					//ExitThread(1);
					//::TerminateThread(m_tHandle,2);

}


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//嵌入
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy802_1XConnectorDlg dialog

CMy802_1XConnectorDlg::CMy802_1XConnectorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy802_1XConnectorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy802_1XConnectorDlg)
	m_username = _T("");
	m_password = _T("");
	m_time = _T("");
	m_saveflag = FALSE;
	m_vip = FALSE;
	m_vmac = FALSE;
	//}}AFX_DATA_INIT
			
	


	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy802_1XConnectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy802_1XConnectorDlg)
	DDX_Control(pDX, IDC_USERPWD, m_userinfo);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	DDX_Control(pDX, IDC_DISCONNECT, m_disconnect);
	DDX_Control(pDX, IDC_CONNECT, m_connect);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDV_MaxChars(pDX, m_username, 10);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDV_MaxChars(pDX, m_password, 8);
	DDX_Text(pDX, IDC_TIME, m_time);
	DDX_Check(pDX, IDC_CHECK1, m_saveflag);
	DDX_Check(pDX, IDC_VIPCHECK, m_vip);
	DDX_Check(pDX, IDC_VMACCHECK, m_vmac);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy802_1XConnectorDlg, CDialog)
	//{{AFX_MSG_MAP(CMy802_1XConnectorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CONFIG, OnConfig)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_VMACCHECK, OnVmaccheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy802_1XConnectorDlg message handlers


BOOL CMy802_1XConnectorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	_connect=(CButton *)GetDlgItem(IDC_CONNECT);
	_discon=(CButton *)GetDlgItem(IDC_DISCONNECT);
	dlghwnd=this->m_hWnd;
//	MessageBox("开始分配内存");


	pAdapterInfo = (IP_ADAPTER_INFO *) new IP_ADAPTER_INFO[10];
	ulOutBufLen = sizeof(IP_ADAPTER_INFO);

if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS) {
    delete pAdapterInfo;

    //pAdapterInfo=(IP_ADAPTER_INFO *) malloc(sizeof(ulOutBufLen));
	pAdapterInfo=(IP_ADAPTER_INFO *) new IP_ADAPTER_INFO[10];
}
//	MessageBox("分配内存中...");

if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != ERROR_SUCCESS) {
	::MessageBox(NULL,"Call to GetAdaptersInfo failed.","802.1x Connector",MB_OK);
	
	ExitProcess(-1);
}
//	MessageBox("分配内存成功");


// ::MessageBox(NULL,pAdapterInfo->Description,"Network Card:",MB_OK);




//添加Header
	CListCtrl *mylist=(CListCtrl*)GetDlgItem(IDC_LIST1);
	mylist->InsertColumn(1,"                  连   接   状   态", LVCFMT_LEFT,400,1);
//	mylist->SetExtendedStyle(LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE);

	m_disconnect.EnableWindow(false);
//显示选择对话框
//	MessageBox("检查网卡数量");

	if(!pAdapterInfo->AdapterName)	//Not Found Network Card
	{
		MessageBox("没有可用的网络适配器可用,请检查网卡是否正常工作!");
		ExitProcess(-2);
	}
	else if(pAdapterInfo->Next)		//Found Network card one more
	{
	//	MessageBox("准备打开选择网卡窗口!");
	CChooseCard *carddlg=new CChooseCard;
	carddlg->DoModal();
	return true;
	}
	else						//Found a Network Card
	{
	
		InitNetworkInfo();
	}

	GetRegistryInfo();
	InitBuffer(UserNameBuf,10);
	InitBuffer(PasswordBuf,10);
	GetDlgItemText(IDC_EDIT1,UserNameBuf,10);
	GetDlgItemText(IDC_EDIT2,PasswordBuf,10);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy802_1XConnectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy802_1XConnectorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy802_1XConnectorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*void CMy802_1XConnectorDlg::OnQuit() 
{
	// TODO: Add your control notification handler code here
	
	
}
*/



DWORD WINAPI ThreadProc(LPVOID lpParameter)
{


	pcap_loop(adhandle,0,CMy802_1XConnectorDlg::packet_handler, NULL);
	//::MessageBox(NULL,"Packet Handling线程退出","802.1x",MB_OK);		
		pcap_close(adhandle);
//	while (1) 
//	{

//		Sleep(100);
//	}
		
		return 1;
}




void CMy802_1XConnectorDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
	Connected=false;
	DisconnectFlag=false;
	FoundServerFlag=false;
	char ndis[]="Generic NdisWan adapter";

		((CListCtrl *)GetDlgItem(IDC_LIST1))->DeleteAllItems();
	

		if(!(strlen(UserNameBuf)&&strlen(PasswordBuf)))
	{
		MessageBox("没有输入用户名与密码");
		return;
	}


	pcap_findalldevs(&alldevs,errbuf); // 获得网络设备指针 

	for(d=alldevs;d;d=d->next) // 枚举网卡
	{ 
		if(!memcmp(ndis,d->description,22)) continue;
		netcardname=d->name; // d->name就是我们需要的网卡名字字符串
		curcard=d;
	} 


	if((adhandle=pcap_open_live(netcardname,128,1,1000,errbuf))==NULL)
	{
		::MessageBox(NULL,"网卡打开失败!\n\r请确定正常安装Winpcap驱动","802.1x",MB_OK);
		ExitProcess(-3);
	}
	else
	{

	
		if(curcard->addresses != NULL)
    /* 获得第一个接口地址的掩码 */
		netmask=((struct sockaddr_in *)(curcard->addresses->netmask))->sin_addr.S_un.S_addr;
		else
			/* 如果这个接口没有地址那么我们假设他为C类地址 */
			netmask=0xffffff; 
		
		pcap_compile(adhandle,&fcode,compile,1,netmask);
		pcap_setfilter(adhandle,&fcode);
		pcap_freealldevs(alldevs);

		pDlg=(CListCtrl*)GetDlgItem(IDC_LIST1);

		m_tHandle=CreateThread(NULL,NULL,ThreadProc,NULL,0,NULL);
	CloseHandle(m_tHandle);

	
		((CListCtrl *)GetDlgItem(IDC_LIST1))->InsertItem(102,"正在搜索认证服务器...\n\r");

	//建立 EAP-OL Start 连接请求
		SetTimer(1,3000,0);
		InitStartPackt();
	pcap_sendpacket(adhandle,(unsigned char *)&StartPacket,60); 
	m_connect.EnableWindow(false);
	m_disconnect.EnableWindow();
	m_disconnect.SetWindowText("停止搜索");
	}
	
}


void CMy802_1XConnectorDlg::OnDisconnect() 
{
	// TODO: Add your control notification handler code here
	
	//TerminateThread(m_tHandle,1);
	m_disconnect.SetWindowText("断开连接");
	DisconnectFlag=true;
	
//	::KillTimer(dlghwnd,1);
	//KillTimer(1);
	if(authorserverflag)
	{
		InitLogonPacket();
		pcap_sendpacket(adhandle,(unsigned char *)&LogonPacket,60);
		((CListCtrl *)GetDlgItem(IDC_LIST1))->InsertItem(1000,"正在与服务器断开连接...");
	

		//pcap_close(adhandle);

		//DisconnectFlag=false;
		//authorserverflag=false;
		//FoundServerFlag=false;
		//Connected=false;
		//m_connect.EnableWindow();
		//m_disconnect.EnableWindow(false);
		DisconnectFlag=true;
			::SetTimer(dlghwnd,5,1000,MyTimerProc);
		//::KillTimer(dlghwnd,2);
		//delete[10] pAdapterInfo;
		
	}
	else
	{
		/*
		::KillTimer(dlghwnd,1);
		delete[10] pAdapterInfo;
		pcap_close(adhandle);
		m_connect.EnableWindow();
		m_disconnect.EnableWindow(false);
		DisconnectFlag=false;
		authorserverflag=false;
		FoundServerFlag=false;
		Connected=false;
		pcap_close(adhandle);
		::KillTimer(dlghwnd,2);
		*/
			DisconnectFlag=true;
		
			::SetTimer(dlghwnd,5,1000,MyTimerProc);
	}
	

	
}

CDialog *dlg;
void CMy802_1XConnectorDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
		
	dlg=new CDialog(IDD_ABOUTBOX,NULL);
	dlg->DoModal();

}

void CMy802_1XConnectorDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if(IDNO==AfxMessageBox("确定要退出吗?",MB_YESNO |MB_ICONEXCLAMATION,-1))
	{
		return;
	}
	else //IDYES 处理
	{
		if(Connected) //检查是否已经建立连接
		{
			if(IDNO==AfxMessageBox("网络已经建立连接，是否要断开网络?",MB_YESNO|MB_ICONEXCLAMATION,-1))
			{
				return;
			}
			else
			{
				DisconnectFlag=true;
				InitLogonPacket();
				pcap_sendpacket(adhandle,(unsigned char *)&LogonPacket,60);
				free(pFixedInfo);
				CDialog::OnClose();
			}
		}
		else
		{
			CDialog::OnClose();
		}
		
	}
	
}






MD5_CTX mymd5;
//EAP_Packet resver;

void CMy802_1XConnectorDlg::packet_handler(u_char *param, const pcap_pkthdr *header, const u_char *pkt_data)
{
	//unsigned char mymac[6]={'\x00','\x0c','\x29','\x0b','\x6c','\x53'};
	
	u_char PType[4] = {0x88, 0x8e, 0x01, 0x00};
	unsigned char len;

	//	pDlg->InsertItem(104,"hello");
//使用switch时候对单字节case不能使用转义字符和单引号的字符
//	if (!memcmp(pkt_data+0xc,PType, 2)&& (!memcmp(pkt_data+0x0,mymac,6)||!memcmp(pkt_data+0x6,switchmac,6)))

//	if (!memcmp(pkt_data+0xc,PType, 2)&& //判断是否为802.1X协议
		if((!memcmp(pkt_data+0x0,LocalMAC,6)||  //判断目的地址是否为本地地址
		!memcmp(pkt_data+0x6,switchmac,6))) //判断原地址是否为交换机MAC
	{ 
		if(*(pkt_data+0xf)>0x0)
		{
		/*	resver.MAC_DEST[0]='\x01';
			resver.MAC_DEST[1]='\x80';
			resver.MAC_DEST[2]='\xc2';
			resver.MAC_DEST[3]='\x00';
			resver.MAC_DEST[4]='\x00';
			resver.MAC_DEST[5]='\x03';
			resver.MAC_SRC[0]='\x00';
			resver.MAC_SRC[1]='\x0c';
			resver.MAC_SRC[2]='\x29';
			resver.MAC_SRC[3]='\x0b';
			resver.MAC_SRC[4]='\x6c';
			resver.MAC_SRC[5]='\x53';
			resver.EType[0]='\x88';
			resver.EType[1]='\x8e';
			resver.EType[2]=*(pkt_data+0xf)+1;
			resver.EType[3]='\x00';
			pcap_sendpacket(adhandle,(unsigned char *)&resver,60);
			//return;
			*/
			if(Connected) //验证是否已经连接，如果没有连接就不给予Reserved PACKET的回应
			{
				FoundReserveMsg=true;
			InitPacket(&CurPacket);
			CurPacket.packlen=0;
			CurPacket.EType[2]=0x1;
			CurPacket.EType[3]=*(pkt_data+0xf)+1;
			pcap_sendpacket(adhandle,(unsigned char *)&CurPacket,60);
			}

		}
		else{
			switch(*(pkt_data+0x12)) //EAP Code
			{
			case 0x0: break;
			
			case 0x1:			//EAP Code 1=Request Packet
				switch((char)* (pkt_data+0x16)) //EAP Type
				{
				
				case 0x1:		//Request Type 1=Identify Type(user name&&net information)
				
				if(DisconnectFlag==FALSE)
				{
					FoundServerFlag=true;

				
				if(!authorserverflag)
				pDlg->InsertItem(119,"发现认证服务器.");
				_discon->SetWindowText("断开连接");
				::KillTimer(dlghwnd,1);
				
				/*
				RType1.EAPheader_id=(unsigned char)(*(pkt_data+0x13));
				RType1.EAPheader_code=(unsigned char)'\x2';	//EAP code 2=Respone Packet
				RType1.EAP_Data_Type=(unsigned char)'\x1';
				RType1.EAPheader_len=(unsigned short int)0x27<<8;
				initRType1();
				*/
				
				InitPacket(&CurPacket);
				InitUserPacket();
				CurPacket.EAPheader_id=(unsigned char)(*(pkt_data+0x13));
				CurPacket.EAPheader_code=(unsigned char)'\x2';
				CurPacket.EAP_Data_Type=(unsigned char)'\x1';

				//CurPacket.EAPheader_len=(unsigned short int)0x27<<8;
				//pcap_sendpacket(adhandle,(unsigned char *)&RType1,60);
				
				pcap_sendpacket(adhandle,(unsigned char *)&CurPacket,60);
				if(!authorserverflag) 
				pDlg->InsertItem(120,"正在验证用户名...");
				//SetTimer(WaitCheckUserInfo,WaitTimeoutCount,NULL);
				::SetTimer(dlghwnd,WaitCheckUserInfo,WaitTimeoutCount,NULL);

			
				authorserverflag=true;
				break;
				}

				break;

//				return;

				case 0x3:		//Request Type=3 EAP NAK 
					InitPacket(&CurPacket);
					CurPacket.EAPheader_id=(unsigned char)(*(pkt_data+0x13));
					CurPacket.EAPheader_len=(unsigned char)0x6>>8;
					CurPacket.EAP_Data_Type=(unsigned char)0x3;
					CurPacket.EAPheader_code=(unsigned char)0x2;
					CurPacket.packlen=(unsigned char)0x6>>8;
					CurPacket.msgs.user.flag=(unsigned char)0xd;
					pcap_sendpacket(adhandle,(unsigned char *)&CurPacket,60);
					break;

				case 0x4:		//Request Type 4=md5 challenge type(md5 password)
				/*initRType4();*/
				//strcat(md5key,pkt_data+0x18);
				
				::KillTimer(dlghwnd,WaitCheckUserInfo);
				InitPacket(&CurPacket);
				InitPasswordPacket();
				len=strlen((const char*)md5key);
				memcpy(md5key+len,pkt_data+0x18,16);
				md5key[0]=(unsigned char)(*(pkt_data+0x13));
				
				mymd5.MD5Update(md5key,len+16);
				mymd5.MD5Final(CurPacket.msgs.md5_msg.md5challenge);
				
				
			//	memcpy(RType4.msgs.md5_msg.username,ids[4].name,strlen(ids[4].name));
			/*	RType4.EAPheader_id=(unsigned char)(*(pkt_data+0x13));
				RType4.msgs.md5_msg.value_size=0x10;
				RType4.EAPheader_code=0x2;
				RType4.EAPheader_len=0x1f<<8;
				RType4.EAP_Data_Type=0x4;
//				RType4.packlen=((short int)strlen((const char *)RType4.EAPheader_code)-1)<<8;
			*/
				CurPacket.EAPheader_id=(unsigned char)(*(pkt_data+0x13));
				memcpy(CurPacket.msgs.md5_msg.username,UserNameBuf,strlen(UserNameBuf));
				
				//pcap_sendpacket(adhandle,(unsigned char *)&RType4,60);
				//Sleep(1000);
				pcap_sendpacket(adhandle,(unsigned char *)&CurPacket,60);
				pDlg->InsertItem(121,"正在验证密码...");
				::SetTimer(dlghwnd,WaitLoginSucessMsg,8000,NULL);
				
				ClearMD5Key();
				break;
				
				case 0x2:
				pDlg->InsertItem(122,(const char*)pkt_data+0x17);
				
				default:break;
				}break;		//'0x1' break
				
				case 0x3:			//EAP Code 3=Success Packet
				::KillTimer(dlghwnd,WaitLoginSucessMsg);
				pDlg->InsertItem(200,"成功与服务器建立连接!");
				::SetTimer(dlghwnd,2,1000,NULL);
				Connected=true;
				::SetTimer(dlghwnd,WaitReserveMsg,250000,NULL);
				
				break;
			
			case 0x4:
				
				if(Connected)
				{
					DisconnectFlag=true;
				::SetTimer(dlghwnd,5,1000,MyTimerProc);
				}

				if(FoundServerFlag)
				{
					
					DisconnectFlag=true;
				::SetTimer(dlghwnd,5,1000,MyTimerProc);
				}
				
				/*if((unsigned char)*(pkt_data+0x13)==0x0)
				{
					pDlg->InsertItem(201,"成功与服务器断开连接!");
					_connect->EnableWindow();
					_discon->EnableWindow(false);
					DisconnectFlag=false;
					authorserverflag=false;
					FoundServerFlag=false;
					Connected=false;
					::KillTimer(dlghwnd,1);
					::KillTimer(dlghwnd,2);
					pcap_close(adhandle);
					RegCloseKey(hKEY);
					ExitThread(1);
				}
				else
				{
					pDlg->InsertItem(202,"密码错误,请核实密码后重新连接!");
					_connect->EnableWindow();
					_discon->EnableWindow(false);
					DisconnectFlag=false;
					authorserverflag=false;
					FoundServerFlag=false;
					Connected=false;
					::KillTimer(dlghwnd,1);
					pcap_close(adhandle);
					RegCloseKey(hKEY);
					ExitThread(1);
				}*/
				DisconnectFlag=true;
				break;

		default: break;
		}
		}
	}

}


void CMy802_1XConnectorDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	for(int i=0;i<10;i++) UserNameBuf[i]=0x0;
	GetDlgItemText(IDC_EDIT1,UserNameBuf,10);
	UpdateData(false);

}

void CMy802_1XConnectorDlg::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	UpdateData();
	for(int i=0;i<10;i++) PasswordBuf[i]=0x0;
	GetDlgItemText(IDC_EDIT2,PasswordBuf,9);
	UpdateData(false);
}


//CWnd *pcwnd=new CWnd;
void CMy802_1XConnectorDlg::OnTimer(UINT nIDEvent) 
{
		static unsigned long int second=0;
		static char buffer[100];
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==1)
	{
		if (FoundServerFlag==false)	//Not Found Authorize Server
		{
			pDlg->InsertItem(2100,"搜索认证服务器超时,正在重新搜索认证服务器.");
			pDlg->InsertItem(2101,"正在搜索认证服务器...");
			//建立 EAP-OL Start 连接请求
			InitStartPackt();
			pcap_sendpacket(adhandle,(unsigned char *)&StartPacket,60); 
		}
		else
		{
			
		//	KillTimer(1);
			::KillTimer(dlghwnd,1);
			//KillTimer(1);
		}
	}
	if (DisconnectFlag)
	{
		//KillTimer(1);
		::KillTimer(dlghwnd,1);
		::KillTimer(dlghwnd,2);
		second=0;
		//KillTimer(1);
	}

	if (nIDEvent==2) //nIDEvent=2 is update Online time Infomation
	{

		second++;
		if(second/3600)
		{
			InitBuffer(buffer,sizeof(buffer));
			wsprintf(buffer,"%2d小时%2d分钟%2d秒",second/3600,second/60%60,second%60);
			SetDlgItemText(IDC_TIME,buffer);

		}
		else if(second/60)
		{
			InitBuffer(buffer,sizeof(buffer));
			wsprintf(buffer,"%2d 分钟 %2d 秒",second/60,second%60);
			SetDlgItemText(IDC_TIME,buffer);

		}
		else
		{
			InitBuffer(buffer,sizeof(buffer));
			wsprintf(buffer,"%2d 秒",second%60);
			SetDlgItemText(IDC_TIME,buffer);

		}
		

	}

	else if(nIDEvent==WaitCheckUserInfo)	//等待密码验证请求是否超时
	{
		::KillTimer(dlghwnd,WaitCheckUserInfo);
		pDlg->InsertItem(3000,"验证用户信息超时,正在重新认证!");
		InitPacket(&CurPacket);
		InitLogonPacket();
		pcap_sendpacket(adhandle,(unsigned char *)&LogonPacket,60);
		FoundServerFlag=false;
		InitPacket(&CurPacket);
		InitStartPackt();
		SetTimer(1,3000,0);
		pcap_sendpacket(adhandle,(unsigned char *)&StartPacket,60); 
		

	}
	else
		if(nIDEvent==WaitLoginSucessMsg)		//等待登陆成功信息是否超时
	{
		::KillTimer(dlghwnd,WaitLoginSucessMsg);
		pDlg->InsertItem(3001,"验证用户密码超时,正在重新认证!");
		//KillTimer(WaitLoginSucessMsg);
		InitPacket(&CurPacket);
		InitLogonPacket();
		pcap_sendpacket(adhandle,(unsigned char *)&LogonPacket,60);
		FoundServerFlag=false;
		InitPacket(&CurPacket);
		InitStartPackt();
		SetTimer(1,3000,0);
		pcap_sendpacket(adhandle,(unsigned char *)&StartPacket,60);

	}
	else if(nIDEvent==WaitReserveMsg&&DisconnectFlag==false)		//等待Reserve Packet是否超时
	{
		if(!FoundReserveMsg)
		{
			CheckNetCard();
			if(dwRetVal==ERROR_SUCCESS)
			{
				::KillTimer(dlghwnd,FoundReserveMsg);
				pDlg->InsertItem(3002,"网络故障:与服务器的连接被强迫断开,正在重新认证!");
				InitPacket(&CurPacket);
				InitLogonPacket();
				pcap_sendpacket(adhandle,(unsigned char *)&LogonPacket,60);
				FoundServerFlag=false;
				InitPacket(&CurPacket);
				InitStartPackt();
				SetTimer(1,3000,0);
				pcap_sendpacket(adhandle,(unsigned char *)&StartPacket,60);
			}
			else KillTimer(WaitReserveMsg);
			
		}
		FoundReserveMsg=false;
	}
	CDialog::OnTimer(nIDEvent);
}

void CMy802_1XConnectorDlg::GetRegistryInfo()
{
	long ret0=(::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set, 0, KEY_READ|KEY_WRITE, &hKEY));
	if(ret0!=ERROR_SUCCESS) //如果无法打开hKEY，则终止程序的执行 
	{
		RegCreateKey(HKEY_CURRENT_USER,data_Set,&hKEY);
		MessageBox("错误0: 无法打开有关的hKEY!"); 
		//return;
	}

	long ret1=::RegQueryValueEx(hKEY, "UserName", NULL, &type_1, username, &cbData_1); 
	if(ret1!=ERROR_SUCCESS) 
	{ 
		RegCreateKey(HKEY_CURRENT_USER,data_Username,&hKEY);
		MessageBox("错误1: 无法查询有关注册表信息!"); 
		//return ; 
	} 
	ret1=::RegQueryValueEx(hKEY, "Password", NULL, &type_1, password, &cbData_1); 
	if(ret1!=ERROR_SUCCESS) 
	{ 
		RegCreateKey(HKEY_CURRENT_USER,data_Password,&hKEY);
		MessageBox("错误2: 无法查询有关注册表信息!"); 
		//return ; 
	} 

/*	ret1=::RegQueryValueEx(hKEY, "SaveFlag", NULL, &type_1, FLAG, &cbData_1); 
	if(ret1!=ERROR_SUCCESS) 
	{ 
		RegCreateKey(HKEY_CURRENT_USER,data_SaveFlag,&hKEY);
		MessageBox("错误3: 无法查询有关注册表信息!"); 
		//return ; 
	} 

	m_username=username;
	m_password=password;
	if(*FLAG=='1')
		m_saveflag=true;
	else
		m_saveflag=false;

		//((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(1);
	UpdateData(false);
*/

}

void CMy802_1XConnectorDlg::OnConfig() 
{
	// TODO: Add your control notification handler code here

	CProSheet ConfigSheet("高级选项设置");
	ConfigSheet.DoModal();
}

void CMy802_1XConnectorDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	if(((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		InitBuffer(UserNameBuf,sizeof(UserNameBuf));
		GetDlgItemText(IDC_EDIT1,UserNameBuf,10);
		RegSetValue(HKEY_CURRENT_USER,"UserName",NULL,UserNameBuf,strlen(UserNameBuf)-1);
		InitBuffer(PasswordBuf,sizeof(PasswordBuf));
		GetDlgItemText(IDC_EDIT2,PasswordBuf,10);
		RegSetValue(HKEY_CURRENT_USER,"Password",NULL,PasswordBuf,strlen(PasswordBuf)-1);
		RegSetValue(HKEY_CURRENT_USER,"SaveFlag",NULL,"1",1);
	}

}

void CMy802_1XConnectorDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
	CMy802_1XConnectorDlg::OnConnect();
}

void CMy802_1XConnectorDlg::OnVmaccheck() 
{
	// TODO: Add your control notification handler code here


	if(m_vmac)
	{
		((CButton *)GetDlgItem(IDC_EDIT1))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_EDIT2))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_CHECK1))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_VIPCHECK))->EnableWindow(true);
		_connect->SetWindowText("建立连接");
		_discon->SetWindowText("断开连接");
		
		vmaccheck=true;
		m_vmac=false;
	}
	else
	{


		((CButton *)GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_CHECK1))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_VIPCHECK))->EnableWindow(FALSE);
		_connect->SetWindowText("绑定VMAC");
		_discon->SetWindowText("取消绑定");
		vmaccheck=false;
		m_vmac=true;
	}
	
}

void CMy802_1XConnectorDlg::CheckNetCard()
{
	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != ERROR_SUCCESS) 
		{
			pDlg->InsertItem(888,"没有发现可用的网卡,请检查网卡是否正常工作!");
		//	::MessageBox(NULL,"Call to GetAdaptersInfo failed.没有发现可用的网卡!","802.1x Connector",MB_OK);
		//	ExitProcess(-1);
		}

}
