#if !defined(AFX_CHOOSE_H__17ACDD01_37B5_11D4_A3E3_C88ADA33424B__INCLUDED_)
#define AFX_CHOOSE_H__17ACDD01_37B5_11D4_A3E3_C88ADA33424B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Choose.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CChoose dialog

class CChoose : public CDialog
{
// Construction
public:
	CChoose(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChoose)
	enum { IDD = IDD_CHOOSE_DIALOG };
	int		m_Value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChoose)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChoose)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSE_H__17ACDD01_37B5_11D4_A3E3_C88ADA33424B__INCLUDED_)
