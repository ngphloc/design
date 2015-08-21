#if !defined(AFX_UPDATEDBDLG_H__A91E53E6_FEAB_420D_8345_2105507DB786__INCLUDED_)
#define AFX_UPDATEDBDLG_H__A91E53E6_FEAB_420D_8345_2105507DB786__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDBDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateDBDlg dialog

class CUpdateDBDlg : public CDialog
{
// Construction
public:
	CUpdateDBDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUpdateDBDlg)
	enum { IDD = IDD_UPDATEDBDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateDBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUpdateDBDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEDBDLG_H__A91E53E6_FEAB_420D_8345_2105507DB786__INCLUDED_)
