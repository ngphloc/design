// ViewColl.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "ViewColl.h"
#include "Tool.h"
#include "Relate.h"
#include "Perform.h"
#include "Choose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewColl dialog

extern CArray<CRelate, CRelate&>		aCollectRelate;
extern CArray<CRelate,CRelate&>			aOutput;
extern CArray<CUIntArray,CUIntArray&>	aGraph;
extern int commonInt;

CViewColl::CViewColl(CWnd* pParent /*=NULL*/)
	: CDialog(CViewColl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewColl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CViewColl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewColl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewColl, CDialog)
	//{{AFX_MSG_MAP(CViewColl)
	ON_BN_CLICKED(IDC_PERFORM_BUTTON, OnPerformButton)
	ON_BN_CLICKED(IDC_FIND_KEY_BUTTON, OnFindKeyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewColl message handlers

BOOL CViewColl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int n;
	if(n=aCollectRelate.GetSize())
	{
		CString tempS,S;
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_VIEW_COLLECT_FULL_EDIT);
		for(int i=0;i<n;i++)
		{
			CString s;
			aCollectRelate[i].Output(tempS);
			if(i<10)
				s.Format("%d.  ",i);
			else if(i<100)
				s.Format("%d. ",i);
			else 
				s.Format("%d.",i);
			tempS=s+tempS;
			tempS+="\r\n";
			S+=tempS;
		}
		pEdit->SetWindowText(S);
	}
	else
	{
		CButton* pButton=(CButton*)GetDlgItem(IDC_FIND_KEY_BUTTON);
		pButton->EnableWindow(FALSE);
		pButton=(CButton*)GetDlgItem(IDC_PERFORM_BUTTON);
		pButton->EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewColl::OnPerformButton() 
{
	// TODO: Add your control notification handler code here
	if(CRelate::PerformToGraph(aCollectRelate,aOutput,aGraph))
	{
		CPerform dlgPerform(this);
		dlgPerform.DoModal();
	}
	
}

void CViewColl::OnFindKeyButton() 
{
	// TODO: Add your control notification handler code here
	int n;
	if(n=aCollectRelate.GetSize())
	{
		commonInt=n;
		CChoose dlgChoose(this);	
		if(dlgChoose.DoModal()==IDOK)
		{
			if(commonInt<0||commonInt>=n)
				commonInt=0;
			CStringArray aszK;
			CString szK;
			aCollectRelate[commonInt].FindKey();
			aCollectRelate[commonInt].GetK(aszK);
			StringArrayToString(aszK,szK);

			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_KEY_EDIT);
			pEdit->SetWindowText(szK);

			char s[256];
			CStatic* pStatic=(CStatic*)GetDlgItem(IDC_KEY_STATIC);
			wsprintf(s,"R%d has %d keys",commonInt,aszK.GetSize());
			pStatic->SetWindowText(s);
		}
	}
}
