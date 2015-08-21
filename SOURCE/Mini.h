#if !defined(AFX_MINI_H__23DA7181_2673_11D4_A3E3_8F4D184B2849__INCLUDED_)
#define AFX_MINI_H__23DA7181_2673_11D4_A3E3_8F4D184B2849__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mini.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CMini dialog

class CMini : public CDialog
{
// Construction
public:
	CMini(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMini)
	enum { IDD = IDD_MINI_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMini)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMini)
	afx_msg void OnAgreeButton();
	afx_msg void OnDelButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINI_H__23DA7181_2673_11D4_A3E3_8F4D184B2849__INCLUDED_)
