// Graph.cpp : implementation file
//
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Design.h"
#include "Graph.h"
#include "Relate.h"
#include "Perform.h"
#include "Tool.h"
#include "Choose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraph dialog

CArray<CRelate,CRelate&>		aInput;
CArray<CRelate,CRelate&>		aOutput;
CArray<CUIntArray,CUIntArray&>	aGraph;
CRelateSchemaIns				rSchemaIns;	
extern CString szCurDir;
extern int commonInt;


void showLinearRiskD();

CGraphHelp::CGraphHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGraphHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphHelp, CDialog)
	//{{AFX_MSG_MAP(CGraphHelp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphHelp message handlers

BOOL CGraphHelp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	TRY //Mo file
	{
		CString s;
		s = szCurDir + "\\GraphHelp.hlp";
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

CGraph::CGraph(CWnd* pParent /*=NULL*/)
	: CDialog(CGraph::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraph)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraph)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraph, CDialog)
	//{{AFX_MSG_MAP(CGraph)
	ON_BN_CLICKED(IDC_PERFORM_BUTTON, OnPerformButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, OnClearButton)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveas)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ACCEPT_BUTTON, OnAcceptButton)
	ON_BN_CLICKED(IDC_FIND_KEY_BUTTON, OnFindKeyButton)
	ON_BN_CLICKED(IDC_TABLEAU_BUTTON, OnTableauButton)
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_BN_CLICKED(IDC_LINEARD_BUTTON, OnLineardButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGraph::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char s[256];
	wsprintf(s,"%s\\DATA",szCurDir);
	szInitDir = s ;
	szFileTitle ="Untitled";
	szFileName = "Untitled.txt";
	szPathName = szInitDir + "\\" +szFileName;

	CString szDlgTitle = "Design - ";
	SetWindowText(szDlgTitle + szFileTitle);
	
	aInput.RemoveAll();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CGraph message handlers
BOOL CGraph::UpdateRelate(CString szS)
{
	Empty();
	CStringArray aTemp;

	szS.TrimLeft();
	szS.TrimLeft('<');
	szS.TrimLeft();
	SplitString(szS,'<',aTemp);//Tach thanh tung quan he
	int i,j;

	if(aTemp.GetSize()==0)
	{
		MessageBox("Error! Data is Empty","Error");
		return FALSE;
	}
	for(i=0;i<aTemp.GetSize();i++)
	{
		CStringArray aszX;
		aTemp[i].TrimRight(';');
		aTemp[i].TrimRight();
		aTemp[i].TrimRight('>');
		aTemp[i].TrimRight();
		SplitString(aTemp[i],';',aszX);//Tach moi quan he thanh tap thuoc tnh 
									   //va tap phu thuoc
		if(aszX.GetSize()!=2)
		{
			MessageBox("Error! Data is nvalid","Error");
			return FALSE;
		}

		CString szR;
		CStringArray aszY;
		CArray<CFunc,CFunc&> aD;
		CRelate tempRelate;

		aszX[0].TrimLeft('R');aszX[0].TrimLeft();
		aszX[0].TrimLeft('{');aszX[0].TrimLeft();
		aszX[0].TrimRight('}');aszX[0].TrimRight();
		Alpha(aszX[0],szR);
		if(szR.IsEmpty())
		{
			MessageBox("Error! Data is nvalid","Error");
			return FALSE;
		}
		tempRelate.SetR(szR);

		aszX[1].TrimLeft('D');aszX[1].TrimLeft();
		aszX[1].TrimLeft('{');aszX[1].TrimLeft();
		aszX[1].TrimLeft('(');aszX[1].TrimLeft();
		aszX[1].TrimRight('}');aszX[1].TrimRight();
		SplitString(aszX[1],'(',aszY);//Tach rieng tung phu thuoc ham

		for(j=0;j<aszY.GetSize();j++)
		{
			CString s;
			aszY[j].TrimRight(',');aszY[j].TrimRight();
			aszY[j].TrimRight(')');aszY[j].TrimRight();

			if(aszY[j].Find("->>") != -1)
				s = "->>";
			else if(aszY[j].Find("->") != -1)
				s = "->";
			else continue;
		
			CStringArray aszZ;

			SplitString(aszY[j],(LPCTSTR)s,aszZ);
			if(aszZ.GetSize() == 2)
			{
				CStringArray X,Y;
				SplitString(aszZ[0],',',X);
				SplitString(aszZ[1],',',Y);
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
		tempRelate.SetD(aD);
		aInput.Add(tempRelate);
	}
	return TRUE;

}

void CGraph::showLinearRiskD()
{
	CRelateSchema& rSchema = rSchemaIns.m_RSchema;
	if(rSchema.m_aLinearRiskD.GetSize()==0)
		MessageBox("Khong co phu thuoc ham dan den mau thuan dang tuyen tinh","Thong bao");
	else
	{
		CString szaLinearRiskD;
		rSchema.OutputaLinearRiskDBrief(szaLinearRiskD);

		CString szNote="Co phu thuoc ham dan den mau thuan dang tuyen tinh\n\n";
		szNote += szaLinearRiskD + "\n\n[Press Ctrl + C to copy information]";
		MessageBox(szNote,"Thong bao");


		//CStdioFile f;
		//f.Open("c:\\pthmauthuan",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
		//f.WriteString(szNote);
		//f.Close();
	}

}

void TESTHR(HRESULT x){if FAILED(x) _com_issue_error(x);};
BOOL GetSchema(_ConnectionPtr&  pCnn, SchemaEnum QueryType, LONG idxFilter, CString sFilter, CString Name, CStringArray& aOutValue)
{
	try
	{
		SAFEARRAY FAR* psa = NULL;
		SAFEARRAYBOUND rgsabound;
		_variant_t  var;
		_variant_t  Array;
		rgsabound.lLbound = 0;
		rgsabound.cElements = 4;
		psa = SafeArrayCreate(VT_VARIANT, 1, &rgsabound);
		var.vt = VT_EMPTY;
		
		var.vt = VT_BSTR;
		_bstr_t str = (LPCTSTR)sFilter;
		var.bstrVal = str;
		SafeArrayPutElement(psa, &idxFilter, &var);
		Array.vt = VT_ARRAY|VT_VARIANT;
		Array.parray = psa;
		
		_RecordsetPtr   pRstSchema  = NULL;
        pRstSchema = pCnn->OpenSchema(QueryType,&Array);
        while(!(pRstSchema->EndOfFile))
        {
			_bstr_t value = pRstSchema->Fields->GetItem((LPCTSTR)Name)->Value;
			CString sValue=(LPCTSTR)value;
			aOutValue.Add(sValue);

			pRstSchema->MoveNext();
        }
        pRstSchema->Close();
		return TRUE;
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
		return FALSE;
	}
}
void CGraph::OnAcceptButton() 
{
	// TODO: Add your control notification handler code here

	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_ENTER_EDIT);
	CButton* pButton=(CButton*)GetDlgItem(IDC_PERFORM_BUTTON);
	CString szS;
	pEdit->GetWindowText(szS);
	if(szS.IsEmpty())
	{
		MessageBox("Error! R is empty","Error");
		pEdit->SetFocus();
		return;
	}
	if(!UpdateRelate(szS))
	{
		pEdit->SetFocus();
		return;
	}

	pButton->EnableWindow(TRUE);
	pButton=(CButton*)GetDlgItem(IDC_TABLEAU_BUTTON);
	pButton->EnableWindow(TRUE);
	pButton=(CButton*)GetDlgItem(IDC_CLEAR_BUTTON);
	pButton->EnableWindow(TRUE);
	pButton=(CButton*)GetDlgItem(IDC_FIND_KEY_BUTTON);
	pButton->EnableWindow(TRUE);
	pButton=(CButton*)GetDlgItem(IDC_LINEARD_BUTTON);
	pButton->EnableWindow(TRUE);

	if (MessageBox("Do you want to update schema instance?\nIf you press OK, may take long time if large schema", 
		"Update schema", MB_OKCANCEL | MB_DEFBUTTON1) == IDOK)
	{
		rSchemaIns.Update(szS);
		showLinearRiskD();
	}
	else
	{
		rSchemaIns.Empty();
		rSchemaIns.m_RSchema.Update(szS);
	}


	/*
	//Insert 	
	// De K10-1 : Tao bo (abcegdx) co duoc chap nhan theo co che qly pth co nguy co dan den mau thuan?
	rSchemaIns.InsertSafe(0,"A:a,B:b,C:c,E:e,G:g,D:d,X:x");
	rSchemaIns.Output(szS);
	MessageBox(szS);
	
	//Update
	// De K10-1 : Sua bo (abcegdx) thanh (abc'egdx) co duoc chap nhan theo co che qly pth co nguy co dan den mau thuan?
	rSchemaIns.EditSafe(0,0,"A:a,B:b,C:c',E:e,G:g,D:d,X:x");
	rSchemaIns.Output(szS);
	MessageBox(szS);
		
	// De K98-1 : Tao bo (bcgd) co duoc chap nhan theo co che qly pth co nguy co dan den mau thuan?
	rSchemaIns.InsertSafe(0,"B:b,C:c,G:g,D:d");
	rSchemaIns.Output(szS);
	MessageBox(szS);		
	*/
	// De K11-2 : Tao bo (ckw) co duoc chap nhan theo co che qly pth co nguy co dan den mau thuan?
	/*
	rSchemaIns.InsertSafe(6,"C:c,K:k,W:w");
	rSchemaIns.Output(szS);
	MessageBox(szS);		
	*/

	/*
    if(FAILED(::CoInitialize(NULL)))
        return;

	_ConnectionPtr  pConnection    = NULL;
	_bstr_t strCnn("Provider=SQLOLEDB;User ID=sa;Password=unisoft;Initial Catalog=pubs;Data Source=LOCNP");
	try
	{
		// Open connection.
		pConnection.CreateInstance(__uuidof(Connection));
		pConnection->Open (strCnn, "", "", adConnectUnspecified);
		CStringArray aOutTableName;
		if(!GetSchema(pConnection,adSchemaTables,3,"TABLE","TABLE_NAME",aOutTableName))
			return;
		LONG m=aOutTableName.GetSize();
		if(m==0)
			return;

		CString s;
		s.Format("Ta %lu",m);
		MessageBox(s);
		for(LONG i=0; i<m; i++)
		{
			CString TableName=aOutTableName.ElementAt(i);
			CStringArray aTableColName;
			if(!GetSchema(pConnection,adSchemaTables,2,TableName,"TABLE_NAME",aTableColName))//duyet ca cot nam trong table do
				return;
			LONG n=aTableColName.GetSize();
			if(n==0)
				continue;
			CString s;
			s.Format("Co %lu",n);
			MessageBox(s);
			for(LONG j=0; j<n; j++)
			{
				
			}

		}
		::CoUninitialize();
	}
	catch (_com_error &e)
	{
		MessageBox(e.ErrorMessage());
		::CoUninitialize();
	}
	*/
}
/*
Vao:
	pCnn:Connection
	QueryType:Loai luoc do tra ve VD :  adSchemaTables
	idxFilter, sFilter:chi muc va chuoi dung de loc cac pt cua luoc do tra ve VD:3 va "TABLE"
	Name:Ten cua field can tra ve (tri cua field nay nam trong aOutValue)
Ra:
	aOutValue: mang chua tri tra ve
*/
void CGraph::OnPerformButton() 
{
	// TODO: Add your control notification handler code here
	if(CRelate::PerformToGraph(aInput,aOutput,aGraph))
	{
		CPerform dlgPerform(this);
		dlgPerform.DoModal();
	}
	else
		MessageBox("Error! Relate is invalid or empty","Error");
}
void CGraph::OnTableauButton() //Thuat toan Tableau
{
	// TODO: Add your control notification handler code here
	if(CRelate::Tableau(aInput))
		MessageBox("PHAN RA NAY BAO TOAN THONG TIN","Thong bao");
	else
		MessageBox("PHAN RA NAY KHONG BAO TOAN THONG TIN","Thong bao");

}

void CGraph::Empty()
{
	aInput.RemoveAll();
	aOutput.RemoveAll();
	for(int i=0;i<aGraph.GetSize();i++)
		aGraph[i].RemoveAll();
	aGraph.RemoveAll();

	CButton* pButton=(CButton*)GetDlgItem(IDC_PERFORM_BUTTON);

	pButton->EnableWindow(FALSE);
	pButton=(CButton*)GetDlgItem(IDC_TABLEAU_BUTTON);
	pButton->EnableWindow(FALSE);
	pButton=(CButton*)GetDlgItem(IDC_CLEAR_BUTTON);
	pButton->EnableWindow(FALSE);
	pButton=(CButton*)GetDlgItem(IDC_FIND_KEY_BUTTON);
	pButton->EnableWindow(FALSE);

	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_KEY_EDIT);
	pEdit->SetWindowText("");
	CStatic* pStatic=(CStatic*)GetDlgItem(IDC_KEY_STATIC);
	pStatic->SetWindowText("");

}


void CGraph::OnClearButton() 
{
	// TODO: Add your control notification handler code here

	Empty();
	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_ENTER_EDIT);
	pEdit->SetWindowText("");
	pEdit->SetModify(TRUE);
	pEdit->SetFocus();
}


void CGraph::OnFileExit() 
{
	// TODO: Add your command handler code here
	OnOK();
}

void CGraph::OnFileNew() 
{
	// TODO: Add your command handler code here
	Remind();

	OnClearButton();
	szFileTitle ="Untitled";
	szFileName = "Untitled.txt";
	szPathName = szInitDir + "\\" +szFileName;
	CString szDlgTitle = "Design - ";
	SetWindowText(szDlgTitle + szFileTitle);

	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_ENTER_EDIT);
	pEdit->SetModify(FALSE);
	
}

void CGraph::OnFileOpen() 
{
	// TODO: Add your command handler code here
	Remind();
	
	char szFilter[] = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CFileDialog dlgFile(TRUE,"txt","Untitled",
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
					if(S!="<@DDB>")
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
					
					OnClearButton();
					CEdit* pEdit = (CEdit *)GetDlgItem(IDC_ENTER_EDIT);
					pEdit->SetWindowText(tempS);
					pEdit->SetModify(FALSE);

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
    

void CGraph::OnFileSave() 
{
	// TODO: Add your command handler code here
	if(szFileTitle == "Untitled")
	{
		OnFileSaveas();
		return;
	}
	CString szBuf;
	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_ENTER_EDIT);
	pEdit->GetWindowText(szBuf);
	if(szBuf.IsEmpty())
	{
		MessageBox("Error! R is empty","Error");
		return;
	}
	TRY //Mo file
	{
		CFile f(szPathName,CFile::modeCreate | CFile::modeWrite);
		f.Write("<@DDB>\n",7);
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

void CGraph::OnFileSaveas() 
{
	// TODO: Add your command handler code here
	CString szBuf;
	CEdit* pEdit = (CEdit *)GetDlgItem(IDC_ENTER_EDIT);
	pEdit->GetWindowText(szBuf);
	if(szBuf.IsEmpty())
	{
		MessageBox("Error! R is empty","Error");
		return;
	}

	char szFilter[] = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CFileDialog dlgFile(FALSE,"txt",szFileTitle,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	dlgFile.m_ofn.lpstrInitialDir = szInitDir; 

	if(dlgFile.DoModal() == IDOK)
	{
		TRY //Mo file
		{
			CString szTempPathName = dlgFile.GetPathName();
			CFile f(szTempPathName,CFile::modeCreate | CFile::modeWrite);
	
			f.Write("<@DDB>\n",7);
			f.Write((LPCTSTR)szBuf,szBuf.GetLength());
	
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
void CGraph::Remind()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_ENTER_EDIT);
	if(pEdit->GetModify())
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

void CGraph::OnDestroy() 
{
	CDialog::OnDestroy();
	Remind();	
	// TODO: Add your message handler code here
	
}


void CGraph::OnFindKeyButton() 
{
	// TODO: Add your control notification handler code here
	int n;
	if(n=aInput.GetSize())
	{
		commonInt=n;
		CChoose dlgChoose(this);	
		if(dlgChoose.DoModal()==IDOK)
		{
			if(commonInt<0||commonInt>=n)
				commonInt=0;
			CStringArray aszK;
			CString szK;
			CRelate tempRelate=aInput;
			tempRelate.SetR(aInput[commonInt].GetR());
			tempRelate.EssenceRD();
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



void CGraph::OnContextHelp() 
{
	// TODO: Add your command handler code here
	CGraphHelp dlgHelp(this);
	dlgHelp.DoModal();
}	


void CGraph::OnLineardButton() 
{
	// TODO: Add your control notification handler code here
	rSchemaIns.m_RSchema.FindLinearRiskD();
	showLinearRiskD();	

	/*
	CRelateSchemaIns	SIns;
	CMapStringToString	rec;
	CRelateSchemaIns	TempSchemaIns;
	CStringArray		aSQL;
	//SIns.TestUpdate(0,0,TempSchemaIns,rec,TRUE,aSQL);
	CString a="dghdgjsgjds";
	CString& b=a;
	b="Loc";
	MessageBox(a);
	*/
}


