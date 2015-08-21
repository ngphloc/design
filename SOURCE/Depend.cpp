// Depend.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "Depend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDepend dialog

extern CString commonS;

CDepend::CDepend(CWnd* pParent /*=NULL*/)
	: CDialog(CDepend::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDepend)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDepend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDepend)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDepend, CDialog)
	//{{AFX_MSG_MAP(CDepend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDepend message handlers

BOOL CDepend::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(LOWORD(wParam)==IDOK)
	{
		commonS.Empty();
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_X_EDIT);
		pEdit->GetWindowText(commonS);
	}
	
	return CDialog::OnCommand(wParam, lParam);
}

BOOL CDepend::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
