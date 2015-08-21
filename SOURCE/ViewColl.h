#if !defined(AFX_VIEWCOLL_H__B7FA6CA1_26B7_11D4_A3E3_DEAC186AF049__INCLUDED_)
#define AFX_VIEWCOLL_H__B7FA6CA1_26B7_11D4_A3E3_DEAC186AF049__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewColl.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CViewColl dialog

class CViewColl : public CDialog
{
// Construction
public:
	CViewColl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewColl)
	enum { IDD = IDD_VIEW_COLLECT_FULL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewColl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewColl)
	virtual BOOL OnInitDialog();
	afx_msg void OnPerformButton();
	afx_msg void OnFindKeyButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWCOLL_H__B7FA6CA1_26B7_11D4_A3E3_DEAC186AF049__INCLUDED_)
