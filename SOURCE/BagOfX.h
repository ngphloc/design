#if !defined(AFX_BAGOFX_H__46A9DDE1_1EAD_11D4_A3E3_BCDF98293049__INCLUDED_)
#define AFX_BAGOFX_H__46A9DDE1_1EAD_11D4_A3E3_BCDF98293049__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BagOfX.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CBagOfX dialog

class CBagOfX : public CDialog
{
// Construction
public:
	CBagOfX(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBagOfX)
	enum { IDD = IDD_BAG_OF_X_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBagOfX)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBagOfX)
	virtual BOOL OnInitDialog();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BAGOFX_H__46A9DDE1_1EAD_11D4_A3E3_BCDF98293049__INCLUDED_)
