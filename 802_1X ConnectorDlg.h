// 802_1X ConnectorDlg.h : header file
//
#include<pcap.h>
#include"md5.h"


struct EAP_Packet
	{	unsigned char MAC_DEST[6];
		unsigned char MAC_SRC[6];
		unsigned char EType[4];
		unsigned short int  packlen;

		unsigned char EAPheader_code;
		unsigned char EAPheader_id;
		unsigned short int EAPheader_len;
		unsigned char EAP_Data_Type;		//0x02=notification type
		union _msgs
		{
//		usermsg user;
			struct  usermsg{
				unsigned char flag;
				unsigned char ipaddr[4];
				unsigned char netmask[4];
				unsigned char gateway[4];
				unsigned char dhcp[4];
//	unsigned char version[8];
				unsigned char VerMiddleWord[2];
				unsigned char chart1;
				unsigned char VerHighWord[2];
				unsigned char chart2;
				unsigned char VerLowWord[2];
				unsigned char username[12];
			}user;
	
	struct md5msg
	{
	unsigned char value_size;
	unsigned char md5challenge[16];
	unsigned char username[18];
	}md5_msg;
		}msgs;
		//		unsigned char EAP_msgbuffer[242];
		//		unsigned char EAP_msgbuffer[256-6-6-4-2-1-1-2-1];
	};


/*
struct idnumber
	{
		char index;
		char name[20];
		char *mac;
	};
*/



#if !defined(AFX_802_1XCONNECTORDLG_H__42E2E2B3_082E_4FD2_9CDA_E968732F17A1__INCLUDED_)
#define AFX_802_1XCONNECTORDLG_H__42E2E2B3_082E_4FD2_9CDA_E968732F17A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy802_1XConnectorDlg dialog

class CMy802_1XConnectorDlg : public CDialog
{
// Construction
public:
	void CheckNetCard();
	void GetRegistryInfo();
	LPVOID lpParameter;
//	DWORD WINAPI ThreadProc(LPVOID lpParameter);
	static void packet_handler(u_char *param, const pcap_pkthdr *header, const u_char *pkt_data);
//	ClistBox m_lbhand;
	HANDLE m_tHandle;
	CMy802_1XConnectorDlg(CWnd* pParent = NULL);	// standard constructor
	DWORD dwThreadId, dwThrdParam; 




// Dialog Data
	//{{AFX_DATA(CMy802_1XConnectorDlg)
	enum { IDD = IDD_MY802_1XCONNECTOR_DIALOG };
	CButton	m_userinfo;
	CListCtrl	m_listctrl;
	CButton	m_disconnect;
	CButton	m_connect;
	CString	m_username;
	CString	m_password;
	CString	m_time;
	BOOL	m_saveflag;
	BOOL	m_vip;
	BOOL	m_vmac;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy802_1XConnectorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy802_1XConnectorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnAbout();
	afx_msg void OnClose();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnConfig();
	afx_msg void OnCheck1();
	virtual void OnOK();
	afx_msg void OnVmaccheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_802_1XCONNECTORDLG_H__42E2E2B3_082E_4FD2_9CDA_E968732F17A1__INCLUDED_)
