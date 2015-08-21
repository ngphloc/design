// Relate.cpp: implementation of the CRelate class.
//
//////////////////////////////////////////////////////////////////////
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Relate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFunc::CFunc()
{
	Empty();
}
CFunc::CFunc(CFunc& Func)
{
	SetFunc(Func);
}
CFunc:: ~CFunc()
{
	Empty();
}

void CFunc::SetFunc(CFunc& Func)
{
	SetX(Func.GetX());
	SetY(Func.GetY());
	SetFlag(Func.GetFlag());
}
CFunc& CFunc::operator = (CFunc& Func)
{
	SetFunc(Func);
	return *this;
}
BOOL CFunc::operator == (CFunc& Func)
{
	CString X1,Y1,X2,Y2;
	BOOL Flag1,Flag2,ret;
	X1=Union(m_aszX);Y1=Union(m_aszY);
	X2=Union(Func.GetX());Y2=Union(Func.GetY());
	Flag1=m_bFlag;
	Flag2=Func.GetFlag();
	
	ret=(IsEqual(X1,X2))&&(IsEqual(Y1,Y2))&&((Flag1==TRUE&&Flag2==TRUE)||
							 (Flag1==FALSE&&Flag2==FALSE));
	return ret;
}
BOOL CFunc::operator != (CFunc& Func)
{
	CString X1,Y1,X2,Y2;
	BOOL Flag1,Flag2,ret;
	X1=Union(m_aszX);Y1=Union(m_aszY);
	X2=Union(Func.GetX());Y2=Union(Func.GetY());
	Flag1=m_bFlag;
	Flag2=Func.GetFlag();
	
	ret=(!IsEqual(X1,X2))||(!IsEqual(Y1,Y2))||(Flag1==TRUE&&Flag2==FALSE)||
							(Flag1==FALSE&&Flag2==TRUE);
	return ret;

}

CStringArray& CFunc::GetX()
{
	return m_aszX;
}
CStringArray& CFunc::GetY()
{
	return m_aszY;
}
BOOL CFunc::GetFlag()
{
	return m_bFlag;
}
CString	CFunc::GetXStr()
{
	return Union(m_aszX);
}
CString	CFunc::GetYStr()
{
	return Union(m_aszY);
}
CString	CFunc::GetXYStr()
{
	return GetXStr() + GetYStr();
}
	
void CFunc::SetX(CStringArray&  aszX)
{
	int i;
	CString tempS;
	m_aszX.RemoveAll();
	for(i=0;i<aszX.GetSize();i++)
	{
		tempS=Essence(aszX[i]);
		m_aszX.Add(tempS);
	}
}
void CFunc::SetY(CStringArray&  aszY)
{
	int i;
	CString tempS;
	m_aszY.RemoveAll();
	for(i=0;i<aszY.GetSize();i++)
	{
		tempS=Essence(aszY[i]);
		m_aszY.Add(tempS);
	}
}
void CFunc::SetX(CString&  szX)
{
	m_aszX.RemoveAll();
	m_aszX.Add(Essence(szX));
}
void CFunc::SetY(CString&  szY)
{
	m_aszY.RemoveAll();
	m_aszY.Add(Essence(szY));
}
void CFunc::SetFlag(BOOL Flag)
{
	m_bFlag = Flag;
}
void CFunc::Empty()
{
	m_aszX.RemoveAll();
	m_aszY.RemoveAll();

}
BOOL CFunc::IsEmpty()
{
	if(m_aszX.GetSize() && m_aszY.GetSize())
		return FALSE;

	return TRUE;
}

//Phan ra phu thuoc ham VD: A->BCDE thanh A->B, A->C, A->D, A->E
BOOL CFunc::Dis(CArray<CFunc, CFunc&>& aD)
{
	if(IsEmpty())
		return FALSE;

	aD.RemoveAll();
	LONG m=GetY().GetSize();
	for(LONG i=0; i<m; i++)
	{
		if(!GetFlag())//Neu day la phu thuoc da tri
		{
			CFunc d;
			d.SetX(GetX());
			d.SetY(GetY().GetAt(i));
			d.SetFlag(GetFlag());
			aD.Add(d);
		}
		else
		{
			CString Y=GetY().GetAt(i);
			LONG length=Y.GetLength();
			if(length==1)
			{
				CFunc d;
				d.SetX(GetX());
				d.SetY(Y);
				d.SetFlag(GetFlag());
				aD.Add(d);
			}
			else
			{
				for(LONG j=0; j<length; j++)
				{
					CString y='A';
					y.SetAt(0,Y.GetAt(j));

					CFunc d;
					d.SetX(GetX());
					d.SetY(y);
					d.SetFlag(GetFlag());
					aD.Add(d);
				}
			}
		}
	}
	return TRUE;
}
//Kiem tra phu thuoc ham hien tai co cung X voi phu thuoc ham d khong
BOOL CFunc::IsSameX(CFunc& d)
{
	return IsEqual(GetX(),d.GetX()) && GetFlag()==d.GetFlag();
}
//Gom nhom neu nhu cung X, ham nay nguoc voi ham Dis o tren
BOOL CFunc::UnionY(CFunc& d, BOOL bTestX)
{
	if(bTestX)
	{
		if(!IsSameX(d))
			return FALSE;
	}

	CString Y=Union(GetY(),d.GetY());
	SetY(Y);
	return TRUE;
}
BOOL CFunc::IsInRelate(CRelate& R)
{
	return IsIn(Union(GetX(),GetY()),R.GetR());
}

void CFunc::Output(CString& szS)
{
	szS.Empty();
	CString X, Y;
	StringArrayToString(GetX(),X);
	StringArrayToString(GetY(),Y);
	if(GetFlag())
		szS= szS + X + "->" + Y;
	else
		szS = szS + X + "->>" + Y;
}
/************************************************************/
CRelate::CRelate()
{
	Empty();	
}
CRelate::CRelate(CRelate& Relate)
{
	SetRelate(Relate);
}
CRelate::CRelate(CArray<CRelate,CRelate&>& aInput)
{
	SetRelate(aInput);
}
CRelate::~CRelate()
{
	Empty();
}

void CRelate::SetRelate(CRelate& Relate)
{
	CArray<CFunc, CFunc&>  aD;
	SetR(Relate.GetR());
	Relate.GetD(aD);
	SetD(aD);
	SetK(Relate.m_aszK);
}
void CRelate::SetRelate(CArray<CRelate,CRelate&>& aInput)
{
	CString tempS;
	CStringArray aK;
	int i,j;

	for(i=0;i<aInput.GetSize();i++)
		tempS +=aInput[i].GetR();
	SetR(tempS);

	m_aD.RemoveAll();
	for(i=0;i<aInput.GetSize();i++)
	{
		CArray<CFunc,CFunc&> aTempD;
		aInput[i].GetD(aTempD);
		for(j=0;j<aTempD.GetSize();j++)
			m_aD.Add(aTempD[j]);
	}
	
}
CRelate& CRelate::operator = (CRelate& Relate)
{
	SetRelate(Relate);
	return *this;
}
CRelate& CRelate::operator = (CArray<CRelate,CRelate&>& aInput)
{
	SetRelate(aInput);
	return *this;
}
BOOL CRelate::operator == (CRelate& Relate)
{
	//To do code
	return TRUE;
}
BOOL CRelate::operator != (CRelate& Relate)
{
	//To do code
	return TRUE;
}
CRelate& CRelate::operator += (CRelate& Relate)
{
	m_szR+=Relate.GetR();
	CArray<CFunc,CFunc&> aD;
	Relate.GetD(aD);
	for(int i=0;i<aD.GetSize();i++)
		m_aD.Add(aD[i]);
	return *this;
}
CRelate CRelate::operator +  (CRelate& Relate)
{
	CRelate tempRelate;
	CString szR;
	CArray<CFunc,CFunc&> aD;

	szR=m_szR+Relate.GetR();
	tempRelate.SetR(szR);

	Relate.GetD(aD);
	for(int i=0;i<m_aD.GetSize();i++)
		aD.Add(m_aD[i]);
	tempRelate.SetD(aD);

	return tempRelate;
}

CString& CRelate::GetR()
{
	return m_szR;
}

void CRelate::GetD(CArray<CFunc, CFunc&>& aD)
{
	aD.RemoveAll();
	for(int i=0;i<m_aD.GetSize();i++)
		aD.Add(m_aD[i]);
}

void CRelate::GetK(CStringArray& aszK)
{
	aszK.RemoveAll();
	for(int i=0;i<m_aszK.GetSize();i++)
		aszK.Add(m_aszK[i]);
}
	
void CRelate::SetR(CString&	R)
{
	m_szR=R;
	m_aszK.RemoveAll();
}
void CRelate::SetD(CArray<CFunc, CFunc&>&  aD)
{
	m_aD.RemoveAll();
	for(int i=0;i<aD.GetSize();i++)
		m_aD.Add(aD[i]);
	m_aszK.RemoveAll();
}
void CRelate::SetK(CStringArray& aszK)
{
	m_aszK.RemoveAll();
	for(int i=0;i<aszK.GetSize();i++)
		m_aszK.Add(aszK[i]);
}
void CRelate::Empty()
{
	m_szR.Empty();
	m_aD.RemoveAll();
	m_aszK.RemoveAll();
}
BOOL CRelate::IsEmpty()
{
	return m_szR.IsEmpty();
}
void CRelate::Output(CString& szS)
{
	CString szR;
	CString tempS;
	tempS = m_name.name + "{";
	szR = tempS + m_szR + "}";

	CString szD;
	tempS = "D{";
	for(int i=0;i<m_aD.GetSize();i++)
	{
		CString X,Y,S;
		S = "(";
		StringArrayToString(m_aD[i].GetX(),X);
		StringArrayToString(m_aD[i].GetY(),Y);
		if(m_aD[i].GetFlag() == TRUE)
			X = S + X + "->" + Y + ")";
		else
			X = S + X + "->>" + Y + ")";

		szD +=X ;
		if(i<m_aD.GetSize()-1)
			szD +=",";

	}
	szD = tempS + szD + "}";

	szS = szR + ";" + szD;
}
void CRelate::OutputBrief(CString& szS)
{
	szS=m_szR;
}
//Ham chuyen chuoi mo ta thanh quan he
BOOL CRelate::Update(CString tempR, CString tempD)
{
	//Cap nhat the hien quan he;
	CString S;
	Alpha(tempR,S);
	if(S.IsEmpty())
	{
		AfxMessageBox("Error ! R is Empty",MB_OK,0);
		return FALSE;
	}
	SetR(S);
	
	//Cac thao tac tao phu thuoc
	if(tempD.IsEmpty())
	{
		m_aD.RemoveAll();
		return TRUE;
	}
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
	SetD(aD);
	return TRUE;
}
BOOL CRelate::Update(CString szS)
{
	Empty();

	szS.TrimLeft();
	szS.TrimLeft('<');
	szS.TrimLeft();
	LONG j;

	CStringArray aszX;
	szS.TrimRight();
	szS.TrimRight('>');
	szS.TrimRight();
	SplitString(szS,';',aszX);//Tach moi quan he thanh tap thuoc tinh va tap phu thuoc								   
	
	if(aszX.GetSize()!=2)
	{
		AfxMessageBox("Error! Data is nvalid",MB_OK,0);
		return FALSE;
	}

	CString szR;
	CStringArray aszY;
	CArray<CFunc,CFunc&> aD;

	aszX[0].TrimLeft('R');aszX[0].TrimLeft();
	aszX[0].TrimLeft('{');aszX[0].TrimLeft();
	aszX[0].TrimRight('}');aszX[0].TrimRight();
	Alpha(aszX[0],szR);
	if(szR.IsEmpty())
	{
		AfxMessageBox("Error! Data is nvalid",MB_OK,0);
		return FALSE;
	}
	SetR(szR);

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
	SetD(aD);
	return TRUE;
}

/*****Thuat toan tim bao dong cua mot tap X nho tap phu thuoc ham F*****/

//Vao Relate: quan he R 
//	  X:1 hay nhieu thuoc tinh
//Ra  FX: Bao dong cua tap X dua vao tap phu thuoc ham Relate.aD	

BOOL CRelate::BagOfX(CString X, CString& XF)
{
	if(m_szR.IsEmpty() || X.IsEmpty() || !IsIn(X,m_szR))
		return FALSE;
	
	CArray<CFunc, CFunc&>  aD;	
	CStringArray aX;
	int i,j;

	XF = X;
	for(i=0;i<m_aD.GetSize();i++)
		if(m_aD[i].GetFlag())
			aD.Add(m_aD[i]);
	if(aD.GetSize() == 0)
		return TRUE;

	for(i=0;i<3;i++)
		aX.Add(XF);

	while(aD.GetSize())
	{
		i=0;
		while(i<aD.GetSize())	
		{
			CString tempS;
			tempS = Union(aD[i].GetX());
			if(IsIn(tempS,XF))
			{
				tempS.IsEmpty();
				tempS = Union(aD[i].GetY());
				XF=Union(XF,tempS);
				aD.RemoveAt(i);
			}
			else	
				i++;
		}
		aX.RemoveAt(0);
		aX.Add(XF);

		if(IsEqual(XF,m_szR))
			break;

		for(j=0;j<aX.GetSize()-1;j++)
			if(!IsEqual(aX[j],aX[j+1]))		
				break;

		if(j==aX.GetSize()-1)//Neu Xn = Xn+1 = Xn+2
			break;
	}
	return TRUE;
}
BOOL CRelate::BagOfX(CStringArray& aszX, CStringArray& aszY)
{
	aszY.RemoveAll();
	int countFalse=0;
	for(int i=0;i<aszX.GetSize();i++)
	{
		CString tempS;
		BOOL ret=BagOfX(aszX[i],tempS);
		aszY.Add(tempS);
		if(!ret)
			countFalse++;
	}
	if(countFalse==aszX.GetSize())
		return FALSE;
	return TRUE;
}
/********************Thuat toan phu toi thieu****************/

//Ra aPTT : tap phu toi thieu
BOOL CRelate::FindPhuTT(CArray<CFunc, CFunc&>&  aPTT)
{
	if(m_szR.IsEmpty())
		return FALSE;

	int i,j;
	aPTT.RemoveAll();

	for(i=0;i<m_aD.GetSize();i++)
		if(m_aD[i].GetFlag())//Neu la phu thuoc ham
			aPTT.Add(m_aD[i]);
	if(aPTT.GetSize()==0)
		return FALSE;

//tao nhung phu thuoc ham day du	
	for(i=0;i<aPTT.GetSize();i++)
	{
		CStringArray aszC;
		CString S = Union(aPTT[i].GetX());
		Combine(S,"",0,aszC);
		Sort(aszC);
		for(j=0;j<aszC.GetSize();j++)
		{
			CString tempS;
			CRelate Relate;
			Relate.SetR(m_szR);
			Relate.SetD(aPTT);
			Relate.BagOfX(aszC[j],tempS);
			if(IsIn(aPTT[i].GetY(),tempS))
				break;
		}
		
		if(j<aszC.GetSize())
		{
			CFunc f(aPTT[i]);
			CStringArray aszX ;
			aszX.Add(aszC[j]);
			f.SetX(aszX);

			aPTT.SetAt(i,f);
		}

	}
	
//loai bo nhung phu thuoc ham thua	
	i=0;
	while(i<aPTT.GetSize())
	{
		CRelate Relate;
		CArray<CFunc, CFunc&>  aD;

		for(j=0;j<aPTT.GetSize();j++)
			aD.Add(aPTT[j]);
		aD.RemoveAt(i);
		
		Relate.SetR(m_szR);
		Relate.SetD(aD);
		CString tempS,XF;
		tempS = Union(aPTT[i].GetX());
		Relate.BagOfX(tempS,XF);
		tempS = Sub(aPTT[i].GetY(),XF);
		if(tempS.IsEmpty())
			aPTT.RemoveAt(i);
		else
		{
			CFunc f=aPTT[i];
			CStringArray aszTemp;
			aszTemp.Add(tempS);
			f.SetY(aszTemp);
			aPTT.SetAt(i,f);
			i++;
		}
			
	}
//loai bo nhung thuoc tinh thua o ve phai cua moi phu thuoc ham
	i=0;
	while(i<aPTT.GetSize())
	{
		CRelate Relate;
		CArray<CFunc, CFunc&>  aD;

		for(j=0;j<aPTT.GetSize();j++)
			aD.Add(aPTT[j]);
		aD.RemoveAt(i);
		Relate.SetR(m_szR);
		Relate.SetD(aD);

		CString tempS = Union(aPTT[i].GetY());

		j=0;
		while(j<tempS.GetLength())
		{
			CString S,X,XF,s1,s2;
			S+= tempS[j];
			s1 = tempS.Left(j);
			s2 = tempS.Mid(j,tempS.GetLength()-j);
			s2.TrimLeft(S);
			X = s1 + s2;

			Relate.BagOfX(X,XF);
			if(IsIn(S,XF))
				tempS = X;
			else
				j++;
		}
		
		if(tempS.IsEmpty())
			aPTT.RemoveAt(i);
		else
		{
			CFunc f=aPTT[i];
			CStringArray aszTemp;
			aszTemp.Add(tempS);
			f.SetY(aszTemp);
			aPTT.SetAt(i,f);
			i++;
		}

	}
//Nhap nhung phu thuoc ham co cung ve trai
	i=0;
	while(i<aPTT.GetSize()-1)
	{
		for(j=i+1;j<aPTT.GetSize();j++)
			if(IsEqual( Union(aPTT[i].GetX()),Union(aPTT[j].GetX())))
				break;
		if(j<aPTT.GetSize())
		{
			CFunc f=aPTT[i];
			CString tempS = Union( Union(aPTT[i].GetY()),Union(aPTT[j].GetY()));
			CStringArray aszTemp;
			aszTemp.Add(tempS);
			f.SetY(aszTemp);
			aPTT.SetAt(i,f);
			aPTT.RemoveAt(j);
		}
		else
			i++;
	}
	return TRUE;
}

/********************Thuat toan tim khoa*********************/

//Bien nay duoc dinh nghia trong Tool.cpp

BOOL CRelate::FindKey()
{
	if(m_szR.IsEmpty())
		return FALSE;

	if(m_aD.GetSize()==0)
	{
		m_aszK.Add(m_szR);
		return TRUE;
	}

	m_aszK.RemoveAll();	
	CString srcX, destY;//tap nguon, tap dich
	CString S,tempS;//Tap trung gian
	CStringArray aszTempX,aszTempY;
	int i;
	for(i=0;i<m_aD.GetSize();i++)
		if(m_aD[i].GetFlag())//Neu la phu thuoc ham
		{
			aszTempX.Append(m_aD[i].GetX());
			aszTempY.Append(m_aD[i].GetY());
		}
	tempS=srcX = Union(aszTempX);
	destY = Union(aszTempY);
	srcX = Sub(srcX,destY);//tao tap nguon
	destY = Sub(destY,tempS);//tao tap dich
	S=Sub(Sub(m_szR,srcX), destY);//Tao tap trung gian

	srcX=Common(srcX,m_szR);
	destY=Common(destY,m_szR);
	S=Common(S,m_szR);

	CString XF;
	BagOfX(srcX,XF);

	if(IsIn(m_szR,XF))//Neu tap srcX la khoa
	{
		m_aszK.Add(srcX);
		return TRUE;
	}

	CStringArray aszC;
	Combine(S,"",0,aszC);//tao cac to hop tu tap trung gian
	Sort(aszC);
	CString szK;
	while(aszC.GetSize())
	{
		tempS = aszC[0];
		szK = srcX + tempS;
		aszC.RemoveAt(0);

		XF.Empty();
		BagOfX(szK,XF);
		if(IsIn(m_szR,XF))//Neu tap szK la khoa
		{
			m_aszK.Add(szK);
			i=0;
			while(i<aszC.GetSize())
			{
				if(IsIn(tempS,aszC[i]))
					aszC.RemoveAt(i);
				else
					i++;
			}
		}
	}
	if(m_aszK.GetSize())
		return TRUE;
	AfxMessageBox("No Key",MB_OK,0);
	return FALSE;
}

/***********Thuat toan tim tap phu thuoc da tri cua X dua tren D*************/

//ham tim tap phu thuoc da tri cua X du tren tap phu thuoc ham
//Vao : X : tap thuoc tinh
//Ra  : G :tap Thuoc tinh cua X dua tren tap phu thuoc da tri

BOOL CRelate::DependOfX(CString szX, CStringArray& aszG)
{
	if(m_szR.IsEmpty() || szX.IsEmpty() || !IsIn(szX,m_szR))
		return FALSE;

	aszG.RemoveAll();
	int i;
	CString tempS;

	for(i=0;i<szX.GetLength();i++)
	{	
		tempS=szX[i];
		aszG.Add(tempS);
	}
	if(m_aD.GetSize()==0)
		return TRUE;

//Buoc 1
	CArray<CFunc, CFunc&>  aD;
	for(i=0;i<m_aD.GetSize();i++)
		aD.Add(m_aD[i]);

	for(i=0;i<aD.GetSize();i++)
	{
		if(IsIn(aD[i].GetX(),szX))
		{
			aszG.Append(aD[i].GetY());
			tempS = Union(aD[i].GetX()) + Union(aD[i].GetY());
			aszG.Add(Sub(m_szR,tempS));
		}
	}
//Buoc 2
	CStringArray tempG;
	Minimum(aszG,tempG);
	aszG.RemoveAll();
	aszG.Append(tempG);
	tempG.RemoveAll();
//Buoc 3
	//tao cac to hop co the cua aszG
	//aszC = new CStringArray; 
	CStringArray aszC; 
	Combine(aszG,"",0,aszC);
	Sort(aszC);
	int j,k;
	for(i=0;i<aD.GetSize();i++)
	{
		
		for(j=0;j<aszC.GetSize();j++)
		{
			if(IsIn(aD[i].GetX(),aszC.GetAt(j)))
			{
				tempS = Sub(aD[i].GetY(),aszC.GetAt(j));//Z-Y
				for(k=0;k<aszC.GetSize();k++)
					if(IsEqual(tempS,aszC.GetAt(k)))
						break;
				if(k==aszC.GetSize())//Neu khong ton tai
				{
					aszG.Add(tempS);
					Minimum(aszG,tempG);
					aszG.RemoveAll();
					aszG.Append(tempG);
					tempG.RemoveAll();
					break;
				}
			}
		}
	}
	return TRUE;
}
/****Loai bo nhung phu thuoc ham thua va phu thuoc da tri***/
void CRelate::EssenceD()
{
	int i=0,j;
	while(i<m_aD.GetSize())
	{
		CString tempS;
		tempS=Union(m_aD[i].GetX());
		if(!IsIn(tempS,m_szR)||!m_aD[i].GetFlag())
			m_aD.RemoveAt(i);
		else
		{
			tempS=Common(Union(m_aD[i].GetY()),m_szR);
			if(tempS.IsEmpty())
				m_aD.RemoveAt(i);
			else
			{
				CFunc f=m_aD[i];
				CStringArray aszY;
				aszY.Add(tempS);
				f.SetY(aszY);
				m_aD.SetAt(i,f);
				i++;
			}
		}
	}
	CArray<CFunc,CFunc&> tempD;
	for(i=0;i<m_aD.GetSize();i++)
	{
		for(j=0;j<tempD.GetSize();j++)
			if(tempD[j]==m_aD[i])
				break;
		if(j==tempD.GetSize())
			tempD.Add(m_aD[i]);
	}
	this->SetD(tempD);
}
void CRelate::EssenceR()
{
	m_szR=Essence(m_szR);
}
void CRelate::EssenceRD()
{
	EssenceR();
	EssenceD();
}

/********************Thuat toan phan ra*********************/

//Ham phan ra
//Vao  Relate:Quan he R
//Ra   aDisRelate:mang chua cac quan he 
void CRelate::DisRelate(CRelate Relate, CArray<CRelate, CRelate&>& aDisRelate)
{
	
	if(Relate.GetR().IsEmpty())
		return;

	int i;
	CArray<CFunc, CFunc&>  aD;
	CStringArray aszTemp;
	CString tempS;
	Relate.GetD(aD);

//Buoc 1
	i=0;
	while(i<aD.GetSize())
	{
		aszTemp.RemoveAll();
		aszTemp.Append(aD[i].GetX());
		aszTemp.Append(aD[i].GetY());
		tempS = Union(aszTemp);

		if(!IsIn(tempS,Relate.GetR()))
			aD.RemoveAt(i);
		else
			i++;
	}

	CRelate tempRelate;
	tempRelate.SetD(aD);
	tempRelate.SetR(Relate.GetR());

//Buoc 2
	
	i=0;
	while(i<aD.GetSize())
	{
		aszTemp.RemoveAll();
		aszTemp.Append(aD[i].GetX());
		aszTemp.Append(aD[i].GetY());
		tempS = Union(aszTemp);

		if(IsEqual(tempS,Relate.GetR()))
			aD.RemoveAt(i);
		else
			i++;
	}

//Buoc 3

	if(aD.GetSize()==0)
		aDisRelate.Add(tempRelate);
	else
	{
		BOOL NotFound=TRUE;	
		for(i=0;(i<aD.GetSize())&&(NotFound);i++)
		{
			CRelate Relate1,Relate2;

			aszTemp.RemoveAll();
			aszTemp.Append(aD[i].GetX());
			aszTemp.Append(aD[i].GetY());
			tempS = Union(aszTemp);
			Relate1 = tempRelate;
			Relate1.SetR(tempS);

			tempS=Union(aD[i].GetY());
			tempS = Sub(Relate.GetR(),tempS);
			Relate2 = tempRelate;
			Relate2.SetR(tempS);

			DisRelate(Relate1,aDisRelate);
			DisRelate(Relate2,aDisRelate);
			NotFound = FALSE;

		}
		if(NotFound)
			AfxMessageBox("Error ! Can't Disintegrate",MB_OK,(UINT)0);
	}
}

/******************Thuat toan phan ra cai tien********************/

//Ham phan ra cai tien : chon ham phan ra la ham vi pham tieu chuan BCK hay
//co ve phai khong xuat hien o ve phai cua cac phu thuoc ham khac
//Vao  Relate:Quan he R
//Ra   aDisRelate:mang chua cac quan he 

void CRelate::DisRelateEnhanced(CRelate Relate, CArray<CRelate, CRelate&>& aDisRelate)
{
	if(Relate.GetR().IsEmpty())
		return;

	int i,j;
	CArray<CFunc, CFunc&>  aD;
	CStringArray aszTemp;
	CString tempS;
	Relate.GetD(aD);

//Buoc 1
	i=0;
	while(i<aD.GetSize())
	{
		aszTemp.RemoveAll();
		aszTemp.Append(aD[i].GetX());
		aszTemp.Append(aD[i].GetY());
		tempS = Union(aszTemp);

		if(!IsIn(tempS,Relate.GetR()))
			aD.RemoveAt(i);
		else
			i++;
	}

	CRelate tempRelate;
	tempRelate.SetD(aD);
	tempRelate.SetR(Relate.GetR());
	CStringArray aszK;
	tempRelate.FindKey();
	tempRelate.GetK(aszK);

//Buoc 2
	
	i=0;
	while(i<aD.GetSize())
	{
		aszTemp.RemoveAll();
		aszTemp.Append(aD[i].GetX());
		aszTemp.Append(aD[i].GetY());
		tempS = Union(aszTemp);

		if(IsEqual(tempS,Relate.GetR()))
			aD.RemoveAt(i);
		else
			i++;
	}



//Buoc 3
	if(aD.GetSize()==0)
		aDisRelate.Add(tempRelate);
	else
	{
		for(i=0;i<aD.GetSize();i++)
		{
			CString tempS = Union(aD[i].GetX());
			for(j=0;j<aszK.GetSize();j++)
				if(IsIn(aszK[j],tempS))
					break;
			if(j==aszK.GetSize())//khong chua bat cu khoa nao
				break;
		}
		if(i<aD.GetSize())
		{
			CFunc f = aD[i];
			aD.RemoveAt(i);
			aD.InsertAt(0,f);
		}
		else 
		{
			for(i=0;i<aD.GetSize();i++)
			{
				CString tempS = Union(aD[i].GetX());
				for(j=0;j<aD.GetSize();j++)
				{
					if(j!=i)
					{
						CString S=Union(aD[j].GetX());
						if(IsIn(tempS,S))
							break;
					}
				}
				if(j==aD.GetSize())//khong co trong ve phai bat ky phu thuoc ham nao
					break;
			}
			if(i<aD.GetSize())
			{
				CFunc f = aD[i];
				aD.RemoveAt(i);
				aD.InsertAt(0,f);
			}
	
		}
		BOOL NotFound=TRUE;	
		for(i=0;(i<aD.GetSize())&&(NotFound);i++)
		{
			CRelate Relate1,Relate2;

			aszTemp.RemoveAll();
			aszTemp.Append(aD[i].GetX());
			aszTemp.Append(aD[i].GetY());
			tempS = Union(aszTemp);
			Relate1 = tempRelate;
			Relate1.SetR(tempS);

			tempS=Union(aD[i].GetY());
			tempS = Sub(Relate.GetR(),tempS);
			Relate2 = tempRelate;
			Relate2.SetR(tempS);

			DisRelate(Relate1,aDisRelate);
			DisRelate(Relate2,aDisRelate);
			NotFound = FALSE;

		}
		if(NotFound)
			AfxMessageBox("Error ! Can't Disintegrate",MB_OK,(UINT)0);
	}

}

/***********Thuat toan tong hop cai tien(co buoc 7)*************/

//Ham tong hop cai tien
//Vao  Relate:Quan he R
//Ra   aCollectRelate:mang chua cac quan he 
void CRelate::Collect(CRelate Relate, CArray<CRelate, CRelate&>& aCollectRelate)
{
	if(Relate.IsEmpty())
		return;

	CArray<CFunc, CFunc&>  aPTT;//Mang chua phu toi thieu
	CArray<CFunc, CFunc&>  aJ;//Mang chua phu thuoc ham J
	CArray<CUIntArray,CUIntArray&> aGroup;//Mang nhom
	CUIntArray aGJ;//mang chua xem cac phan tu cua aJ thuoc nhom nao
	int i,j,k;

//Buoc 1,2
	Relate.FindPhuTT(aPTT);
	if(aPTT.GetSize() == 0)
	{
		aCollectRelate.Add(Relate);
		return;
	}

//Buoc 3,4.1,4.2
	k=0;
	for(i=0;i<aPTT.GetSize() - 1;i++)
	{
		CUIntArray aTemp;
		if(!FindUInt((UINT)i,aGroup))//Neu khong co trong nhom
		{
			aTemp.Add((UINT)i);
			for(j=i+1;j<aPTT.GetSize();j++)
			{
				if(!FindUInt((UINT)j,aGroup))//Neu khong co trong nhom
				{
					//Neu ve trai bang nhau
					if(IsEqual( Union(aPTT[j].GetX()),Union(aPTT[i].GetX())))
						aTemp.Add(j);
					else
					{
						CString XF1;
						CRelate tempRelate;
						tempRelate.SetR(Relate.GetR());
						tempRelate.SetD(aPTT);
						tempRelate.BagOfX(Union(aPTT[i].GetX()),XF1);
						if (IsIn(Union(aPTT[j].GetX()),XF1))//Neu Ki->Kj
						{
							CString XF2;
							tempRelate.BagOfX(Union(aPTT[j].GetX()),XF2);
							if (IsIn(Union(aPTT[i].GetX()),XF2))//Neu Kj->Ki
							{
								aTemp.Add(j);

								//Dua vao aJ nhung phu thuoc ham chua co
								CString tempS1 = Union(aPTT[i].GetX());
								CString tempS2 = Union(aPTT[j].GetX());
								for(int h=0;h<aJ.GetSize();h++)
								{
									CString S1 = Union(aJ[h].GetX());
									CString S2 = Union(aJ[h].GetY());
									if(IsEqual(S1,tempS1)&&IsEqual(S2,tempS2))
										break;
								}
								if(h==aJ.GetSize())//Neu trong aJ chua co i,j
								{
									CFunc f;
									f.SetX(aPTT[i].GetX());
									f.SetY(aPTT[j].GetX());
									f.SetFlag(TRUE);
									aJ.Add(f);
									aGJ.Add((UINT)k);

									f.SetX(aPTT[j].GetX());
									f.SetY(aPTT[i].GetX());
									aJ.Add(f);
									aGJ.Add((UINT)k);
								}
							}
						}
					}
				}
			}
		}
		//Chinh thuc tao nhom
		if(aTemp.GetSize()>0)
		{	
			aGroup.SetSize(aGroup.GetSize()+1);
			for(int l=0;l<aTemp.GetSize();l++)
				aGroup[k].SetAtGrow(l, aTemp[l]);
			k++;
		}
	}
	if(!FindUInt((UINT)i,aGroup))
	{
		aGroup.SetSize(aGroup.GetSize()+1);
		aGroup[k].SetAtGrow(0,(UINT)i);	
	}
//Buoc 4.3,4.4
	for(i=0;i<aJ.GetSize();i++)
	{
		CString tempS;
		tempS = Union(aJ[i].GetY());
		CStringArray aszC;
		Combine(tempS,"",0,aszC);//Tao to hop
		Sort(aszC);
		tempS = Union(aJ[i].GetX());
		for(j=0;j<aszC.GetSize();j++)
		{
			for(k=0;k<aPTT.GetSize();k++)
			{
				CString S=Union(aPTT[k].GetX());
				if(IsEqual(S,tempS))
				{
					CString szS=Sub(aPTT[k].GetY(),aszC[j]);
					if(szS.IsEmpty())
					{
						int seg,off;
						//Loai bo phu thuoc co trong aJ
						if(FindUInt(k,aGroup,seg,off))
							aGroup[seg].RemoveAt(off);						
					}
					else 
					{
						CFunc f = aPTT[k];
						CStringArray aszTemp;
						aszTemp.Add(szS);
						f.SetY(aszTemp);
						aPTT.SetAt(k,f);
					}
				}
			}
		}
	}
//Buoc 5.1 5.2

	for(i=0;i<aPTT.GetSize();i++)
	{
		int seg,off;
		if(FindUInt(i,aGroup,seg,off))
		{
			CArray<CFunc,CFunc&> aD;
			for(j=0;j<aPTT.GetSize();j++)
				if(j!=i && FindUInt(j,aGroup))
					aD.Add(aPTT[j]);
			for(j=0;j<aJ.GetSize();j++)
				aD.Add(aJ[j]);

			CRelate tempRelate;
			tempRelate.SetR(Relate.GetR());
			tempRelate.SetD(aD);
			CString tempS = Union(aPTT[i].GetX());
			CString S;
			tempRelate.BagOfX(tempS,S);
			tempS = Union(aPTT[i].GetY());
			if(IsIn(tempS,S))
				aGroup[seg].RemoveAt(off);//huy phu thuoc ham bac cau
		}
	}

//Buoc 5.3 : Dua aJ vao nhom
	for(i=0;i<aGJ.GetSize();i++)
	{
		int seg=aGJ[i];
		aGroup[seg].Add(10000+i);
	}
	i=0;
	//Xoa nhung Group[i] rong
	while(i<aGroup.GetSize())
	{
		if(aGroup[i].GetSize()==0)
			aGroup.RemoveAt(i);
		else
			i++;
	}


//Buoc 6
	for(i=0;i<aGroup.GetSize();i++)
	{
		CRelate tempRelate;
		CString tempS;
		CArray<CFunc, CFunc&>  aD;
		for(j=0;j<aGroup[i].GetSize();j++)
		{
			CFunc f;
			int n=aGroup[i][j];
			if(n<10000)//Neu tu tap phu toi thieu
			{
				f=aPTT[n];
				aD.Add(f);
				tempS = Union(tempS,Union(aPTT[n].GetX(),
							aPTT[n].GetY()));
			}
			else//Neu tu tap aJ
			{
				f=aJ[n-10000];
				aD.Add(f);
				tempS = Union(tempS,Union(aJ[n-10000].GetX(),
							aJ[n-10000].GetY()));
			}
		
		}
		tempRelate.SetR(tempS);
		tempRelate.SetD(aD);
		aCollectRelate.Add(tempRelate);
	}

//Buoc 7
	if(Relate.FindKey())
	{
		CStringArray aszK;
		Relate.GetK(aszK);
		CString szK = aszK[0];
		for(i=0;i<aCollectRelate.GetSize();i++)
		{
			CRelate tempRelate = aCollectRelate[i];
			if(tempRelate.FindKey())
			{
				CStringArray aszTempK;
				tempRelate.GetK(aszTempK);
				for(j=0;j<aszTempK.GetSize();j++)
					if(IsEqual(szK,aszTempK[j]))
						break;
				if(j<aszTempK.GetSize())//neu co khoa tap con nhu vay
					break;
			}
			
		}
		if(i==aCollectRelate.GetSize())
		{
			CRelate tempRelate;
			tempRelate.SetR(aszK[0]);
			aCollectRelate.Add(tempRelate);
		}
	}
	
}

/**********Thuat toan bieu dien mot phan ra duoi dang do thi********/
//Vao : phan ra aInput;
//Ra  : tap cac nut aOutput
//      Ma tran ke aGraph
BOOL CRelate::PerformToGraph(CArray<CRelate,CRelate&>& aInput,
					CArray<CRelate,CRelate&>& aOutput,
					CArray<CUIntArray,CUIntArray&>& aGraph)
{
	if(aInput.GetSize()==0)
		return FALSE;
	int i,j,k,n;
	aOutput.RemoveAll();
	for(i=0;i<aGraph.GetSize();i++)
		aGraph[i].RemoveAll();
	aGraph.RemoveAll();

	CRelate Relate(aInput);//day la quan he tong quat
	
	CArray<CRelate,CRelate&> aTemp;
	CUIntArray aHinge;//Nut ban le
	CArray<CFunc,CFunc&> aD;
	Relate.GetD(aD);
	
	
//Buoc 1.1;
	for(i=0;i<aInput.GetSize();i++)
		aTemp.Add(aInput[i]);
	for(i=0;i<aTemp.GetSize();i++)
	{
		aTemp[i].SetD(aD);
		aTemp[i].EssenceRD();
	}


	for(i=0;i<aTemp.GetSize();i++)
	{
		CStringArray aszKi,aszX;
		aTemp[i].FindKey();
		aTemp[i].GetK(aszKi);
		if(!Relate.BagOfX(aszKi,aszX))
			continue;
		
		for(j=0;j<aOutput.GetSize();j++)
		{
			CStringArray aszKj,aszY;
			aOutput[j].FindKey();
			aOutput[j].GetK(aszKj);
			int idx1,idx2;
			if(IsInF(aszKj,aszX,idx1,idx2))//Neu Ki->Kj
			{
				int idx3,idx4;
				if(!Relate.BagOfX(aszKj,aszY))
					continue;
				if(IsInF(aszKi,aszY,idx3,idx4))//Neu Ki<-Kj
					if(idx2==idx3&&idx1==idx4) //Neu Ki<->Kj
						break;
			}
		}
		if(j==aOutput.GetSize())
			aOutput.Add(aTemp[i]);
		else
		{
			CRelate tempRelate;
			tempRelate=(aTemp[i]+aOutput[j]);
			tempRelate.EssenceRD();
			aOutput.SetAt(j,tempRelate);
		}
	}


//Buoc 1.2; Neu Qi chua mot khoa cua Qj thi Qi chua tat ca cac khoa
			//con lai cua Qj
	for(i=0;i<aOutput.GetSize();i++)
		for(j=0;j<aOutput.GetSize();j++)
			if(j!=i)
			{
				CStringArray aszKj;
				aOutput[j].FindKey();
				aOutput[j].GetK(aszKj);
				int idx;
				//Neu Qi co chua mot khoa cua Qj
				if(IsInF(aszKj,aOutput[i].GetR(),idx))
				{
					CString szR,tempS;
					szR=Union(aOutput[i].GetR(),aszKj);

					aOutput[i].SetR(szR);//Qi chua tat ca cac khoa con lai
					aOutput[i].SetD(aD);
					aOutput[i].EssenceRD();
				}
			}

	aTemp.RemoveAll();


//Buoc 3 : Tao nut ban le
	n=aOutput.GetUpperBound();
	for(i=0;i<aOutput.GetSize()-1;i++)
		for(j=i+1;j<aOutput.GetSize();j++)
		{
			CString szR;
			szR=Common(aOutput[i].GetR(),aOutput[j].GetR());
			while(!szR.IsEmpty())
			{
				CRelate tempRelate;
				CStringArray aszK;

				tempRelate.SetD(aD);
				tempRelate.SetR(szR);
				tempRelate.EssenceRD();
				tempRelate.FindKey();
				tempRelate.GetK(aszK);
				
				for(k=0;k<aOutput.GetSize();k++)
				{
					CStringArray aszX;
					aOutput[k].FindKey();
					aOutput[k].GetK(aszX);
					if(IsEqualSpecial(aszX,aszK))
						break;
				}
				if(k==aOutput.GetSize())//Neu khong ton tai
				{
					CRelate tempRelate;
					tempRelate.SetR(Essence(Union(aszK)));
					tempRelate.SetD(aD);
					tempRelate.EssenceRD();

					aTemp.Add(tempRelate);
					n++;
					aHinge.Add(n);
				}
				szR=Sub(szR,aszK);

			}//Cuoi while
		}
	for(i=0;i<aTemp.GetSize();i++)
		aOutput.Add(aTemp[i]);//Them nut ban le vao
	n=aOutput.GetSize();
	for(i=0;i<n;i++)
		aOutput[i].FindKey();//Tim khoa cho tat ca cac quan he

	aGraph.SetSize(n);
	//Khoi dong ma tran ke
	for(i=0;i<n;i++)
	{
		aGraph[i].SetSize(n);
		for(j=0;j<n;j++)
			aGraph[i][j]=0;
	}
	aTemp.RemoveAll();


//Buoc 4 : Tao cung
	for(i=0;i<n;i++)
	{
		CUIntArray aPTH;	
		CUIntArray aPTH_THUA;	
		CUIntArray aLONG_KHOA;	
		CUIntArray aLONG_KHOA_THUA;	

		//Tao PTH,LONG_KHOA
		for(j=0;j<n;j++)
			if(j!=i)
			{
				CString szR;
				CStringArray aszKi,aszKj;
				int idx1,idx2;

				szR=aOutput[i].GetR();
				aOutput[i].GetK(aszKi);

				aOutput[j].GetK(aszKj);
				if(IsInF(aszKj,szR,idx1))
					aPTH.Add(j);//Tao long khoa
				if(IsInF(aszKj,aszKi,idx1,idx2))
					aLONG_KHOA.Add(j);

			}

		//Tao PTH_THUA
		for(j=0;j<aPTH.GetSize();j++)
		{
			for(k=0;k<aPTH.GetSize();k++)
				if(k!=j)
				{
					CStringArray aszKj,aszKk;
					int idx1,idx2;

					aOutput[aPTH[j]].GetK(aszKj);
					aOutput[aPTH[k]].GetK(aszKk);
					if(IsInF(aszKj,aszKk,idx1,idx2))
						break;
				}
			if(k<aPTH.GetSize())//Neu co
				aPTH_THUA.Add(aPTH[j]);
		}
		//Tao LONG_KHOA_THUA
		for(j=0;j<aLONG_KHOA.GetSize();j++)
		{
			for(k=0;k<aLONG_KHOA.GetSize();k++)
				if(k!=j)
				{
					CStringArray aszKj,aszKk;
					int idx1,idx2;

					aOutput[aLONG_KHOA[j]].GetK(aszKj);
					aOutput[aLONG_KHOA[k]].GetK(aszKk);
					if(IsInF(aszKj,aszKk,idx1,idx2))
						break;
				}
			if(k<aLONG_KHOA.GetSize())//Neu co
				aLONG_KHOA_THUA.Add(aPTH[j]);
		}
		CUIntArray aTemp,aTemp1,aTemp2;
		Sub(aPTH,aPTH_THUA,aTemp1);
		Sub(aLONG_KHOA,aLONG_KHOA_THUA,aTemp2);
		Union(aTemp1,aTemp2,aTemp);

		//Tao ma tran ke
		for(j=0;j<aTemp.GetSize();j++)
			aGraph[i].SetAt(aTemp[j],1);
	}

//Buoc 5: Huy nhung nut ban le
	i=0;
	while(i<aHinge.GetSize())
	{
		CStringArray aszK;
		int idx=aHinge[i];
		aOutput[idx].GetK(aszK);
		//Neu co 1 khoa duy nhat va khong co thuoc tinh ngoai khoa
		if(aszK.GetSize()==1&&IsEqual(aOutput[idx].GetR(),aszK))
		{
			for(j=0;j<aGraph[idx].GetSize();j++)
				if(aGraph[idx][j]==1)
					break;
			if(j==aGraph[idx].GetSize())//Neu khong co cung ra
			{
				int count=0,offset;
				for(j=0;j<aGraph.GetSize();j++)
				{
					if(j!=idx&&aGraph[j][idx]==1)
					{
						count++;
						offset=j;
						if(count>1)
							break;
					}
				}
				if(count==1)//Neu chi co duy nhat 1 cung vao
				{
					CRelate tempRelate=aOutput[idx];
					aHinge.RemoveAt(i);//Huy nu ban le
					aOutput.RemoveAt(idx);//Huy nut ban le
					aGraph.RemoveAt(idx);//Xoa dong tuon ung voi nut ban le
					for(j=0;j<aGraph.GetSize();j++)
						aGraph[j].RemoveAt(idx);//Xoa cot tuong ung voi nu ban le
					
					aOutput[offset].GetK(aszK);
					aOutput[offset]+=tempRelate;
					aOutput[offset].EssenceRD();
					//aOutput[offset].FindKey();
					aOutput[offset].SetK(aszK);
					continue;
				}

			}
		}
		i++;
	}

	n=aOutput.GetSize();
//Buoc 6: Min hoa cac quan he nut;

	for(i=0;i<n;i++)
	{
		CStringArray aszKi;
		CString      szKi,szR;
		aOutput[i].GetK(aszKi);szKi=Union(aszKi);
		szR=aOutput[i].GetR();
		for(j=0;j<n;j++)
			if(aGraph[i][j]==1)//Neu co cung noi nut i,j
			{
				CStringArray aszKj;
				CString      szKj,tempS;

				aOutput[j].GetK(aszKj);szKj=Union(aszKj);

				for(k=0;k<szR.GetLength();k++)
					if(szKi.Find(szR[k])==-1&&szKj.Find(szR[k])!=-1)
						tempS+=szR[k];	//Neu szR[k] khong la thuoc tinh khoa 
										//cua Qi nhung lai la thuoc tinh khoa cua Qj

				szR=Sub(szR,tempS);
				aOutput[i].SetR(szR);
				aOutput[i].EssenceD();
				//aOutput[i].FindKey();
				aOutput[i].SetK(aszKi);
			}
	}
//Buoc 7: Tao cung vo huong
	i=0;
	while(i<aOutput.GetSize())
	{
		CStringArray aszK;
		aOutput[i].GetK(aszK);
		if(IsEqual(aOutput[i].GetR(),aszK))//Qi khong co thuoc tinh khong khoa
		{
			for(j=0;j<aGraph.GetSize();j++)
				if(aGraph[j][i]==1)
					break;
			if(j==aGraph.GetSize())//Neu khong co cung vao
			{
				int idx=0,Node[2];

				for(j=0;j<aGraph[i].GetSize();j++)
				{
					if(aGraph[i][j]==1)
					{
						if(idx<2)
							Node[idx]=j;
						idx++;
						if(idx>2)
							break;
					}
				}
				if(idx==2)//Neu chi co 2 cung ra
				{
					CStringArray aszK1,aszK2;
					aOutput[Node[0]].GetK(aszK1);
					aOutput[Node[1]].GetK(aszK2);

					for(k=0;k<aszK.GetSize();k++)
					{
						//Cac bien i,j cuc bo
						for(int i=0;i<aszK1.GetSize();i++)
						{
							for(int j=0;j<aszK2.GetSize();j++)
							{
								CString tempS;
								tempS=Union(aszK1[i],aszK2[j]);
								if(IsEqual(aszK[k],tempS))//Neu KQk=KQi + KQj
									break;
							}
							if(j<aszK2.GetSize())
								break;
						}
						if(i<aszK1.GetSize())
							break;
					}
					if(k<aszK.GetSize())//Neu KQk=KQi + KQj
					{
						//Tao cung vo huong
						aGraph[Node[0]][Node[1]]=1;												
						aGraph[Node[1]][Node[0]]=1;
						//Huy nut i
						aGraph.RemoveAt(i);
						for(j=0;j<aGraph.GetSize();j++)
							aGraph[j].RemoveAt(i);

						aOutput.RemoveAt(i);
						continue;
					}
				}
			}
		}
		i++;
	}
	
	return TRUE;
}
BOOL CheckTrue(CArray<BOOL,BOOL>& a)
{
	int n=a.GetSize();
	if(n==0)
		return FALSE;
	for(int i=0;i<n;i++)
		if(!a[i])
			return FALSE;
	return TRUE;
}

//Vao : tap cac quan he aQ
//Ra  : TRUE neu bao toan thong tin
//      FALSE neu khong bao toan thong tin
BOOL CRelate::Tableau(CArray<CRelate,CRelate&>& aQ)
{
	CArray<CArray<BOOL,BOOL>,CArray<BOOL,BOOL>& > aTableau;
	int i,j,k,m,n,step;
	BOOL Flag;
	CString szR	;
	CArray<CFunc,CFunc&> aD;
	CRelate Q;

	m=aQ.GetSize();
	Q=aQ;//Tao quan he cha
	Q.EssenceRD();
	szR=Q.GetR();
	n=szR.GetLength();

//Khoi tao bang Tableau moi phan tu la TRUE neu co thuoc tinh nguoc lai la FALSE
	aTableau.SetSize(m);
	for(i=0;i<m;i++)
	{
		aTableau[i].SetSize(n);
		CString tmpS=aQ[i].GetR();

		for(j=0;j<n;j++)
		{
			if(tmpS.Find(szR[j])!=-1)
				aTableau[i][j]=TRUE;
			else
				aTableau[i][j]=FALSE;
		}
	}

//Kiem tra
	Q.GetD(aD);
	i=0;
	int count=0;
	while(i<aD.GetSize())
	{
		CString tmpS=Union(aD[i].GetX());
		if(!IsIn(tmpS,szR) || !aD[i].GetFlag())
			aD.RemoveAt(i);//Loai bo nhung phu thuoc da tri hoac khong nam trong Q	
		else
			i++;
	}
	if(aD.GetSize()==0)
		return FALSE;

	step=0;//bien chay cho phu thuoc ham
	Flag=FALSE;
	while(1)
	{
		CUIntArray a;//bang chi muc
		CString tmpS=Union(aD[step].GetX());
		for(k=0;k<tmpS.GetLength();k++)
			a.Add(szR.Find(tmpS[k]));				

		for(i=0;i<m;i++)
		{
			if(CheckTrue(aTableau[i]))
				return TRUE;
			for(j=0;j<m;j++)
			{
				if(j==i)
					continue;
				if(CheckTrue(aTableau[j]))
					return TRUE;
				for(k=0;k<a.GetSize();k++)
				{
					if(!aTableau[i].GetAt(a[k]) || !aTableau[j].GetAt(a[k]))
						break;
				}
				if(k<a.GetSize())
					continue;
				a.RemoveAll();

				tmpS=Union(aD[step].GetY());
				for(k=0;k<tmpS.GetLength();k++)
					a.Add(szR.Find(tmpS[k]));				
	
				for(k=0;k<a.GetSize();k++)
				{
					if(aTableau[i].GetAt(a[k]))
					{
						if(!aTableau[j].GetAt(a[k]))
						{
							aTableau[j].SetAt(a[k],TRUE);
							if(CheckTrue(aTableau[j]))
								return TRUE;
							
							Flag=TRUE;//co thay doi
						}
					}
					else 
					{
						if(aTableau[j].GetAt(a[k]))
						{
							aTableau[i].SetAt(a[k],TRUE);
							if(CheckTrue(aTableau[i]))
								return TRUE;
							Flag=TRUE;//co thay doi
						}
					}
				}
			}
		}
		step++;
		count++;
		if(step==aD.GetSize())//Het 1 chu ki reset lai
		{
			for(i=0;i<aTableau.GetSize();i++)
				if(CheckTrue(aTableau[i]))
					return TRUE;
			if(!Flag)
				return FALSE;
			else
			{
				step=0;
				Flag=FALSE;
			}
		}
	}
	return FALSE;
}

/**************************************************************************************************/
/********** Thuat toan : Tim cac phu thuoc ham co nguy co dan den mau thuan (tuyen tinh) **********/
//Cac method cua CLinearRiskFunc
CLinearRiskFunc::CLinearRiskFunc():CFunc()
{
}

CLinearRiskFunc::~CLinearRiskFunc()
{
	Empty();
}
//Xoa trang 
void CLinearRiskFunc::Empty()
{
	m_aR.RemoveAll();
	m_aRIdx.RemoveAll();
	CFunc::Empty();
}
CLinearRiskFunc::CLinearRiskFunc(CLinearRiskFunc& LinearRiskD)
{
	SetLinearRiskFunc(LinearRiskD);
}
void CLinearRiskFunc::SetLinearRiskFunc(CLinearRiskFunc& LinearRiskD)
{
	LONG n=LinearRiskD.m_aR.GetSize();

	SetFunc(LinearRiskD);
	m_aR.RemoveAll();
	for(LONG i=0; i<n; i++)
		m_aR.Add(LinearRiskD.m_aR.ElementAt(i));

	m_aRIdx.RemoveAll();
	m_aRIdx.Append(LinearRiskD.m_aRIdx);
}
CLinearRiskFunc&  CLinearRiskFunc::operator =  (CLinearRiskFunc& LinearRiskD)
{
	SetLinearRiskFunc(LinearRiskD);
	return *this;
}
void CLinearRiskFunc::Output(CString& szS)
{
	szS.Empty();

	CString szD;
	CFunc::Output(szD);//Xuat phu thuoc ham
	szS += szD + ":";

	LONG n=m_aR.GetSize();
	if(n==0)
		return;
	for(LONG i=0; i<n-1; i++)
	{
		CString szR;
		m_aR.ElementAt(i).Output(szR);//Xuat tung quan he

		szS +="<";
		szS += szR + ">,";
	}
	if(n>0)
	{
		CString szR;
		m_aR.ElementAt(n-1).Output(szR);//Xuat tung quan he

		szS +="<";
		szS += szR + ">";
	}
}
void CLinearRiskFunc::OutputBrief(CString& szS)//xuat phu thuoc ham mau thuan dang ngan gon
{
	szS.Empty();

	CString szD;
	CFunc::Output(szD);//Xuat phu thuoc ham
	szS += szD + ":";

	LONG n=m_aR.GetSize();
	if(n==0)
		return;
	for(LONG i=0; i<n-1; i++)
	{
		CString szR;
		m_aR.ElementAt(i).OutputBrief(szR);//Xuat tung quan he dang ngan gon
		
		CString frontS;
		frontS.Format("R%lu",m_aRIdx[i]+1);
		szS += frontS + "<";
		szS += szR + ">,";
	}
	if(n>0)
	{
		CString szR;
		m_aR.ElementAt(n-1).OutputBrief(szR);//Xuat tung quan he dang ngan gon

		CString frontS;
		frontS.Format("R%lu",m_aRIdx[n-1]+1);
		szS += frontS + "<";
		szS += szR + ">";
	}
}

/***************************************************/

//Cac method cua luoc do quan he CRelateSchema
CRelateSchema::CRelateSchema()
{

}

CRelateSchema::~CRelateSchema()
{
	Empty();
}


//Xoa trang luoc do quan he
void CRelateSchema::Empty()
{
	m_aR.RemoveAll();
	m_aD.RemoveAll();
	m_aLinearRiskD.RemoveAll();
}
void CRelateSchema::OutputaR(CString& szaR)
{
	LONG	n=m_aR.GetSize();
	if(n==0)	return;

	LONG	i;
	szaR.Empty();
	for(i=0; i<n-1; i++)
	{
		CString szR;
		m_aR.ElementAt(i).Output(szR);

		szaR +="<";
		szaR +=szR + ">,";
	}
	if(n>0)
	{
		CString szR;
		m_aR.ElementAt(n-1).Output(szR);

		szaR +="<";
		szaR +=szR + ">";
	}
}
void CRelateSchema::OutputaD(CString& szaD)
{
	LONG	n=m_aD.GetSize();
	if(n==0)	return;

	LONG	i;
	szaD.Empty();

	szaD +="D{";
	for(i=0; i<n-1; i++)
	{
		CString szD;
		m_aD.ElementAt(i).Output(szD);
		szaD +="(";
		szaD +=szD + "),";
	}
	if(n>0)
	{
		CString szD;
		m_aD.ElementAt(n-1).Output(szD);
		szaD +="(";
		szaD +=szD + ")";
	}
	szaD +="}";
}
void CRelateSchema::OutputaLinearRiskD(CString& szaLinearRiskD)
{
	LONG n=m_aLinearRiskD.GetSize();
	if(n==0) 	return;

	szaLinearRiskD.Empty();
	for(LONG i=0; i<n-1; i++)
	{
		CString szLinearRiskD;
		m_aLinearRiskD.ElementAt(i).Output(szLinearRiskD);

		szaLinearRiskD +="(";
		szaLinearRiskD +=szLinearRiskD + "),";
	}
	if(n>0)
	{
		CString szLinearRiskD;
		m_aLinearRiskD.ElementAt(n-1).Output(szLinearRiskD);

		szaLinearRiskD +="(";
		szaLinearRiskD +=szLinearRiskD + ")";
	}
}
void CRelateSchema::OutputaLinearRiskDBrief(CString& szaLinearRiskD)
{
	LONG n=m_aLinearRiskD.GetSize();
	if(n==0) 	return;

	szaLinearRiskD.Empty();
	for(LONG i=0; i<n-1; i++)
	{
		CString szLinearRiskD;
		m_aLinearRiskD.ElementAt(i).OutputBrief(szLinearRiskD);

		szaLinearRiskD +="(";
		szaLinearRiskD +=szLinearRiskD + ")\n";
	}
	if(n>0)
	{
		CString szLinearRiskD;
		m_aLinearRiskD.ElementAt(n-1).OutputBrief(szLinearRiskD);

		szaLinearRiskD +="(";
		szaLinearRiskD +=szLinearRiskD + ")";
	}
}
void CRelateSchema::Output(CString& szS)
{
	szS.Empty();

	CString szaR;
	OutputaR(szaR);
	szS += szaR + "\n";

	CString szaD;
	OutputaD(szaD);
	szS += szaD + "\n";

	CString szaLinearRiskD;
	OutputaLinearRiskD(szaLinearRiskD);
	szS += szaLinearRiskD;
}

//Gom cac phu thuoc ham trong aR 
BOOL CRelateSchema::UpdateD()
{
	LONG m=m_aR.GetSize();
	if(m==0) return FALSE;

	CArray<CFunc, CFunc&>		aTempD;
	LONG i;
	for(i=0; i<m ;i++)
	{
		CArray<CFunc, CFunc&> aD;//tap phu thuoc ham hay phu thuoc da tri
		m_aR.ElementAt(i).GetD(aD);
		int n=aD.GetSize();
		if(n==0)	continue;
		
		for(int j=0; j<n; j++)
			aTempD.Add(aD.ElementAt(j));//lay ra cac phu thuoc ham cua tung quan he de Add vao m_aD
	}
	
	//Gom nhung phu thuoc ham co cung X
	m_aD.RemoveAll();
	m=aTempD.GetSize();
	for(i=0; i<m; i++)
	{
		LONG n=m_aD.GetSize();
		if(n==0)
			m_aD.Add(aTempD[i]);
		else
		{
			LONG j;
			for(j=0; j<n; j++)//Tim nhung phu thuoc ham cua m_aD co cung X voi aTempD[i]
			{
				if(m_aD.ElementAt(j).IsSameX(aTempD[i]))
					break;
			}
			if(j==n)//khong tim thay
				m_aD.Add(aTempD[i]);
			else
			{
				CFunc d=m_aD.ElementAt(j);
				d.UnionY(aTempD[i],FALSE);//khong can kiem tra vi da biet cung X
				m_aD.SetAt(j,d);
			}
		}
	}
	return TRUE;
}

//Ham chuyen chuoi mo ta thanh cac quan he
BOOL CRelateSchema::UpdateR(CString szS)
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
		AfxMessageBox("Error! Data is Empty",MB_OK,0);
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
			AfxMessageBox("Error! Data is nvalid",MB_OK,0);
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
			AfxMessageBox("Error! Data is nvalid",MB_OK,0);
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
		tempRelate.m_name.name="R";
		tempRelate.m_name.idx.Format("%lu",i);
		m_aR.Add(tempRelate);
	}
	return TRUE;
}
BOOL CRelateSchema::Update(CString szS)
{
	if(!UpdateR(szS))
		return FALSE;
	else
		return  UpdateD();
}
BOOL CRelateSchema::FindLinearRiskD()
{
	LONG i,j,k;

	LONG m=m_aD.GetSize();
	m_aLinearRiskD.RemoveAll();
	for(i=0; i<m; i++) //for tung phu thuoc ham cua m_aD
	{
		CArray<CFunc, CFunc&> aChildD;//tap cac phu thuoc ham con aChildD
		m_aD.ElementAt(i).Dis(aChildD);//tach tung phu thuoc ham thanh tap cac phu thuoc ham con aChildD

		LONG n=aChildD.GetSize();//so phan tu cua phu thuoc ham con
		for(j=0; j<n; j++)//for tung phu thuoc ham con
		{
			CUIntArray	tempRIdx;
			LONG		u=m_aR.GetSize();//so quan he trong luoc do
			for(k=0; k<u; k++)//for tung quan he
			{
				if(aChildD.ElementAt(j).IsInRelate(m_aR.ElementAt(k)))//Neu nhu co mot quan he nao do nam trong phu thuoc ham con nay
					tempRIdx.Add(k);//thi add chi muc cua quan he do vao tempRIdx
			}

			LONG P=tempRIdx.GetSize();//p la so quan he chua phu thuoc ham con
			if(P>1)//Neu co 2 quan he tro len chua phu thuoc ham con thi phu thuoc ham con do chinh la phu thuoc ham dan den mau thuan dang tuyen tinh
			{
				LONG count=m_aLinearRiskD.GetSize();
				if(count==0)//Neu nhu m_aLinearRiskD chua co phan tu nao
				{
					CLinearRiskFunc LinearRiskD;
					LinearRiskD.SetFunc(aChildD.ElementAt(j));
					for(LONG p=0; p<P; p++)
					{
						LinearRiskD.m_aR.Add(m_aR.ElementAt(tempRIdx[p]));
						LinearRiskD.m_aRIdx.Add(tempRIdx[p]);
					}

					m_aLinearRiskD.Add(LinearRiskD);//add phu thuoc ham co nguy co nay vao m_aLinearRiskD
				}
				else
				{
					BOOL bTheSame=FALSE;
					if(m_aLinearRiskD[count-1].IsSameX(aChildD.ElementAt(j)))//Neu nhu pth cuoi cung trong m_aLinearRiskD co cung X voi pth con
						bTheSame=TRUE;

					if(bTheSame)
					{
						if(m_aLinearRiskD[count-1].m_aR.GetSize()!=P)
							bTheSame=FALSE;
						else
						{
							for(LONG p=0; p<P; p++)
								if(m_aLinearRiskD[count-1].m_aRIdx[p]!=tempRIdx[p])
								{
									bTheSame=FALSE;
									break;
								}
						}
					}

					if(bTheSame)//Neu pth cuoi cung trong m_aLinearRiskD co cung X va cung so quan he lien quan voi pth con dan den mau thuan thi hop chung lai
					{
						m_aLinearRiskD[count-1].UnionY(aChildD.ElementAt(j),FALSE);//khong can phai kiem tra X
					}
					else//nguoc lai thi add vao binh thuong
					{
						CLinearRiskFunc LinearRiskD;
						LinearRiskD.SetFunc(aChildD.ElementAt(j));
						for(LONG p=0; p<P; p++)
						{
							LinearRiskD.m_aR.Add(m_aR.ElementAt(tempRIdx[p]));
							LinearRiskD.m_aRIdx.Add(tempRIdx[p]);
						}

						m_aLinearRiskD.Add(LinearRiskD);//add phu thuoc ham co nguy co nay vao m_aLinearRiskD
					}
				}

			}
		}

	}
	return TRUE;
}
void CRelateIns::Output(CString& szS)//Xuat ra tat ca
{
	szS.Empty();
	LONG			j;
	LONG			n=m_CheckR.m_szR.GetLength();
	if(n==0)		return;
	CStringArray	aFieldName;
	for(j=0; j<n; j++)
	{
		CString FieldName="A";
		FieldName.SetAt(0,m_CheckR.m_szR.GetAt(j));

		CString rValue;
		if(m_CheckR.m_name.fieldNameMap.Lookup(FieldName,rValue))
		{
			if(!rValue.IsEmpty())
				FieldName=rValue;
		}
		aFieldName.Add(FieldName);

		CString szTemp;
		szTemp.Format("%4s",FieldName);
		szS +=szTemp;
	}
	
	LONG m=m_aDat.GetSize();
	LONG i;
	for(i=0; i<m; i++)
	{
		szS +="\n";
		for(j=0; j<n; j++)
		{
			CString FieldValue;
			m_aDat.ElementAt(i).Lookup(aFieldName.ElementAt(j),FieldValue);

			CString szTemp;
			szTemp.Format("%4s",FieldValue);
			szS +=szTemp;
		}
	}
	
}

//Chieu inRec xuong 1 so thuoc tinh
BOOL CRelateIns::ProjectRec(CString fieldNames, CMapStringToString& inRec, CMapStringToString& outRec)
{
	LONG length=fieldNames.GetLength();
	if(length==0)	return FALSE;

	outRec.RemoveAll();
	for(LONG i=0; i<length; i++)
	{
		CString key="A";
		LPTSTR	rKey=NULL;
		key.SetAt(0,fieldNames.GetAt(i));
		if(!inRec.LookupKey(key,rKey))	continue;

		CString rValue;
		if(!inRec.Lookup(rKey, rValue))	continue;
		outRec.SetAt(rKey,rValue);		
	}
	return TRUE;
}
//Chieu inRec xuong 1 so thuoc tinh
BOOL CRelateIns::ProjectRec(CStringArray afieldNames, CMapStringToString& inRec, CMapStringToString& outRec)
{
	LONG n=afieldNames.GetSize();
	if(n==0)	return FALSE;

	outRec.RemoveAll();
	for(LONG i=0; i<n; i++)
	{
		CString& key=afieldNames.ElementAt(i);
		LPTSTR	rKey=NULL;
		if(!inRec.LookupKey(key,rKey))	continue;

		CString rValue;
		if(!inRec.Lookup(rKey, rValue))	continue;
		outRec.SetAt(rKey,rValue);		
	}
	return TRUE;
}
//Chieu 1 record xuong the hien qua he nay
BOOL CRelateIns::ProjectRec(CMapStringToString& inRec, CMapStringToString& outRec)
{
	CString fieldNames=m_CheckR.GetR();
	return CRelateIns::ProjectRec(fieldNames,inRec,outRec);
}
//Chieu 1 record xuong 1 pth
BOOL CRelateIns::ProjectRec(CFunc& d, CMapStringToString& inRec, CMapStringToString& outRec)
{
	CString fieldNames=d.GetXYStr();
	return CRelateIns::ProjectRec(fieldNames,inRec,outRec);
}
//Chieu 1 record xuong 1 pth theo X(trong X->Y)
BOOL CRelateIns::ProjectRecX(CFunc& d, CMapStringToString& inRec, CMapStringToString& outRec)
{
	CString fieldNames=d.GetXStr();
	return CRelateIns::ProjectRec(fieldNames,inRec,outRec);
}
//Chieu 1 record xuong 1 pth theo Y(trong X->Y)
BOOL CRelateIns::ProjectRecY(CFunc& d, CMapStringToString& inRec, CMapStringToString& outRec)
{
	CString fieldNames=d.GetYStr();
	return CRelateIns::ProjectRec(fieldNames,inRec,outRec);
}
//Kiem tra xem 1 record co nam trong the hien nay khong
LONG CRelateIns::IsRecIn(CArray<CMapStringToString,  CMapStringToString&>& aDat, CMapStringToString& rec, LONG beginIdx)//Tra ve khac -1 neu nhu do la chi muc cua record trong the hien chua rec
{
	LONG n=rec.GetCount();
	if(n==0||beginIdx>=n)	return -1;
	
	LONG m=aDat.GetSize();
	BOOL bFound=FALSE;	
	for(LONG i=beginIdx; i<m; i++)
	{
		CMapStringToString& iRec=aDat.ElementAt(i);
		
		BOOL		bFoundiFlag=FALSE;
		POSITION	pos=rec.GetStartPosition();
		while(pos!=NULL)
		{
			bFoundiFlag=FALSE;

			CString rKey,rValue;
			rec.GetNextAssoc(pos,rKey,rValue);

			CString rmeValue;
			if(iRec.Lookup(rKey, rmeValue))
			{
				if(rValue.Compare(rmeValue)==0)
					bFoundiFlag=TRUE;
			}

			if(!bFoundiFlag)
				break;
		}
		if(bFoundiFlag)
		{
			bFound=TRUE;
			break;
		}
	}
	if(bFound)
		return i;
	return -1;
}
LONG CRelateIns::IsRecIn(CMapStringToString& rec, LONG beginIdx)//Tra ve khac -1 neu nhu do la chi muc cua record trong the hien chua rec
{
	return CRelateIns::IsRecIn(m_aDat,rec,beginIdx);
}
//Hop  record 2 vao record 1 VD : ta co record 1la abcdefg va record 2 la d'e' thi record ket qua la abcd'e'fg
BOOL CRelateIns::UnionRec(CMapStringToString& inRec1, CMapStringToString& inRec2, CMapStringToString& outRec)
{
	POSITION	pos=inRec1.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue1;
		inRec1.GetNextAssoc(pos,rKey,rValue1);

		CString rValue2;
		if(inRec2.Lookup(rKey, rValue2))
			outRec.SetAt(rKey,rValue2);
		else
			outRec.SetAt(rKey,rValue1);
	}
	return TRUE;	
}
BOOL CRelateIns::UnionRec(CMapStringToString& inRec, LONG inIdx, CMapStringToString& outRec)
{
	CMapStringToString& inRec1=m_aDat.ElementAt(inIdx);
	return CRelateIns::UnionRec(inRec1,inRec,outRec);
}
//Them mot record
BOOL CRelateIns::Insert(CMapStringToString& rec)
{
	LONG n=m_aDat.GetSize();
	m_aDat.SetSize(n+1);

	return Edit(rec,n);
/*
	m_aDat.Add(rec);
	return TRUE;
*/
}
//Xoa mot record
BOOL CRelateIns::Del(LONG idx)
{
	m_aDat.RemoveAt(idx);
	return TRUE;
}
//Sua mot record
BOOL CRelateIns::Edit(CMapStringToString& rec, LONG idx)
{
	CMapStringToString& iRec=m_aDat.ElementAt(idx);

	POSITION	pos=rec.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		rec.GetNextAssoc(pos,rKey,rValue);
		iRec.SetAt(rKey,rValue);
	}
	return TRUE;
}
//Tao cau cau lenh o day thanh cau lenh SQL vao the hien quan he
CString CRelateIns::ChangeCommandToSQL(CMapStringToString& rec)
{
	CString SQL;
	return SQL;
}

//NULL duoc xem nhu la khoang trang
//Kiem tra xem record do co thoa man khong chi gioi han trong pth duoc bao
BOOL CRelateIns::TestUpdate(CMapStringToString& rec, LONG idx)//idx chinh la chi muc khong can phai xet record tai do, voi idx=-1 thi xel tat ca record
{
	//Doan nay co the bo
	//Kiem tra cac thuoc tinh khoa khong duoc rong
	CString szK=Union(m_CheckR.m_aszK);
	LONG length=szK.GetLength();
	for(LONG ikey=0; ikey<length; ikey++)
	{
		CString keyname=_T("A");
		keyname.SetAt(0,szK.GetAt(ikey));

		CString rValue;
		if(!rec.Lookup(keyname,rValue))
			return FALSE;
		if(rValue.Compare(_T(" "))==0)
			return FALSE;
	}
	//

	LONG	m=m_CheckR.m_aD.GetSize();
	BOOL	bSatisfy=TRUE;//Xem nhu la thoa man
	for(LONG i=0; i<m; i++)//duyet tat ca cac phu thuoc ham
	{
		CFunc&	d=m_CheckR.m_aD.ElementAt(i);

		CStringArray	aFieldNameX;
		CStringArray	aFieldNameY;
		CMapStringToString	mapX;
		CMapStringToString	mapY;

		//Lay ten cac field ma rec chua
		POSITION		pos=rec.GetStartPosition();
		while(pos!=NULL)
		{
			CString rKey,rValue;
			rec.GetNextAssoc(pos,rKey,rValue);

			if(IsIn(rKey,d.GetX()))
			{
				aFieldNameX.Add(rKey);
				mapX.SetAt(rKey,rValue);
			}
			if(IsIn(rKey,d.GetY()))
			{
				aFieldNameY.Add(rKey);
				mapY.SetAt(rKey,rValue);
			}
		}
		if(aFieldNameX.GetSize()==0)
			continue;

		//Tim dong chua X
		for(LONG j=0; j<m_aDat.GetSize(); )
		{
			LONG idxFound=IsRecIn(mapX,j);
			if(idxFound==-1)//Ne nhu khong co record nao chua X
				break;

			if(j==idx)
			{
				j++;
				continue;
			}
			//Neu nhu co recrd nao chua no

			//Co the bo doan nay
			//Kiem tra trung khoa chinh
			CString szX,szK;
			szX=Union(aFieldNameX);
			szK=Union(m_CheckR.m_aszK);
			if(IsEqual(szX,szK))//Neu nhu trung khoa chinh
				return FALSE;
			//

			if(mapY.GetCount()==0)//Neu Y rong
				break;

			//Neu nhu khong trung khoa chinh va Y khong rong
			CMapStringToString& foundRec=m_aDat.ElementAt(idxFound);

			//So sanh Y cua foundRec voi Y cua rec tuc la Y cua mapY;
			LONG		countY=0;
			POSITION	pos=mapY.GetStartPosition();
			while(pos!=NULL)
			{
				CString rKey,rValue;
				mapY.GetNextAssoc(pos,rKey,rValue);

				CString rfoundValue;
				if(!foundRec.Lookup(rKey,rfoundValue))
					continue;
				if(rfoundValue.Compare(rValue)==0)
					countY++;
			}
			//Trung X phai Trung Y
			if(countY!=mapY.GetCount())
				return FALSE;
			j=idxFound+1;
		}
		continue;
	}
	return bSatisfy;
}
BOOL CRelateSchemaIns::UpdateContrainst()//Ham nay cap nhat rang buoc tim cac rang buoc, vi the phai cap nhat m_RSchema truoc
{
	LONG m=m_RSchema.m_aR.GetSize();
	if(m==0)
		return FALSE;
	for(LONG i=0; i<m; i++)
	{
		CRelate&				R=m_RSchema.m_aR.ElementAt(i);
		CRelateIns				RIns;

		CCheckRelate			CheckR;
		CheckR.SetRelate(R);

		CCheckLinearRiskRelate	CheckLinearRiskR;
		CheckLinearRiskR.SetRelate(R);
		CheckLinearRiskR.m_aCheckLinearRiskD.RemoveAll();
		LONG n=m_RSchema.m_aLinearRiskD.GetSize();
		for(LONG j=0; j<n; j++)//duyet cac phu thuoc ham co nguy co dan den mau thuan
		{
			//Tim xem pth co mau thuan nay co lien quan den Ri khong
			if(FindUInt(i,m_RSchema.m_aLinearRiskD.ElementAt(j).m_aRIdx)!=-1)
			{
				CCheckLinearRiskFunc CheckLinearRiskFunc;
				CheckLinearRiskFunc.SetLinearRiskFunc(m_RSchema.m_aLinearRiskD.ElementAt(j));
				CheckLinearRiskR.m_aCheckLinearRiskD.Add(CheckLinearRiskFunc);
			}
		}
		CheckLinearRiskR.m_bCheck=FALSE;

		RIns.SetRelateIns(CheckR,CheckLinearRiskR);
		m_aDat.Add(RIns);
	}
	Check();
	return TRUE;
}
BOOL CRelateSchemaIns::Update(CString szS)
{
	Empty();
	if(!m_RSchema.Update(szS))
		return FALSE;
	m_RSchema.FindKey();
	m_RSchema.FindLinearRiskD();
	return UpdateContrainst();
}
void CRelateSchemaIns::Output(CString& szS)//Xuat ra tat ca
{
	szS.Empty();

	LONG		n=m_aDat.GetSize();
	if(n==0)	return;
	for(LONG i=0; i<n-1; i++)
	{
		CString szRIns;
		m_aDat.ElementAt(i).Output(szRIns);
		szS +=szRIns+"\n";
	}
	CString szRIns;
	m_aDat.ElementAt(i).Output(szRIns);
	szS +=szRIns;
}
//NULL duoc xem nhu la khoang trang
BOOL CRelateSchemaIns::TestUpdate(LONG idxRIns, LONG idxRec, CRelateSchemaIns& TempSchemaIns, CMapStringToString& rec, CString& recName, CUIntArray& updatingRIdx, BOOL bInsert, CStringArray* paCommand)
{

	CRelateIns& RIns=TempSchemaIns.m_aDat.ElementAt(idxRIns);
	if(bInsert)
	{
		//Neu rec la rong thi xem nhu la thoa man
		if(rec.GetCount()==0)
			return TRUE;
		if(!RIns.TestUpdate(rec))//Kiem tra xem rec co duoc thoa man trong quna he nay hay khong, rec co the co so truong lon hon so field cua quan he
		{
			CString sErr; sErr.Format("Them vao quan he :%lu bi loi",idxRIns);AfxMessageBox(sErr,MB_OK,0);
			return FALSE;
		}
	}
	else//Neu la sua
	{
		CMapStringToString editRec;
		RIns.UnionRec(rec,idxRec,editRec);//hop lai xem nhu rec chung

		//Neu editRec la rong thi xem nhu la thoa man
		if(editRec.GetCount()==0)
			return TRUE;
		if(!RIns.TestUpdate(editRec,idxRec))//Kiem tra xem rec co duoc thoa man trong quna he nay hay khong
		{
			CString sErr; sErr.Format("Sua trong quan he :%lu bi loi",idxRIns);AfxMessageBox(sErr,MB_OK,0);
			return FALSE;
		}
	}
	
	updatingRIdx.Add(idxRIns);//Xem nhu the hien cua quan he nay thoa man chinh no va dang duoc xem xet
	LONG m=RIns.m_CheckLinearRiskR.m_aCheckLinearRiskD.GetSize();//So pt cua tap pth co nguy co trong RIns
	for(LONG i=0; i<m; i++) //for tung pth co nguy co co trong RIns
	{
		CCheckLinearRiskFunc& fRisk=RIns.m_CheckLinearRiskR.m_aCheckLinearRiskD.GetAt(i);
		if(fRisk.IsChecked())//Neu pth co nguy co nay da duoc xem xet thi continue
			continue;
		if(!IsIn(fRisk.GetXYStr(),recName))//Neu nhu fRisk khong nam trong vung cap nhat thi xem nhu thoa man
		{
			fRisk.Check();
			continue;
		}

		LONG n=TempSchemaIns.m_aDat.GetSize();//So the hien quan he co trong the hien luoc do
		for(LONG j=0; j<n; j++)//for tat ca cac the hien quan he trong the hien luoc do
		{
			if(j==idxRIns || TempSchemaIns.m_aDat.ElementAt(j).IsChecked())//Tru the hien quan he RIns ban dau va tru nhung the hien da duoc check
				continue;
			if(FindUInt(j,updatingRIdx)!=-1)//Neu nhu la quan he dang duoc xet o dau do
				continue;
			if(FindUInt(j,fRisk.m_aRIdx )==-1)//Neu fRisk khong lien quan den quan he nay
				continue;

			CMapStringToString XRec;
			if(bInsert)
			{
				CRelateIns::ProjectRecX(fRisk,rec,XRec);
			}
			else
			{
				CRelateIns::ProjectRecX(fRisk,RIns.m_aDat.ElementAt(idxRec),XRec);
			}
			if(XRec.GetCount()==0)//neu vung chieu la rong thi xem nhu la thoa man
				continue;

			LONG idx=TempSchemaIns.m_aDat.ElementAt(j).IsRecIn(XRec);//Neu nhu XRec khong nam trong quan he j tuc la can phai them vao

			BOOL bInsertFlag;
			if(idx==-1)//Day chinh la dan den insert qh khac
			{
				bInsertFlag=TRUE;
			}
			else//Day chinh la dan den edit qh khac
			{
				bInsertFlag=FALSE;
			}
			if(!TestUpdate(j,idx,TempSchemaIns,rec,recName,updatingRIdx,bInsertFlag,paCommand))
				return FALSE;
		}
		fRisk.Check();//fRisk phu thuoc ham nay da duoc thoa
	}
	//RIns thoa man dieu kien pth co nguy co
	RIns.CheckAll();
	if(bInsert)
	{
		RIns.Insert(rec);//Them record vao
		if(paCommand!=NULL)
		{
			CString Command="Add:";
			//Do here
			paCommand->Add(Command);
		}
	}
	else
	{
		RIns.Edit(rec,idxRec);//Sua record
		if(paCommand!=NULL)
		{
			CString Command="Add:";
			//Do here
			paCommand->Add(Command);
		}
	}

	return TRUE;
}
BOOL CRelateSchemaIns::TestInsert(LONG idxRIns, CRelateSchemaIns& TempSchemaIns, CMapStringToString& rec, CStringArray* paCommand)
{
	if(rec.GetCount()==0||idxRIns<0||idxRIns>=m_RSchema.m_aR.GetSize())
		return FALSE;
	if(!IsChecked())
		return FALSE;
	//Khoi tao TempSchemaIns thua ban sao cua chinh the hien
	TempSchemaIns.SetRelateSchemaIns(this);

	//Cac truong cua vung cap nhat
	CString		recName;
	POSITION	pos=rec.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		rec.GetNextAssoc(pos,rKey,rValue);
		recName +=rKey;
	}

	CUIntArray updatingRIdx;//Cung luu tru chi muc cac quan he tam
	if(paCommand!=NULL)
		paCommand->RemoveAll();

	TempSchemaIns.Uncheck();
	BOOL bIsAccept=TestUpdate(idxRIns,-1,TempSchemaIns,rec,recName,updatingRIdx,TRUE,paCommand);
	if(bIsAccept)
	{
		TempSchemaIns.Check();
	}
	return bIsAccept;
}
BOOL CRelateSchemaIns::TestEdit(LONG idxRIns, LONG idxRec, CRelateSchemaIns& TempSchemaIns, CMapStringToString& rec, CStringArray* paCommand)
{
	if(rec.GetCount()==0||idxRIns<0||idxRIns>=m_RSchema.m_aR.GetSize())
		return FALSE;
	if(!IsChecked())
		return FALSE;
	//Khoi tao TempSchemaIns thua ban sao cua chinh the hien
	TempSchemaIns.SetRelateSchemaIns(this);

	//Cac truong cua vung cap nhat
	CString		recName;
	POSITION	pos=rec.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		rec.GetNextAssoc(pos,rKey,rValue);
		recName +=rKey;
	}

	CUIntArray updatingRIdx;//Cung luu tru chi muc cac quan he tam
	if(paCommand!=NULL)
		paCommand->RemoveAll();

	TempSchemaIns.Uncheck();
	BOOL bIsAccept=TestUpdate(idxRIns,idxRec,TempSchemaIns,rec,recName,updatingRIdx,FALSE,paCommand);
	if(bIsAccept)
	{
		TempSchemaIns.Check();
	}
	return bIsAccept;
}
BOOL CRelateSchemaIns::TestInsert(LONG idxRIns, CMapStringToString& rec, CStringArray* paCommand)
{
	if(rec.GetCount()==0||idxRIns<0||idxRIns>=m_RSchema.m_aR.GetSize())
		return FALSE;
	if(!IsChecked())
		return FALSE;
	//Khoi tao TempSchemaIns thua ban sao cua chinh the hien
	CRelateSchemaIns TempSchemaIns;
	TempSchemaIns.SetRelateSchemaIns(this);

	//Cac truong cua vung cap nhat
	CString		recName;
	POSITION	pos=rec.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		rec.GetNextAssoc(pos,rKey,rValue);
		recName +=rKey;
	}

	CUIntArray updatingRIdx;//Cung luu tru chi muc cac quan he tam
	if(paCommand!=NULL)
		paCommand->RemoveAll();

	TempSchemaIns.Uncheck();
	BOOL bIsAccept=TestUpdate(idxRIns,-1,TempSchemaIns,rec,recName,updatingRIdx,TRUE,paCommand);
	return bIsAccept;
}
BOOL CRelateSchemaIns::TestEdit(LONG idxRIns, LONG idxRec, CMapStringToString& rec, CStringArray* paCommand)
{
	if(rec.GetCount()==0||idxRIns<0||idxRIns>=m_RSchema.m_aR.GetSize())
		return FALSE;
	if(!IsChecked())
		return FALSE;
	//Khoi tao TempSchemaIns thua ban sao cua chinh the hien
	CRelateSchemaIns TempSchemaIns;
	TempSchemaIns.SetRelateSchemaIns(this);

	//Cac truong cua vung cap nhat
	CString		recName;
	POSITION	pos=rec.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		rec.GetNextAssoc(pos,rKey,rValue);
		recName +=rKey;
	}

	CUIntArray updatingRIdx;//Cung luu tru chi muc cac quan he tam
	if(paCommand!=NULL)
		paCommand->RemoveAll();

	TempSchemaIns.Uncheck();
	BOOL bIsAccept=TestUpdate(idxRIns,idxRec,TempSchemaIns,rec,recName,updatingRIdx,FALSE,paCommand);
	return bIsAccept;
}
BOOL CRelateSchemaIns::InsertSafe(LONG idxRIns, CMapStringToString& rec)
{
	CStringArray*		paCommand=new CStringArray();
	CRelateSchemaIns	TempSchemaIns;
	BOOL IsAccept=TestInsert(idxRIns,TempSchemaIns,rec,paCommand);
	if(IsAccept)
	{
		//Xu ly cau lenh paCommand;
		delete paCommand;
		this->SetRelateSchemaIns(TempSchemaIns);
		return TRUE;
	}
	delete paCommand;
	return FALSE;
}
BOOL CRelateSchemaIns::EditSafe(LONG idxRIns, LONG idxRec, CMapStringToString& rec)
{
	CStringArray*		paCommand=new CStringArray();
	CRelateSchemaIns	TempSchemaIns;
	BOOL IsAccept=TestEdit(idxRIns,idxRec,TempSchemaIns,rec,paCommand);

	if(IsAccept)
	{
		//Xu ly cau lenh paCommand;
		delete paCommand;
		this->SetRelateSchemaIns(TempSchemaIns);
		return TRUE;
	}
	delete paCommand;
	return FALSE;
}
BOOL CRelateSchemaIns::TestInsert(LONG idxRIns, CRelateSchemaIns& TempSchemaIns, LPCTSTR prec, LPTSTR* pCommand)
{
	CStringArray aszR;
	SplitString(prec,",",aszR);
	LONG n=aszR.GetSize();
	if(n==0) return FALSE;

	CMapStringToString recMap;
	for(LONG i=0; i<n; i++)
	{
		CStringArray aszRi;
		SplitString(aszR.ElementAt(i),":",aszRi);
		if(aszRi.GetSize()>2||aszRi.GetSize()==0)
			return FALSE;
		if(aszRi.GetSize()==1)
			recMap.SetAt(aszRi.ElementAt(0)," ");
		else
			recMap.SetAt(aszRi.ElementAt(0),aszRi.ElementAt(1));
	}
	CStringArray* paCommand=NULL;
	if(pCommand!=NULL)
		paCommand=new CStringArray();

	BOOL bIsAccept=TestInsert(idxRIns,TempSchemaIns, recMap,paCommand);
	if(bIsAccept)
	{
		if(*pCommand!=NULL)
		{
			CString Command;
			StringArrayToString(paCommand,Command,";");
			delete *pCommand;
			*pCommand=new TCHAR[Command.GetLength()+1];
			strcpy(*pCommand,Command);

			delete paCommand;
		}
	}
	else
	{
		if(pCommand!=NULL)
			delete paCommand;
	}
	return bIsAccept;
}
BOOL CRelateSchemaIns::TestEdit(LONG idxRIns, LONG idxRec, CRelateSchemaIns& TempSchemaIns, LPCTSTR prec, LPTSTR* pCommand)
{
	CStringArray aszR;
	SplitString(prec,",",aszR);
	LONG n=aszR.GetSize();
	if(n==0) return FALSE;

	CMapStringToString recMap;
	for(LONG i=0; i<n; i++)
	{
		CStringArray aszRi;
		SplitString(aszR.ElementAt(i),":",aszRi);
		if(aszRi.GetSize()>2||aszRi.GetSize()==0)
			return FALSE;
		if(aszRi.GetSize()==1)
			recMap.SetAt(aszRi.ElementAt(0)," ");
		else
			recMap.SetAt(aszRi.ElementAt(0),aszRi.ElementAt(1));
	}
	CStringArray* paCommand=NULL;
	if(pCommand!=NULL)
		paCommand=new CStringArray();

	BOOL bIsAccept=TestEdit(idxRIns,idxRec,TempSchemaIns, recMap,paCommand);
	if(bIsAccept)
	{
		if(*pCommand!=NULL)
		{
			CString Command;
			StringArrayToString(paCommand,Command,";");
			delete *pCommand;
			*pCommand=new TCHAR[Command.GetLength()+1];
			strcpy(*pCommand,Command);

			delete paCommand;
		}
	}
	else
	{
		if(pCommand!=NULL)
			delete paCommand;
	}
	return bIsAccept;
}
BOOL CRelateSchemaIns::TestInsert(LONG idxRIns, LPCTSTR prec, LPTSTR* pCommand)
{
	CStringArray aszR;
	SplitString(prec,",",aszR);
	LONG n=aszR.GetSize();
	if(n==0) return FALSE;

	CMapStringToString recMap;
	for(LONG i=0; i<n; i++)
	{
		CStringArray aszRi;
		SplitString(aszR.ElementAt(i),":",aszRi);
		if(aszRi.GetSize()>2||aszRi.GetSize()==0)
			return FALSE;
		if(aszRi.GetSize()==1)
			recMap.SetAt(aszRi.ElementAt(0)," ");
		else
			recMap.SetAt(aszRi.ElementAt(0),aszRi.ElementAt(1));
	}
	CStringArray* paCommand=NULL;
	if(pCommand!=NULL)
		paCommand=new CStringArray();

	CRelateSchemaIns	TempSchemaIns;
	BOOL bIsAccept=TestInsert(idxRIns,TempSchemaIns, recMap,paCommand);
	if(bIsAccept)
	{
		if(*pCommand!=NULL)
		{
			CString Command;
			StringArrayToString(paCommand,Command,";");
			delete *pCommand;
			*pCommand=new TCHAR[Command.GetLength()+1];
			strcpy(*pCommand,Command);

			delete paCommand;
		}
	}
	else
	{
		if(pCommand!=NULL)
			delete paCommand;
	}
	return bIsAccept;
}
BOOL CRelateSchemaIns::TestEdit(LONG idxRIns, LONG idxRec, LPCTSTR prec, LPTSTR* pCommand)
{
	CStringArray aszR;
	SplitString(prec,",",aszR);
	LONG n=aszR.GetSize();
	if(n==0) return FALSE;

	CMapStringToString recMap;
	for(LONG i=0; i<n; i++)
	{
		CStringArray aszRi;
		SplitString(aszR.ElementAt(i),":",aszRi);
		if(aszRi.GetSize()>2||aszRi.GetSize()==0)
			return FALSE;
		if(aszRi.GetSize()==1)
			recMap.SetAt(aszRi.ElementAt(0)," ");
		else
			recMap.SetAt(aszRi.ElementAt(0),aszRi.ElementAt(1));
	}
	CStringArray* paCommand=NULL;
	if(pCommand!=NULL)
		paCommand=new CStringArray();

	CRelateSchemaIns	TempSchemaIns;
	BOOL bIsAccept=TestEdit(idxRIns,idxRec,TempSchemaIns, recMap,paCommand);
	if(bIsAccept)
	{
		if(*pCommand!=NULL)
		{
			CString Command;
			StringArrayToString(paCommand,Command,";");
			delete *pCommand;
			*pCommand=new TCHAR[Command.GetLength()+1];
			strcpy(*pCommand,Command);

			delete paCommand;
		}
	}
	else
	{
		if(pCommand!=NULL)
			delete paCommand;
	}
	return bIsAccept;
}
BOOL CRelateSchemaIns::InsertSafe(LONG idxRIns, LPCTSTR prec)
{
	LPTSTR				pCommand=new TCHAR[1];
	CRelateSchemaIns	TempSchemaIns;
	BOOL IsAccept=TestInsert(idxRIns,TempSchemaIns,prec,&pCommand);

	if(IsAccept)
	{
		//Xu ly cau lenh pCommand;
		delete pCommand;
		this->SetRelateSchemaIns(TempSchemaIns);
		return TRUE;
	}
	delete pCommand;
	return FALSE;
}
BOOL CRelateSchemaIns::EditSafe(LONG idxRIns, LONG idxRec, LPCTSTR prec)
{
	LPTSTR				pCommand=new TCHAR[1];
	CRelateSchemaIns	TempSchemaIns;
	BOOL IsAccept=TestEdit(idxRIns,idxRec,TempSchemaIns,prec,&pCommand);
		//this->SetRelateSchemaIns(TempSchemaIns);

	if(IsAccept)
	{
		//Xu ly cau lenh pCommand;
		delete pCommand;
		this->SetRelateSchemaIns(TempSchemaIns);
		return TRUE;
	}
	delete pCommand;
	return FALSE;
}




