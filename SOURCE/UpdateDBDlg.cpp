// UpdateDBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Design.h"
#include "UpdateDBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateDBDlg dialog


CUpdateDBDlg::CUpdateDBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDBDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUpdateDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDBDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateDBDlg, CDialog)
	//{{AFX_MSG_MAP(CUpdateDBDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDBDlg message handlers
