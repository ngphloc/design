// Perform.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "Perform.h"
#include "Relate.h"
#include "Tool.h"
#include "MSFlexGrid.h"
#include "NodeArg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPerform dialog

extern CArray<CRelate,CRelate&>  aOutput;
extern CArray<CUIntArray,CUIntArray&>	 aGraph;

CPerform::CPerform(CWnd* pParent /*=NULL*/)
	: CDialog(CPerform::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPerform)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPerform::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPerform)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPerform, CDialog)
	//{{AFX_MSG_MAP(CPerform)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_VIEW_FULL_BUTTON, OnViewFullButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPerform message handlers

BOOL CPerform::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMSFlexGrid* pGrid=(CMSFlexGrid*)GetDlgItem(IDC_GRAPH_MSFLEXGRID);
	int i,j,m,n=aGraph.GetSize();
	m=n;
	if(n==0)
	{
		MessageBox("Error! R is empty","Error");
		return TRUE;
	}
	char s[16];

	if(n<12)
		n=12;
	pGrid->SetCols(n);
	pGrid->SetRows(n);
	for(i=0;i<n;i++)
		pGrid->SetRowHeight(i,300);
	for(i=0;i<n;i++)
		pGrid->SetColWidth(i,300);

	for(i=0;i<aGraph.GetSize();i++)
		for(j=0;j<aGraph.GetSize();j++)
		{
			pGrid->SetRow(i);
			pGrid->SetCol(j);
			wsprintf(s," %d",aGraph[i][j]);
			if(aGraph[i][j]==1)
				pGrid->SetCellForeColor(RGB(255,0,0));
			else
				pGrid->SetCellForeColor(RGB(0,0,255));
			pGrid->SetText(s);
		}
	
	aPoint.RemoveAll();
	if(m<=20)
		CreatePoint(11,11,9,aPoint);
	else if(m<=30)
	{
		CArray<CPoint,CPoint&> aTemp1;
		CArray<CPoint,CPoint&> aTemp2;
		CreatePoint(11,11,9,aTemp1);
		CreatePoint(11,11,6,aTemp2);
		aPoint.Append(aTemp1);
		aPoint.Append(aTemp2);
	}
	else
	{
		CArray<CPoint,CPoint&> aTemp1;
		CArray<CPoint,CPoint&> aTemp2;
		CArray<CPoint,CPoint&> aTemp3;
		CreatePoint(11,11,9,aTemp1);
		CreatePoint(11,11,6,aTemp2);
		CreatePoint(11,11,3,aTemp3);
		aPoint.Append(aTemp1);
		aPoint.Append(aTemp2);
		aPoint.Append(aTemp3);
	}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CPerform::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	int i,j,seg,n=aGraph.GetSize();
	if(n==0)
	{
		MessageBox("Error! Relate is Empty","Error");
		return;
	}
	char s[8];
	CPen *pPen,*pOldPen;
	pPen=new CPen;
	pPen->CreatePen(PS_SOLID,1,RGB(128,128,255));
	pOldPen=dc.SelectObject(pPen);
	CUIntArray aUINT,a;

	aUINT.SetSize(n);
	aUINT[0]=0;
	seg=aPoint.GetSize()/n;
	for(i=1;i<n;i++)
		aUINT[i]=aUINT[i-1]+seg;
	for(i=0;i<n;i++)
	{
		CPoint point;
		point.x=aPoint[aUINT[i]].x*20;
		point.y=aPoint[aUINT[i]].y*20;
		dc.Ellipse(point.x-12,point.y-12,point.x+12,point.y+12);
		wsprintf(s,"%d",i);
		dc.TextOut(point.x-5,point.y-8,s);
		
	}

	a.SetSize(n);
	for(i=0;i<n;i++)
		a[i]=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			if(aGraph[i][j]==1)
			{
				CPen* pPen;
				CBrush* pBrush,*pOldBrush; 
				pPen=new CPen;
				pBrush=new CBrush;
				CPoint point;

				pPen->CreatePen(PS_SOLID,1,RGB(255,128,0));
				pBrush->CreateSolidBrush(RGB(0,255,0));
				dc.SelectObject(pPen);
				int mode=dc.SetROP2(R2_XORPEN);
				dc.MoveTo(aPoint[aUINT[i]].x*20,aPoint[aUINT[i]].y*20);
				dc.LineTo(aPoint[aUINT[j]].x*20-14+a[j],aPoint[aUINT[j]].y*20-a[j]);
				dc.SetROP2(mode);

				pOldBrush=dc.SelectObject(pBrush);
				point.x=aPoint[aUINT[j]].x*20-14+a[j];
				point.y=aPoint[aUINT[j]].y*20-a[j];
				dc.Ellipse(point.x-3,point.y-3,point.x+3,point.y+3);

				dc.SelectObject(pOldBrush);
				delete pPen;
				delete pBrush;
				a[j]+=6;
			}
	}

	dc.SelectObject(pOldPen);
	delete pPen;
	// Do not call CDialog::OnPaint() for painting messages
}

void CPerform::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}


BEGIN_EVENTSINK_MAP(CPerform, CDialog)
    //{{AFX_EVENTSINK_MAP(CPerform)
	ON_EVENT(CPerform, IDC_GRAPH_MSFLEXGRID, -600 /* Click */, OnClickGraphMsflexgrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CPerform::OnClickGraphMsflexgrid() 
{
	// TODO: Add your control notification handler code here
	CMSFlexGrid* pGrid=(CMSFlexGrid*)GetDlgItem(IDC_GRAPH_MSFLEXGRID);
	CStatic* pStatic=(CStatic*)GetDlgItem(IDC_NODE_I_STATIC);
	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_NODE_I_EDIT);
	int i=pGrid->GetRowSel();
	int j=pGrid->GetColSel();
	if(i>=aGraph.GetSize()||j>=aGraph.GetSize())
		return;
	CString tempS,s,szR;
	CRelate tempRelate;
	CStringArray aszKi,aszKj;

	//Cac nut
	s.Format("Nut %d",i);
	pStatic->SetWindowText(s);
	aOutput[i].Output(tempS);
	pEdit->SetWindowText(tempS);

	pStatic=(CStatic*)GetDlgItem(IDC_NODE_J_STATIC);
	pEdit=(CEdit*)GetDlgItem(IDC_NODE_J_EDIT);
	s.Format("Nut %d",j);
	pStatic->SetWindowText(s);
	aOutput[j].Output(tempS);
	pEdit->SetWindowText(tempS);

	//Cac cung
	pStatic=(CStatic*)GetDlgItem(IDC_ARG_I_STATIC);
	pEdit=(CEdit*)GetDlgItem(IDC_ARG_I_EDIT);
	s.Format("Cung %d->%d",i,j);
	pStatic->SetWindowText(s);
	if(aGraph[i][j]==1)
	{
		aOutput[i].FindKey();
		aOutput[i].GetK(aszKi);
		aOutput[j].FindKey();
		aOutput[j].GetK(aszKj);
		szR=Union(aszKi,aszKj);
		tempRelate=aOutput[i]+aOutput[j];
		tempRelate.SetR(szR);
		tempRelate.EssenceRD();
		tempRelate.Output(tempS);

		pEdit->SetWindowText(tempS);
	}
	else
		pEdit->SetWindowText("Khong co ");

	pStatic=(CStatic*)GetDlgItem(IDC_ARG_J_STATIC);
	pEdit=(CEdit*)GetDlgItem(IDC_ARG_J_EDIT);
	s.Format("Cung %d->%d",j,i);
	pStatic->SetWindowText(s);
	if(aGraph[j][i]==1)
	{
		if(aGraph[i][j]==0)
		{
			aOutput[i].FindKey();
			aOutput[i].GetK(aszKi);
			aOutput[j].FindKey();
			aOutput[j].GetK(aszKj);
			szR=Union(aszKi,aszKj);
			tempRelate=aOutput[i]+aOutput[j];
			tempRelate.SetR(szR);
			tempRelate.EssenceRD();
			tempRelate.Output(tempS);
		}
		pEdit->SetWindowText(tempS);
	}
	else
		pEdit->SetWindowText("Khong co ");
	
}

void CPerform::OnViewFullButton() 
{
	// TODO: Add your control notification handler code here
	CNodeArg dlgNodeArg(this);
	dlgNodeArg.DoModal();
}
