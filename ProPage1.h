#if !defined(AFX_PROPAGE1_H__D7103A73_25A3_4139_8EAA_312925798E13__INCLUDED_)
#define AFX_PROPAGE1_H__D7103A73_25A3_4139_8EAA_312925798E13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProPage1 dialog

class CProPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProPage1)

// Construction
public:
	CProPage1();
	~CProPage1();

// Dialog Data
	//{{AFX_DATA(CProPage1)
	enum { IDD = IDD_PROPPAGE_LARGE1 };
	CIPAddressCtrl	m_vgateway;
	CIPAddressCtrl	m_vnetmask;
	CIPAddressCtrl	m_vip;
	CString	m_mac1;
	CString	m_mac2;
	CString	m_mac3;
	CString	m_mac4;
	CString	m_mac5;
	CString	m_mac6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProPage1)
	afx_msg void OnChangeMac1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPAGE1_H__D7103A73_25A3_4139_8EAA_312925798E13__INCLUDED_)
