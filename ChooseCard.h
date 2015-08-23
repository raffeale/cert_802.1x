#if !defined(AFX_CHOOSECARD_H__78FE7583_26F7_45A7_BEB9_DB93125081DF__INCLUDED_)
#define AFX_CHOOSECARD_H__78FE7583_26F7_45A7_BEB9_DB93125081DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseCard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseCard dialog

class CChooseCard : public CDialog
{
// Construction
public:
	CChooseCard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseCard)
	enum { IDD = IDD_DIALOG1 };
	int		m_index;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseCard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseCard)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCardlist();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSECARD_H__78FE7583_26F7_45A7_BEB9_DB93125081DF__INCLUDED_)
