// ViewD.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "ViewD.h"
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
// CViewD dialog
extern CArray<CRelate, CRelate&> aDisRelate;
extern CRelate Relate;
extern CString szPathName;
extern CArray<CRelate,CRelate&>       aOutput;
extern CArray<CUIntArray,CUIntArray&> aGraph;
extern int commonInt;

CViewD::CViewD(CWnd* pParent /*=NULL*/)
	: CDialog(CViewD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CViewD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewD)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewD, CDialog)
	//{{AFX_MSG_MAP(CViewD)
	ON_BN_CLICKED(IDC_PERFORM_BUTTON, OnPerformButton)
	ON_BN_CLICKED(IDC_FIND_KEY_BUTTON, OnFindKeyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewD message handlers

BOOL CViewD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	int n;
	if(n=aDisRelate.GetSize())
	{
		CString tempS,S;
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_VIEW_D_FULL_EDIT);
		for(int i=0;i<n;i++)
		{
			CString s;
			aDisRelate[i].Output(tempS);
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

void CViewD::OnPerformButton() 
{
	// TODO: Add your control notification handler code here
	CArray<CRelate,CRelate&>    aInput;
	CArray<CFunc,CFunc&> aD;
	CRelate tempRelate;
	CString szR;

	Relate.GetD(aD);
	for(int i=0;i<aDisRelate.GetSize();i++)
	{
		szR=aDisRelate[i].GetR();
		if(!szR.IsEmpty())
		{
			tempRelate.SetR(szR);
			tempRelate.SetD(aD);
			tempRelate.EssenceRD();
			aInput.Add(tempRelate);
		}
	}

	if(CRelate::PerformToGraph(aDisRelate,aOutput,aGraph))
	{
		CPerform dlgPerform(this);
		dlgPerform.DoModal();
	}
	
}

void CViewD::OnFindKeyButton() 
{
	// TODO: Add your control notification handler code here
	int n;
	if(n=aDisRelate.GetSize())
	{
		commonInt=n;
		CChoose dlgChoose(this);	
		if(dlgChoose.DoModal()==IDOK)
		{
			if(commonInt<0||commonInt>=n)
				commonInt=0;
			CStringArray aszK;
			CString szR,szK;
			CRelate tempRelate;
			CArray<CFunc,CFunc&> aD;
			Relate.GetD(aD);			

			tempRelate.SetR(aDisRelate[commonInt].GetR());
			tempRelate.SetD(aD);
			tempRelate.EssenceD();
			tempRelate.FindKey();
			tempRelate.GetK(aszK);
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
