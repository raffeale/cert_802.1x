#if !defined(AFX_PROSHEET_H__E5C2DAC8_CA7A_4AC2_90E8_CED1522DA349__INCLUDED_)
#define AFX_PROSHEET_H__E5C2DAC8_CA7A_4AC2_90E8_CED1522DA349__INCLUDED_

#include "ProPage1.h"
#include "ProPage2.h"
#include "ProPage3.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProSheet

class CProSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CProSheet)

// Construction
public:
	CProSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CProSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CProPage1 configpage1;
	CProPage2 configpage2;
	CProPage3 configpage3;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROSHEET_H__E5C2DAC8_CA7A_4AC2_90E8_CED1522DA349__INCLUDED_)
