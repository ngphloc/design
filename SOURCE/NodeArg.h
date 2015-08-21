#if !defined(AFX_NODEARG_H__E722C3E1_394C_11D4_A3E3_CD33ADC8D349__INCLUDED_)
#define AFX_NODEARG_H__E722C3E1_394C_11D4_A3E3_CD33ADC8D349__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NodeArg.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CNodeArg dialog

class CNodeArg : public CDialog
{
// Construction
public:
	CNodeArg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNodeArg)
	enum { IDD = IDD_NODE_ARG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNodeArg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNodeArg)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindKeyNodeButton();
	afx_msg void OnFindKeyArgButton();
	afx_msg void OnFindKeyQoButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODEARG_H__E722C3E1_394C_11D4_A3E3_CD33ADC8D349__INCLUDED_)
