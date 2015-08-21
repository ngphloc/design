// Choose.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "Choose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoose dialog

extern int commonInt;

CChoose::CChoose(CWnd* pParent /*=NULL*/)
	: CDialog(CChoose::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChoose)
	m_Value = -1;
	//}}AFX_DATA_INIT
}


void CChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChoose)
	DDX_CBIndex(pDX, IDC_VALUE_COMBO, m_Value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChoose, CDialog)
	//{{AFX_MSG_MAP(CChoose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChoose message handlers

BOOL CChoose::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_VALUE_COMBO);
	for(int i=0;i<commonInt;i++)
	{
		CString s;
		s.Format("%d",i);
		pCombo->AddString((LPCTSTR)s);
	}
	pCombo->SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChoose::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	char szText[16];
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_VALUE_COMBO);
	
	pCombo->GetLBText(m_Value,szText);
	commonInt=atoi(szText);

	CDialog::OnOK();
}
