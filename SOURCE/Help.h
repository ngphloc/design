#if !defined(AFX_HELP_H__C621B621_22DA_11D4_A3E3_83CF9E098C49__INCLUDED_)
#define AFX_HELP_H__C621B621_22DA_11D4_A3E3_83CF9E098C49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Help.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CHelp dialog

class CHelp : public CDialog
{
// Construction
public:
	CHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHelp)
	enum { IDD = IDD_HELP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHelp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELP_H__C621B621_22DA_11D4_A3E3_83CF9E098C49__INCLUDED_)
