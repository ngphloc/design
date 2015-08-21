// DesignDlg.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#if !defined(AFX_DESIGNDLG_H__E9324289_1A09_11D4_A3E3_D1558B86324A__INCLUDED_)
#define AFX_DESIGNDLG_H__E9324289_1A09_11D4_A3E3_D1558B86324A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDesignDlg dialog


class CDesignDlg : public CDialog
{
// Construction
public:
	CDesignDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDesignDlg)
	enum { IDD = IDD_DESIGN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesignDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString  szPathName,szFileName,szInitDir,szFileTitle;
	void Remind();
	void UpdateRelate(CString tempR, CString tempS);
	void Clear();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDesignDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClearButton();
	afx_msg void OnFindKeyButton();
	afx_msg void OnBagOfXButton();
	afx_msg void OnAcceptButton();
	afx_msg void OnDependOfXButton();
	afx_msg void OnDisRelateButton();
	afx_msg void OnViewDFullButton();
	afx_msg void OnAppAbout();
	afx_msg void OnFileExit();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	afx_msg void OnFileNew();
	afx_msg void OnContextHelp();
	afx_msg void OnDestroy();
	afx_msg void OnPttButton();
	afx_msg void OnCoSoTtButton();
	afx_msg void OnCollectButton();
	afx_msg void OnViewCollectFullButton();
	afx_msg void OnDisRelateEnhancedButton();
	afx_msg void OnGraphButton();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESIGNDLG_H__E9324289_1A09_11D4_A3E3_D1558B86324A__INCLUDED_)
