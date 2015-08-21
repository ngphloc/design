#if !defined(AFX_PTT_H__5C7F4621_2649_11D4_A3E3_E30FDC1D0E49__INCLUDED_)
#define AFX_PTT_H__5C7F4621_2649_11D4_A3E3_E30FDC1D0E49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ptt.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CPtt dialog

class CPtt : public CDialog
{
// Construction
public:
	CPtt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPtt)
	enum { IDD = IDD_PTT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPtt)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTT_H__5C7F4621_2649_11D4_A3E3_E30FDC1D0E49__INCLUDED_)
