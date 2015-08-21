// Mini.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "Mini.h"
#include "Tool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMini dialog


CMini::CMini(CWnd* pParent /*=NULL*/)
	: CDialog(CMini::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMini)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMini::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMini)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMini, CDialog)
	//{{AFX_MSG_MAP(CMini)
	ON_BN_CLICKED(IDC_AGREE_BUTTON, OnAgreeButton)
	ON_BN_CLICKED(IDC_DEL_BUTTON, OnDelButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMini message handlers

void CMini::OnAgreeButton() 
{
	// TODO: Add your control notification handler code here
	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_SOURCE_EDIT);
	CString tempS;
	pEdit->GetWindowText(tempS);
	if(tempS.IsEmpty())
	{
		MessageBox("Source is empty !","Error",MB_OK);
		pEdit->SetFocus();
		return;
	}
	CStringArray aszX,aszY;

	SplitString(tempS,',',aszX);
	Minimum(aszX,aszY);

	tempS.Empty();
	CString S="(";
	StringArrayToString(aszY,tempS);
	tempS = S + tempS + ")";
	pEdit = (CEdit *)GetDlgItem(IDC_DEST_EDIT);
	pEdit->SetWindowText(tempS);
}

void CMini::OnDelButton() 
{
	// TODO: Add your control notification handler code here
	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_SOURCE_EDIT);	
	pEdit->SetWindowText("");
	pEdit = (CEdit *)GetDlgItem(IDC_DEST_EDIT);	
	pEdit->SetWindowText("");

}
