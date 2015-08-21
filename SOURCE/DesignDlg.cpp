// DesignDlg.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include <direct.h>
#include "stdafx.h"
#include "Design.h"
#include "DesignDlg.h"
#include "Relate.h"
#include "Tool.h"
#include "BagOfX.h"
#include "Depend.h"
#include "ViewD.h"
#include "DisR.h"
#include "Help.h"
#include "Ptt.h"
#include "Mini.h"
#include "ViewColl.h"
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CArray<CRelate, CRelate&> aDisRelate;
CArray<CRelate, CRelate&> aCollectRelate;
CArray<CFunc, CFunc&> aPTT;
CRelate Relate;
CString commonS;//chuoi dung chung
int  commonInt;
CString  szCurDir;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesignDlg dialog

CDesignDlg::CDesignDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDesignDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDesignDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_DESIGN_ICON);
}

void CDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDesignDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDesignDlg, CDialog)
	//{{AFX_MSG_MAP(CDesignDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, OnClearButton)
	ON_BN_CLICKED(IDC_FIND_KEY_BUTTON, OnFindKeyButton)
	ON_BN_CLICKED(IDC_BAG_OF_X_BUTTON, OnBagOfXButton)
	ON_BN_CLICKED(IDC_ACCEPT_BUTTON, OnAcceptButton)
	ON_BN_CLICKED(IDC_DEPEND_OF_X_BUTTON, OnDependOfXButton)
	ON_BN_CLICKED(IDC_DIS_RELATE_BUTTON, OnDisRelateButton)
	ON_BN_CLICKED(IDC_VIEW_D_FULL_BUTTON, OnViewDFullButton)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveas)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_PTT_BUTTON, OnPttButton)
	ON_BN_CLICKED(IDC_CO_SO_TT_BUTTON, OnCoSoTtButton)
	ON_BN_CLICKED(IDC_COLLECT_BUTTON, OnCollectButton)
	ON_BN_CLICKED(IDC_VIEW_COLLECT_FULL_BUTTON, OnViewCollectFullButton)
	ON_BN_CLICKED(IDC_DIS_RELATE_ENHANCED_BUTTON, OnDisRelateEnhancedButton)
	ON_BN_CLICKED(IDC_GRAPH_BUTTON, OnGraphButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesignDlg message handlers

BOOL CDesignDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	char s[256];
	::GetCurrentDirectory(sizeof(s),s);
	szCurDir = s;
	wsprintf(s,"%s\\DATA",s);
	szInitDir = s ;
	szFileTitle ="Untitled";
	szFileName = "Untitled.dat";
	szPathName = szInitDir + "\\" +szFileName;

	CString szDlgTitle = "Design - ";
	SetWindowText(szDlgTitle + szFileTitle);

	CHelp dlgHelp;
	dlgHelp.DoModal();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDesignDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CDesignDlg::OnAppAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CDesignDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
	OnOK();	
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDesignDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDesignDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDesignDlg::UpdateRelate(CString tempR, CString tempD)
{
	//Cap nhat the hien quan he;
	CString S;
	Alpha(tempR,S);
	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_R_EDIT);
	if(S.IsEmpty())
	{
		MessageBox("Error ! R is Empty","Error",MB_OK);
		pEdit->SetFocus();
		return;
	}
	Clear();
	Relate.SetR(S);
	pEdit->SetWindowText((LPCTSTR)S);
	pEdit->SetModify(TRUE);
	
	//Cac thao tac tao phu thuoc
	if(tempD.IsEmpty())
		return;
	CStringArray aszS,aszTemp;
	SplitString(tempD,'\n',aszTemp);
	int i;
	
	for(i=0;i<aszTemp.GetSize();i++)
	{
		CStringArray aszR;
		SplitString(aszTemp[i],';',aszR);
		aszS.Append(aszR);
	}
	
	CArray<CFunc,CFunc&> aD;
	for(i=0;i<aszS.GetSize();i++)
	{
		CString s;
		if(aszS[i].Find("->>") != -1)
			s = "->>";
		else if(aszS[i].Find("->") != -1)
			s = "->";
		else continue;
		
		CStringArray aszX;

		SplitString(aszS[i],(LPCTSTR)s,aszX);
		if(aszX.GetSize() == 2)
		{
			CStringArray X,Y;
			SplitString(aszX[0],',',X);
			SplitString(aszX[1],',',Y);
			Alpha(X);Alpha(Y);
			if(X.GetSize() && Y.GetSize())
			{
				CFunc f;
				f.SetX(X);
				f.SetY(Y);

				if(s=="->")
					f.SetFlag(TRUE);
				else if(s=="->>")
					f.SetFlag(FALSE);
				aD.Add(f);
			}
		}
			
	}
	Relate.SetD(aD);

}

void CDesignDlg::OnAcceptButton() 
{
	// TODO: Add your control notification handler code here
	CString tempR,tempD;
	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_R_EDIT);
	pEdit->GetWindowText(tempR);
	pEdit = (CEdit *)GetDlgItem(IDC_D_EDIT);
	pEdit->GetWindowText(tempD);

	UpdateRelate(tempR,tempD);
}

void CDesignDlg::Clear()
{
	Relate.Empty();
	aDisRelate.RemoveAll();
	aCollectRelate.RemoveAll();
	aPTT.RemoveAll();

	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_KEY_EDIT);	
	pEdit->SetWindowText("");
	pEdit = (CEdit *)GetDlgItem(IDC_BAG_OF_X_EDIT);	
	pEdit->SetWindowText("");
	pEdit = (CEdit *)GetDlgItem(IDC_DEPEND_OF_X_EDIT);	
	pEdit->SetWindowText("");
	pEdit = (CEdit *)GetDlgItem(IDC_DIS_RELATE_EDIT);	
	pEdit->SetWindowText("");
	pEdit = (CEdit *)GetDlgItem(IDC_COLLECT_EDIT);	
	pEdit->SetWindowText("");
	pEdit = (CEdit *)GetDlgItem(IDC_BX_EDIT);	
	pEdit->SetWindowText("");
	pEdit = (CEdit *)GetDlgItem(IDC_DX_EDIT);	
	pEdit->SetWindowText("");
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_KEY_STATIC);
	pStatic->SetWindowText("");
}

void CDesignDlg::OnClearButton() 
{
	// TODO: Add your control notification handler code here
	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_D_EDIT);
	pEdit->SetWindowText("");
	pEdit->SetModify(TRUE);
	pEdit = (CEdit *)GetDlgItem(IDC_R_EDIT);	
	pEdit->SetWindowText("");
	pEdit->SetFocus();
	pEdit->SetModify(TRUE);
	Clear();
}

void CDesignDlg::OnFindKeyButton() 
{
	// TODO: Add your control notification handler code here
	if(Relate.GetR().IsEmpty())
	{
		MessageBox("Error ! Relation is empty","Error");
		return;
	}
	
	CStringArray aszTempS;
	CString S;
	
	if(Relate.FindKey())
	{
		Relate.GetK(aszTempS);
		StringArrayToString(aszTempS,S);

		CEdit* pEdit = (CEdit *)GetDlgItem(IDC_KEY_EDIT);
		pEdit->SetWindowText((LPCTSTR)S);
		CStatic* pStatic =(CStatic*)GetDlgItem(IDC_KEY_STATIC);
		char s[50];
		wsprintf(s,"%ld keys",aszTempS.GetSize());
		pStatic->SetWindowText(s);
	}
	else
		MessageBox("Error ! Can't find any key","Error");
}

void CDesignDlg::OnBagOfXButton() 
{
	// TODO: Add your control notification handler code here
	if(Relate.GetR().IsEmpty())
	{
		MessageBox("Error ! Relation is empty","Error");
		return;
	}

	CBagOfX dlgBagOfX(this);
	if(dlgBagOfX.DoModal()==IDOK)
	{

		CString tempS;

		CEdit* pEdit = (CEdit *)GetDlgItem(IDC_BX_EDIT);
		pEdit->SetWindowText((LPCTSTR)commonS);
		if(commonS.IsEmpty())
		{
			MessageBox("Error ! X is Empty","Error");
			return;
		}
		if(!IsIn(commonS,Relate.GetR()))
		{
			MessageBox("Error ! X isn't attribute","Error");
			return;
		}
		if(Relate.BagOfX(commonS,tempS))
		{
			pEdit = (CEdit *)GetDlgItem(IDC_BAG_OF_X_EDIT);
			pEdit->SetWindowText((LPCTSTR)tempS);
		}
		else
			MessageBox("Error ! Can't find any BagOfX","Error");
	}
}


void CDesignDlg::OnDependOfXButton() 
{
	// TODO: Add your control notification handler code here
	if(Relate.GetR().IsEmpty())
	{
		MessageBox("Error ! Relation is empty","Error");
		return;
	}

	CDepend dlgDepend(this);
	if(dlgDepend.DoModal()==IDOK)
	{

		CString tempS;
		CStringArray aszTemp;

		CEdit* pEdit = (CEdit *)GetDlgItem(IDC_DX_EDIT);
		pEdit->SetWindowText((LPCTSTR)commonS);

		if(commonS.IsEmpty())
		{
			MessageBox("Error ! X is Empty","Error");
			return;
		}
		if(!IsIn(commonS,Relate.GetR()))
		{
			MessageBox("Error ! X isn't attribute","Error");
			return;
		}
		if(Relate.DependOfX(commonS,aszTemp))
		{
			tempS.Empty();
			StringArrayToString(aszTemp,tempS);
			tempS +=")";
			CString S = "(";
			tempS = S + tempS;
		
			pEdit = (CEdit *)GetDlgItem(IDC_DEPEND_OF_X_EDIT);
			pEdit->SetWindowText((LPCTSTR)tempS);
		}
		else
			MessageBox("Error ! Can't find any DependOfX","Error");
	}
	
}


void CDesignDlg::OnDisRelateButton() 
{
	// TODO: Add your control notification handler code here
	if(Relate.GetR().IsEmpty())
	{
		MessageBox("Error ! Relation is empty","Error");
		return;
	}

	aDisRelate.RemoveAll();

	CArray<CFunc,CFunc&> aD;
	Relate.GetD(aD);
	commonInt = aD.GetSize();
	if(commonInt== 0)
		aDisRelate.Add(Relate);
	else
	{
		CDisR dlgDisR(this);
		if(dlgDisR.DoModal()==IDOK)
		{
			CFunc f;
			CArray<CFunc,CFunc&> tempD;

			if((commonInt < 0)||(commonInt>=aD.GetSize()))
				commonInt = 0;
			Relate.GetD(tempD);
			f = tempD.GetAt(commonInt);
			tempD.RemoveAt(commonInt);
			tempD.InsertAt(0,f);
			Relate.SetD(tempD);
		
			CRelate::DisRelate(Relate,aDisRelate);
			Relate.SetD(aD);
		}
		else
			return;
	}

	if(!aDisRelate.GetSize())
	{
		MessageBox("Error ! aDisRelate is Empty ","Error");
		return;
	}
	CString tempS;
	for(int i=0;i<aDisRelate.GetSize()-1;i++)
	{
		tempS += aDisRelate.GetAt(i).GetR();
		tempS +=',';
	}
	tempS += aDisRelate.GetAt(i).GetR();

	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_DIS_RELATE_EDIT);
	pEdit->SetWindowText("");
	pEdit->SetWindowText((LPCTSTR)tempS);
}
void CDesignDlg::OnDisRelateEnhancedButton() 
{
	// TODO: Add your control notification handler code here
	if(Relate.GetR().IsEmpty())
	{
		MessageBox("Error ! Relation is empty","Error");
		return;
	}

	aDisRelate.RemoveAll();

	CArray<CFunc,CFunc&> tempD;
	Relate.GetD(tempD);
	if(tempD.GetSize() <= 0)
		aDisRelate.Add(Relate);
	else
	{
		CRelate::DisRelateEnhanced(Relate,aDisRelate);
		Relate.SetD(tempD);
	}
	
	if(!aDisRelate.GetSize())
	{
		MessageBox("Error ! aDisRelate is Empty ","Error");
		return;
	}
	CString tempS;
	for(int i=0;i<aDisRelate.GetSize()-1;i++)
	{
		tempS += aDisRelate.GetAt(i).GetR();
		tempS +=',';
	}
	tempS += aDisRelate.GetAt(i).GetR();

	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_DIS_RELATE_EDIT);
	pEdit->SetWindowText("");
	pEdit->SetWindowText((LPCTSTR)tempS);
}
void CDesignDlg::OnPttButton() 
{
	// TODO: Add your control notification handler code here
	if(Relate.GetR().IsEmpty())
	{
		MessageBox("Error ! Relation is empty","Error");
		return;
	}


	if(Relate.FindPhuTT(aPTT))
	{
		CPtt dlgPtt(this);
		dlgPtt.DoModal();	
	}
	else
		MessageBox("Error ! Can't find any Minimum","Error");
}

void CDesignDlg::OnCoSoTtButton() 
{
	// TODO: Add your control notification handler code here
	CMini dlgMini(this);
	dlgMini.DoModal();
}

void CDesignDlg::OnCollectButton() 
{
	// TODO: Add your control notification handler code here
	if(Relate.GetR().IsEmpty())
	{
		MessageBox("Error ! Relation is empty","Error");
		return;
	}

	CArray<CFunc,CFunc&> tempD;
	Relate.GetD(tempD);
	aCollectRelate.RemoveAll();
	if(tempD.GetSize() <= 0)
		aCollectRelate.Add(Relate);
	else
		CRelate::Collect(Relate,aCollectRelate);	

	if(!aCollectRelate.GetSize())
	{
		MessageBox("Error ! aCollectRelate is Empty ","Error");
		return;
	}
	CString tempS;
	for(int i=0;i<aCollectRelate.GetSize()-1;i++)
	{
		tempS += aCollectRelate.GetAt(i).GetR();
		tempS +=',';
	}
	tempS += aCollectRelate.GetAt(i).GetR();

	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_COLLECT_EDIT);
	pEdit->SetWindowText((LPCTSTR)tempS);
}

void CDesignDlg::OnViewDFullButton() 
{
	// TODO: Add your control notification handler code here

	CViewD dlgViewD(this);
	dlgViewD.DoModal();
}
void CDesignDlg::OnViewCollectFullButton() 
{
	// TODO: Add your control notification handler code here
	CViewColl dlgViewColl(this);
	dlgViewColl.DoModal();
}


void CDesignDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	Remind();
	
	char szFilter[] = "Text Files (*.dat)|*.dat|All Files (*.*)|*.*||";
	CFileDialog dlgFile(TRUE,"dat","Untitled",
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);

	dlgFile.m_ofn.lpstrInitialDir =(LPCTSTR)szInitDir; 
    
	if(dlgFile.DoModal() == IDOK)
	{
		CString szTempPathName = dlgFile.GetPathName();
		TRY //Mo file
		{
			CFile f(szTempPathName,CFile::modeRead);

			CString tempS;
			TRY//Doc file
			{
				
				UINT n=f.GetLength();
				HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE,n+1);
				LPSTR lpBuf = (LPSTR)::GlobalLock(hGlobal);

				UINT nBytesRead = f.Read(lpBuf,n);
				lpBuf[nBytesRead] = 0;
				tempS = lpBuf;
				::GlobalUnlock(hGlobal);
				::GlobalFree(hGlobal);
				
				tempS.TrimLeft();
				tempS.TrimRight();
				int index = tempS.Find('\n');
				if(index ==-1)
				{
					MessageBox("Error !File doesn't content data ","Error",MB_OK);
					return;
				
				}
				else
				{
					CString S=tempS.Left(index);
					S.TrimRight();
					if(S!="@DDB")
					{
						MessageBox("Error ! it isn't data file",
								"Error",MB_OK);
						return;
					}
					tempS.TrimLeft((LPCTSTR)S);
					tempS.TrimLeft();

				}
				if(!tempS.IsEmpty())
				{
					CString tempR,tempD;
					index = tempS.Find('\n');
					CEdit* pEdit;
					if(index == -1)		
					{
						tempR = tempS;
						if(tempR.IsEmpty())
						{
							MessageBox("Error ! R is empty","Error",MB_OK);
							return;
						}
						OnClearButton();
						pEdit = (CEdit *)GetDlgItem(IDC_R_EDIT);
						pEdit->SetWindowText((LPCTSTR)tempR);
						pEdit->SetModify(FALSE);
						pEdit = (CEdit *)GetDlgItem(IDC_D_EDIT);
						pEdit->SetWindowText("");
						pEdit->SetModify(FALSE);
					}
					else
					{
						CString szS = tempS.Left(index);
						szS.TrimRight();
						tempR = szS;
						if(tempR.IsEmpty())
						{
							MessageBox("Error ! R is empty","Error",MB_OK);
							return;
						}
						OnClearButton();
						pEdit = (CEdit *)GetDlgItem(IDC_R_EDIT);
						pEdit->SetWindowText((LPCTSTR)tempR);
						pEdit->SetModify(FALSE);

						tempS.TrimLeft((LPCTSTR)tempR);
						tempS.TrimLeft();
						tempD = tempS;
						pEdit = (CEdit *)GetDlgItem(IDC_D_EDIT);
						pEdit->SetWindowText((LPCTSTR)tempD);
						pEdit->SetModify(FALSE);
					}
					szPathName = szTempPathName;
					szFileName = f.GetFileName();
					szFileTitle = f.GetFileTitle();
					CString szDlgTitle = "Design - ";
					SetWindowText(szDlgTitle + szFileTitle);
				}
				else
				{
					MessageBox("Error !File doesn't content data ","Error",MB_OK);
					return;
				}
			}
			CATCH(CFileException,err) 
			{
				CString szError;
				szError = "Can't read file "+dlgFile.GetFileTitle();
				#ifdef _DEBUG
					afxDump <<szError<<err->m_cause<<"\n";
				#endif
				MessageBox((LPCTSTR)szError,"Error",MB_OK);
			}
			END_CATCH
		}
		CATCH(CFileException,err) 
		{
			CString szError;
			szError = "Can't open file "+dlgFile.GetFileTitle();
			#ifdef _DEBUG
				afxDump <<szError<<err->m_cause<<"\n";
			#endif
			MessageBox((LPCTSTR)szError,"Error",MB_OK);
		}
		END_CATCH
	
	}
}

void CDesignDlg::OnFileSave() 
{
	// TODO: Add your command handler code here
	if(szFileTitle == "Untitled")
	{
		OnFileSaveas();
		return;
	}
	CString szBuf,tempS;
	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_R_EDIT);
	pEdit->GetWindowText(tempS);
	Alpha(tempS,szBuf);
	if(szBuf.IsEmpty())
	{
		MessageBox("Error! R is empty","Error");
		return;
	}
	TRY //Mo file
	{
		CFile f(szPathName,CFile::modeCreate | CFile::modeWrite);

		f.Write("@DDB\n",5);
		f.Write((LPCTSTR)szBuf,szBuf.GetLength());
		f.Write("\n",1);
		pEdit->SetModify(FALSE);

		pEdit = (CEdit *)GetDlgItem(IDC_D_EDIT);
		pEdit->GetWindowText(szBuf);
		f.Write((LPCTSTR)szBuf,szBuf.GetLength());
		pEdit->SetModify(FALSE);
	}
	CATCH(CFileException,err)
	{
		CString szError;
		szError = "Can't save file " + szFileName;
		#ifdef _DEBUG
			afxDump <<szError<<err->m_cause<<"\n";
		#endif
		MessageBox((LPCTSTR)szError,"Error",MB_OK);
		
	}
	END_CATCH
}

void CDesignDlg::OnFileSaveas() 
{
	// TODO: Add your command handler code here
	CString szBuf,tempS;
	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_R_EDIT);
	pEdit->GetWindowText(tempS);
	Alpha(tempS,szBuf);
	if(szBuf.IsEmpty())
	{
		MessageBox("Error! R is empty","Error");
		return;
	}

	char szFilter[] = "Text Files (*.dat)|*.dat|All Files (*.*)|*.*||";
	CFileDialog dlgFile(FALSE,"dat",szFileTitle,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	dlgFile.m_ofn.lpstrInitialDir = szInitDir; 

	if(dlgFile.DoModal() == IDOK)
	{
		TRY //Mo file
		{
			CString szTempPathName = dlgFile.GetPathName();
			CFile f(szTempPathName,CFile::modeCreate | CFile::modeWrite);
	
			f.Write("@DDB\n",5);
			f.Write((LPCTSTR)szBuf,szBuf.GetLength());
			f.Write("\n",1);
			pEdit->SetModify(FALSE);
	
			pEdit = (CEdit *)GetDlgItem(IDC_D_EDIT);
			pEdit->GetWindowText(szBuf);
			f.Write((LPCTSTR)szBuf,szBuf.GetLength());
			pEdit->SetModify(FALSE);
	
			CString S1=szTempPathName;
			CString S2=szPathName;
			S1.TrimRight(f.GetFileName());
			S1.TrimRight("\\");
			S1.TrimRight();
			S2.TrimRight(szFileName);
			S2.TrimRight("\\");
			S2.TrimRight();
			
			if(S1==S2 && szFileName != f.GetFileName())
			{
				CFile f;
				TRY
				{
					f.Remove(szPathName);
				}
				CATCH(CFileException,err)
				{
					CString szError;
					szError = "Can't remove file " + szFileName;
					szError +=" because it has not save before";
					#ifdef _DEBUG
						afxDump <<szError<<err->m_cause<<"\n";
					#endif
					//MessageBox((LPCTSTR)szError,"Error",MB_OK);
				}
				END_CATCH
			}
			szPathName = szTempPathName;
			szFileName = f.GetFileName();
			szFileTitle = f.GetFileTitle();
			CString szDlgTitle = "Design - ";
			SetWindowText(szDlgTitle + szFileTitle);
		}
		CATCH(CFileException,err)
		{
			CString szError;
			szError = "Can't save as file " + szFileName;
			#ifdef _DEBUG
				afxDump <<szError<<err->m_cause<<"\n";
			#endif
			MessageBox((LPCTSTR)szError,"Error",MB_OK);
			
		}
		END_CATCH
	}
}

void CDesignDlg::OnFileNew() 
{
	// TODO: Add your command handler code here
	Remind();

	OnClearButton();
	szFileTitle ="Untitled";
	szFileName = "Untitled.dat";
	szPathName = szInitDir + "\\" +szFileName;
	CString szDlgTitle = "Design - ";
	SetWindowText(szDlgTitle + szFileTitle);

	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_R_EDIT);
	pEdit->SetModify(FALSE);
	pEdit = (CEdit *)GetDlgItem(IDC_D_EDIT);
	pEdit->SetModify(FALSE);
	
}

void CDesignDlg::Remind()
{
	CEdit* pREdit = (CEdit *)GetDlgItem(IDC_R_EDIT);
	CEdit* pDEdit = (CEdit *)GetDlgItem(IDC_D_EDIT);
	if(pREdit->GetModify() || pDEdit->GetModify())
	{
		if(MessageBox("File has changed ! Do you want to save?",
			"Remind",MB_OKCANCEL) ==IDOK)
		{
			if(szFileTitle =="Untitled")
				OnFileSaveas();
			else
				OnFileSave();
		}
	}

}


void CDesignDlg::OnContextHelp() 
{
	// TODO: Add your command handler code here
	CHelp dlgHelp(this);
	dlgHelp.DoModal();
}

void CDesignDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	Remind();
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
	
}




void CDesignDlg::OnGraphButton() 
{
	// TODO: Add your control notification handler code here
	CGraph dlgGraph(this);
	dlgGraph.DoModal();
}

void CDesignDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}
