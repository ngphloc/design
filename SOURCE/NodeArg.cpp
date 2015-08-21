// NodeArg.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "NodeArg.h"
#include "Relate.h"
#include "Tool.h"
#include "Choose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeArg dialog
extern CArray<CRelate,CRelate&>  aOutput;
extern CArray<CUIntArray,CUIntArray&>	 aGraph;
extern int commonInt;

CNodeArg::CNodeArg(CWnd* pParent /*=NULL*/)
	: CDialog(CNodeArg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNodeArg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNodeArg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeArg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeArg, CDialog)
	//{{AFX_MSG_MAP(CNodeArg)
	ON_BN_CLICKED(IDC_FIND_KEY_NODE_BUTTON, OnFindKeyNodeButton)
	ON_BN_CLICKED(IDC_FIND_KEY_ARG_BUTTON, OnFindKeyArgButton)
	ON_BN_CLICKED(IDC_FIND_KEY_Qo_BUTTON, OnFindKeyQoButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeArg message handlers

BOOL CNodeArg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int n;
	if(n=aOutput.GetSize())
	{
		int count,i,j;
		CRelate tempRelate;
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_NODE_EDIT);
		CString s;
		CString tempS,S;

		for(i=0;i<n;i++)
		{
			aOutput[i].Output(tempS);
			if(i<10)
				s.Format("%d.  ",i);
			else if(i<100)
				s.Format("%d. ",i);
			else 
				s.Format("%d.",i);
			tempS=s+tempS+"\r\n";
			S+=tempS;
		}
		pEdit->SetWindowText(S);

		pEdit = (CEdit*)GetDlgItem(IDC_ARG_EDIT);
		
		count=0;
		CArray<CRelate,CRelate&> aRelate;
		CStringArray aszTemp;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(aGraph[i][j]==1)
				{
					CStringArray aszKi,aszKj;
					CString szR;

					aOutput[i].FindKey();
					aOutput[i].GetK(aszKi);
					aOutput[j].FindKey();
					aOutput[j].GetK(aszKj);
					szR=Union(aszKi,aszKj);
					tempRelate=aOutput[i]+aOutput[j];
					tempRelate.SetR(szR);
					tempRelate.EssenceRD();

					aRelate.Add(tempRelate);
					if(aGraph[j][i]==1)
						s.Format("Cung %d<->%d  ",i,j);
					else
						s.Format("Cung %d->%d  ",i,j);
					aszTemp.Add(s);

					count++;
				}
		if(count==0)
		{
			MessageBox("Remind ! Khonng co cung","Remind");
			CButton* pButton=(CButton*)GetDlgItem(IDC_FIND_KEY_ARG_BUTTON);
			pButton->EnableWindow(FALSE);
			return TRUE;
		}	

		S.Empty();
		tempS.Empty();
		for(i=0;i<count;i++)
		{
			if(i<10)
				s.Format("%d.  ",i);
			else if(i<100)
				s.Format("%d. ",i);
			else 
				s.Format("%d.",i);

			aRelate[i].Output(tempS);

			tempS=s+aszTemp[i]+tempS+"\r\n";
			S+=tempS;					
		}
		pEdit->SetWindowText(S);
		tempRelate=aOutput;
		tempRelate.EssenceRD();
		tempRelate.Output(tempS);
		pEdit = (CEdit*)GetDlgItem(IDC_Qo_EDIT);
		pEdit->SetWindowText(tempS);


	}
	else
	{
		CButton* pButton=(CButton*)GetDlgItem(IDC_FIND_KEY_NODE_BUTTON);
		pButton->EnableWindow(FALSE);
		pButton=(CButton*)GetDlgItem(IDC_FIND_KEY_ARG_BUTTON);
		pButton->EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNodeArg::OnFindKeyNodeButton() 
{
	// TODO: Add your control notification handler code here
	int n;
	if(n=aOutput.GetSize())
	{
		commonInt=n;
		CChoose dlgChoose(this);	
		if(dlgChoose.DoModal()==IDOK)
		{
			if(commonInt<0||commonInt>=n)
				commonInt=0;
			CStringArray aszK;
			CString szK;
			aOutput[commonInt].FindKey();
			aOutput[commonInt].GetK(aszK);
			StringArrayToString(aszK,szK);

			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_KEY_NODE_EDIT);
			pEdit->SetWindowText(szK);

			char s[256];
			CStatic* pStatic=(CStatic*)GetDlgItem(IDC_KEY_NODE_STATIC);
			wsprintf(s,"R%d has %d keys",commonInt,aszK.GetSize());
			pStatic->SetWindowText(s);
		}
	}
	
}

void CNodeArg::OnFindKeyArgButton() 
{
	// TODO: Add your control notification handler code here
	int count=0,i,j,n=aOutput.GetSize();
	if(n==0)
		return;
	
	CArray<CRelate,CRelate&> aRelate;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(aGraph[i][j]==1)
			{
				CRelate tempRelate;
				CStringArray aszKi,aszKj;
				CString szR;

				aOutput[i].FindKey();
				aOutput[i].GetK(aszKi);
				aOutput[j].FindKey();
				aOutput[j].GetK(aszKj);
				szR=Union(aszKi,aszKj);
				tempRelate=aOutput[i]+aOutput[j];
				tempRelate.SetR(szR);
				tempRelate.EssenceRD();

				aRelate.Add(tempRelate);
				count++;
			}
	if(count>0)
	{
		commonInt=count;
		CChoose dlgChoose(this);	
		if(dlgChoose.DoModal()==IDOK)
		{
			if(commonInt<0||commonInt>=count)
				commonInt=0;
			CStringArray aszK;
			CString szK;
			aRelate[commonInt].FindKey();
			aRelate[commonInt].GetK(aszK);
			StringArrayToString(aszK,szK);

			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_KEY_ARG_EDIT);
			pEdit->SetWindowText(szK);

			char s[256];
			CStatic* pStatic=(CStatic*)GetDlgItem(IDC_KEY_ARG_STATIC);
			wsprintf(s,"R%d has %d keys",commonInt,aszK.GetSize());
			pStatic->SetWindowText(s);
		}
	}
	
}

void CNodeArg::OnFindKeyQoButton() 
{
	// TODO: Add your control notification handler code here
	if(aOutput.GetSize()==0)
	{
		MessageBox("Error! Qo is empty","Error");
		return;
	}

	CRelate tempRelate=aOutput;
	CStringArray aszK;
	CString szK,s;
	CStatic* pStatic=(CStatic*)GetDlgItem(IDC_KEY_Qo_STATIC);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_KEY_Qo_EDIT);

	tempRelate.FindKey();
	tempRelate.GetK(aszK);
	StringArrayToString(aszK,szK);
	pEdit->SetWindowText(szK);

	s.Format("Qo has %d keys",aszK.GetSize());
	pStatic->SetWindowText(s);
	
}
