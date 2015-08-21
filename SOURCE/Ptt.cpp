// Ptt.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "Ptt.h"
#include "Tool.h"
#include "Relate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPtt dialog

extern CArray<CFunc, CFunc&> aPTT;

CPtt::CPtt(CWnd* pParent /*=NULL*/)
	: CDialog(CPtt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPtt)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPtt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPtt)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPtt, CDialog)
	//{{AFX_MSG_MAP(CPtt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPtt message handlers

BOOL CPtt::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for(int i=0;i<aPTT.GetSize();i++)
	{
		CString X,Y;
		StringArrayToString(aPTT[i].GetX(),X);
		StringArrayToString(aPTT[i].GetY(),Y);
		if(aPTT[i].GetFlag())
			X = X + "->" + Y  ;
		else
			X = X + "->>" + Y ;

		CListBox* pListBox =(CListBox *) GetDlgItem(IDC_PTT_LIST);
		pListBox->AddString((LPCTSTR)X);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
