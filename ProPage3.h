#if !defined(AFX_PROPAGE3_H__658D5400_1D37_4377_ACDB_C2F5319F2D01__INCLUDED_)
#define AFX_PROPAGE3_H__658D5400_1D37_4377_ACDB_C2F5319F2D01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProPage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProPage3 dialog

class CProPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProPage3)

// Construction
public:
	CProPage3();
	~CProPage3();

// Dialog Data
	//{{AFX_DATA(CProPage3)
	enum { IDD = IDD_PROPPAGE_LARGE3 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProPage3)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPAGE3_H__658D5400_1D37_4377_ACDB_C2F5319F2D01__INCLUDED_)
