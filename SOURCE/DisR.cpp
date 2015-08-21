// DisR.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "DisR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisR dialog

extern int commonInt;

CDisR::CDisR(CWnd* pParent /*=NULL*/)
	: CDialog(CDisR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDisR)
	m_Value = -1;
	//}}AFX_DATA_INIT
}


void CDisR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisR)
	DDX_CBIndex(pDX, IDC_VALUE_COMBO, m_Value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisR, CDialog)
	//{{AFX_MSG_MAP(CDisR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisR message handlers

void CDisR::OnOK() 
{

	// TODO: Add extra validation here
	UpdateData();
	char szText[16];
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_VALUE_COMBO);
	
	pCombo->GetLBText(m_Value,szText);
	commonInt=atoi(szText);
	CDialog::OnOK();
}

BOOL CDisR::OnInitDialog() 
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
