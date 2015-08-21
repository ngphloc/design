#if !defined(AFX_GRAPH_H__03EB8741_3575_11D4_A3E3_CEB1DFAF8549__INCLUDED_)
#define AFX_GRAPH_H__03EB8741_3575_11D4_A3E3_CEB1DFAF8549__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Graph.h : header file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/////////////////////////////////////////////////////////////////////////////
// CGraph dialog
class CGraphHelp : public CDialog
{
// Construction
public:
	CGraphHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CABC)
	enum { IDD = IDD_GRAPH_HELP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphHelp)
	virtual BOOL OnInitDialog();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CGraph : public CDialog
{
// Construction
public:
	CGraph(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraph)
	enum { IDD = IDD_GRAPH_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraph)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Empty();
	void Remind();
	CString  szPathName,szFileName,szInitDir,szFileTitle;
	BOOL UpdateRelate(CString szS);
	void showLinearRiskD();


	// Generated message map functions
	//{{AFX_MSG(CGraph)
	afx_msg void OnPerformButton();
	afx_msg void OnClearButton();
	afx_msg void OnFileExit();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	virtual BOOL OnInitDialog();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	afx_msg void OnDestroy();
	afx_msg void OnAcceptButton();
	afx_msg void OnFindKeyButton();
	afx_msg void OnTableauButton();
	afx_msg void OnContextHelp();
	afx_msg void OnLineardButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPH_H__03EB8741_3575_11D4_A3E3_CEB1DFAF8549__INCLUDED_)
