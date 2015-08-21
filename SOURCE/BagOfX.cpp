// BagOfX.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/


#include "stdafx.h"
#include "Design.h"
#include "BagOfX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBagOfX dialog

extern CString commonS;
CBagOfX::CBagOfX(CWnd* pParent /*=NULL*/)
	: CDialog(CBagOfX::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBagOfX)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBagOfX::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBagOfX)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBagOfX, CDialog)
	//{{AFX_MSG_MAP(CBagOfX)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBagOfX message handlers

BOOL CBagOfX::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBagOfX::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
		case VK_RETURN:
			//OnOK();
			break;
		case VK_ESCAPE:
			break;
	}
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CBagOfX::OnOK() 
{
	// TODO: Add extra validation here
	commonS.Empty();
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_X_EDIT);
	pEdit->GetWindowText(commonS);

	CDialog::OnOK();
}
