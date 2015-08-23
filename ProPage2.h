#if !defined(AFX_PROPAGE2_H__699CE96D_46BC_419B_99A7_158EC64AAA85__INCLUDED_)
#define AFX_PROPAGE2_H__699CE96D_46BC_419B_99A7_158EC64AAA85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProPage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProPage2 dialog

class CProPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProPage2)

// Construction
public:
	CProPage2();
	~CProPage2();

// Dialog Data
	//{{AFX_DATA(CProPage2)
	enum { IDD = IDD_PROPPAGE_LARGE2 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProPage2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPAGE2_H__699CE96D_46BC_419B_99A7_158EC64AAA85__INCLUDED_)
