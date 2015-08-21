#if !defined(AFX_DISR_H__EC4482C1_1F73_11D4_A3E3_BA6CF2F9764A__INCLUDED_)
#define AFX_DISR_H__EC4482C1_1F73_11D4_A3E3_BA6CF2F9764A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisR.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CDisR dialog

class CDisR : public CDialog
{
// Construction
public:
	CDisR(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDisR)
	enum { IDD = IDD_DIS_DIALOG };
	int		m_Value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDisR)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISR_H__EC4482C1_1F73_11D4_A3E3_BA6CF2F9764A__INCLUDED_)
