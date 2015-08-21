// Help.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "Help.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CHelp dialog

extern CString szCurDir;

CHelp::CHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelp, CDialog)
	//{{AFX_MSG_MAP(CHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelp message handlers

BOOL CHelp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//pEdit->ModifyStyleEx(0,ES_AUTOHSCROLL,SWP_SHOWWINDOW);
	//pEdit->ModifyStyle(0,WS_HSCROLL,SWP_SHOWWINDOW);
	//pEdit->Set

	TRY //Mo file
	{
		CString s;
		s = szCurDir + "\\Design.hlp";
		CFile f(s,CFile::modeRead);

		TRY//Doc file
		{
			
			UINT n=f.GetLength();
			HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE,n+1);
			LPSTR lpBuf = (LPSTR)::GlobalLock(hGlobal);

			UINT nBytesRead = f.Read(lpBuf,n);
			lpBuf[nBytesRead] = 0;
			CEdit* pEdit =(CEdit*) GetDlgItem(IDC_HELP_EDIT);
			pEdit->SetWindowText(lpBuf);
			::GlobalUnlock(hGlobal);
			::GlobalFree(hGlobal);
		}
		CATCH(CFileException,err) 
		{
			CString szError;
			szError = "Can't read help file ";
			#ifdef _DEBUG
				afxDump <<szError<<err->m_cause<<"\n";
			#endif
			AfxMessageBox((LPCTSTR)szError,MB_OK,0);
		}
		END_CATCH
	}
	CATCH(CFileException,err) 
	{
		CString szError;
		szError = "Can't open help file ";
		#ifdef _DEBUG
			afxDump <<szError<<err->m_cause<<"\n";
		#endif
		AfxMessageBox((LPCTSTR)szError,MB_OK,0);
	}
	END_CATCH

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

