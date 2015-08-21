#if !defined(AFX_PERFORM_H__03EB8742_3575_11D4_A3E3_CEB1DFAF8549__INCLUDED_)
#define AFX_PERFORM_H__03EB8742_3575_11D4_A3E3_CEB1DFAF8549__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Perform.h : header file
//
#include <Afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CPerform dialog
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

class CPerform : public CDialog
{
// Construction
public:
	CPerform(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPerform)
	enum { IDD = IDD_PERFORM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPerform)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CArray<CPoint,CPoint&> aPoint;
	// Generated message map functions
	//{{AFX_MSG(CPerform)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnClickGraphMsflexgrid();
	afx_msg void OnViewFullButton();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERFORM_H__03EB8742_3575_11D4_A3E3_CEB1DFAF8549__INCLUDED_)
