#if !defined(AFX_VIEWD_H__57EDD681_1F4B_11D4_A3E3_B8219097EF49__INCLUDED_)
#define AFX_VIEWD_H__57EDD681_1F4B_11D4_A3E3_B8219097EF49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewD.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CViewD dialog

class CViewD : public CDialog
{
// Construction
public:
	CViewD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewD)
	enum { IDD = IDD_VIEW_D_FULL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewD)
	virtual BOOL OnInitDialog();
	afx_msg void OnPerformButton();
	afx_msg void OnFindKeyButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWD_H__57EDD681_1F4B_11D4_A3E3_B8219097EF49__INCLUDED_)
