	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#include "stdafx.h"
#include "Tool.h"

/********************Cac Ham tien ich***********************/

int  FindUInt(UINT x, CUIntArray& aUInt)
{
	for(int i=0;i<aUInt.GetSize();i++)
		if(x==aUInt[i])
			return i;
	return -1;
}
BOOL FindUInt(UINT x, CArray<CUIntArray, CUIntArray&>& aUInt)
{
	for(int i=0;i<aUInt.GetSize();i++)
		for(int j=0;j<aUInt[i].GetSize();j++)
			if(aUInt[i].GetAt(j) == x)
				return TRUE;
	return FALSE;
}
BOOL FindUInt(UINT x, CArray<CUIntArray, CUIntArray&>& aUInt,int& seg,int& off)
{
	for(int i=0;i<aUInt.GetSize();i++)
		for(int j=0;j<aUInt[i].GetSize();j++)
			if(aUInt[i].GetAt(j) == x)
			{
				seg = i ; off = j;
				return TRUE;
			}
	seg = off = -1;
	return FALSE;

}

void Alpha(CString szX,CString& szY)
{
	szY.Empty();
	for(int i=0;i<szX.GetLength();i++)
		if(isalpha(szX[i]))		szY +=szX[i];
}
void Alpha(CStringArray& aszS)
{
	int i=0;
	while(i<aszS.GetSize())
	{
		CString tempS;
		Alpha(aszS[i],tempS);
		if(tempS.IsEmpty())
			aszS.RemoveAt(i);
		else
		{
			aszS.SetAt(i,tempS);
			i++;
		}
	}

}

void SplitString(CString szS,TCHAR ch, CStringArray& aszR)
{
	aszR.RemoveAll();
	szS.TrimLeft(ch);
	szS.TrimLeft();
	szS.TrimRight(ch);
	szS.TrimRight();
	while(!szS.IsEmpty())
	{
		int index = szS.Find(ch);
		if(index == -1)		
		{
			aszR.Add(szS);
			break;
		}
		CString tempS = szS.Left(index);
		tempS.TrimRight();
		if(!tempS.IsEmpty())
			aszR.Add(tempS);
		szS.TrimLeft((LPCTSTR)tempS);
		szS.TrimLeft(ch);
		szS.TrimLeft();
	}
}
void SplitString(CString szS,LPCTSTR lpszS, CStringArray& aszR)
{
	aszR.RemoveAll();
	szS.TrimLeft(lpszS);
	szS.TrimLeft();
	szS.TrimRight(lpszS);
	szS.TrimRight();
	while(!szS.IsEmpty())
	{
		int index = szS.Find(lpszS);
		if(index == -1)		
		{
			aszR.Add(szS);
			break;
		}
		CString tempS = szS.Left(index);
		tempS.TrimRight();
		if(!tempS.IsEmpty())
			aszR.Add(tempS);
		szS.TrimLeft((LPCTSTR)tempS);
		szS.TrimLeft(lpszS);
		szS.TrimLeft();
	}
}

void StringArrayToString(CStringArray& aszX, CString& szY, LPCTSTR phancach)
{
	szY.Empty();
	if(aszX.GetSize()==0)	return;
	for(int i=0;i<aszX.GetSize()-1;i++)
	{
		szY += aszX[i];
		if(phancach==NULL)
			szY +=',';
		else
			szY +=phancach;
	}
	szY +=aszX[i];

}
void StringArrayToString(CStringArray* aszX, CString& szY, LPCTSTR phancach)
{
	szY.Empty();
	if(aszX->GetSize()==0)	return;
	for(int i=0;i<aszX->GetSize()-1;i++)
	{
		szY += aszX->GetAt(i);
		if(phancach==NULL)
			szY +=',';
		else
			szY +=phancach;
	}
	szY +=aszX->GetAt(i);

}
CString  Essence(CString szX)//Loai bo nhung phan tu trung nhau
{
	CString tempS;
	for(int i=0;i<szX.GetLength();i++)
		if(tempS.Find(szX[i])==-1)//Neu khong tim thay
			tempS +=szX[i];
	return tempS;

}
void Essence(CStringArray& aszX,CStringArray& aszY)//Loai bo nhung phan tu trung nhau
{
	int i,j;
	aszY.RemoveAll();
	for(i=0;i<aszX.GetSize();i++)
	{
		for(j=0;j<aszY.GetSize();j++)
			if(IsEqual(aszY[j],aszX[i]))
				break;
		if(j==aszY.GetSize())//Neu Khong tim thay
			aszY.Add(aszX[i]);
	}
}
void     Essence(CUIntArray& aX,CUIntArray& aY)//loai bo nhung phan tu trung nhau
{
	aY.RemoveAll();
	for(int i=0;i<aX.GetSize();i++)
		if(FindUInt(aX[i],aY)==-1)//Neu khong tim thay
			aY.Add(aX[i]);
}
CString  Common(CString szX, CString szY)//Giao cua 2 tap hop
{
	CString tempS;
	for(int i=0;i<szX.GetLength();i++)
		if(szY.Find(szX[i])!=-1)	tempS +=szX[i];
	tempS=Essence(tempS);
	return tempS;
}
CString  Common(CStringArray& aszX)//Giao cua cac tap hop
{
	CString tempS=aszX[0];
	for(int i=1;i<aszX.GetSize();i++)
		tempS = Common(tempS,aszX[i]);

	return tempS;
}
CString  Common(CStringArray& aszX, CStringArray& aszY)//Giao cua cac tap hop
{
	CString tempS;
	tempS = Common(Common(aszX),Common(aszY));
	return tempS;
}
CString  Common(CString szX, CStringArray& aszY)//Giao cua cac tap hop
{
	CString tempS;
	tempS = Common(szX,Common(aszY));
	return tempS;
}
CString  Common(CStringArray& aszX, CString szY)//Giao cua cac tap hop
{
	CString tempS;
	tempS = Common(Common(aszX),szY);
	return tempS;
}
void     Common(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ )
{
	CUIntArray aTemp;
	for(int i=0;i<aX.GetSize();i++)
		if(FindUInt(aX[i],aY)!=-1)//Neu tim thay
			aTemp.Add(aX[i]);
	Essence(aTemp,aZ);
}
CString  Union(CString szX, CString szY)//Hop cua 2 tap hop
{
	CString tempS;
	tempS = szX + szY;
	tempS = Essence(tempS);
	return tempS;
}
CString  Union(CStringArray& aszX)//Hop cua cac tap hop
{
	CString tempS;
	for(int i=0;i<aszX.GetSize();i++)
		tempS +=aszX[i];
	tempS = Essence(tempS);
	return tempS;
}
CString  Union(CStringArray& aszX, CStringArray& aszY)//Hop cua cac tap hop
{
	CString tempS;
	tempS = Union(Union(aszX),Union(aszY));
	return tempS;
}
CString  Union(CString szX, CStringArray& aszY)//Hop cua cac tap hop
{
	CString tempS;
	tempS = Union(szX,Union(aszY));
	return tempS;
}
CString  Union(CStringArray& aszX, CString szY)//Hop cua cac tap hop
{
	CString tempS;
	tempS = Union(Union(aszX),szY);
	return tempS;
}
void Union(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ )
{
	CUIntArray aTemp;
	aTemp.Append(aX);
	aTemp.Append(aY);
	Essence(aTemp,aZ);
}
CString Sub(CString szX, CString szY)//Hieu cua 2 tap hop
{
	CString tempS;

	for(int i=0;i<szX.GetLength();i++)
		if(szY.Find(szX[i])==-1)	tempS +=szX[i];
	tempS = Essence(tempS);
	return tempS;
		
}
CString Sub(CStringArray& aszX)//Hieu cua cac tap hop
{
	CString tempS=aszX[0];

	for(int i=1;i<aszX.GetSize();i++)
		tempS=Sub(tempS,aszX[i]);
	return tempS;
		
}
CString Sub(CStringArray& aszX, CStringArray& aszY)//Hieu cua cac tap hop
{
	CString tempS;
	tempS = Sub(Union(aszX),Union(aszY));
	return tempS;
}
CString Sub(CString szX, CStringArray& aszY)//Hieu cua cac tap hop
{
	CString tempS;
	tempS = Sub(szX,Union(aszY));
	return tempS;
}
CString Sub(CStringArray& aszX, CString szY)//Hieu cua cac tap hop
{
	CString tempS;
	tempS = Sub(Union(aszX),szY);
	return tempS;
}
void Sub(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ )
{
	CUIntArray aTemp;
	for(int i=0;i<aX.GetSize();i++)
		if(FindUInt(aX[i],aY)==-1)//Neu khong tim thay
			aTemp.Add(aX[i]);
	Essence(aTemp,aZ);
	
}
//X co chua trong Y hay khong
//Qui uoc X=Y van co the xem X chua trong Y
BOOL IsIn(CString szX, CString szY)
{
	if(szX.IsEmpty())	return TRUE;
	for(int i=0;i<szX.GetLength();i++)
		if(szY.Find(szX[i])==-1)	return FALSE;

	return TRUE;
}

BOOL IsIn(CString szX, CStringArray& aszY,BOOL Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszY);
		return (IsIn(szX,tempS));	
	}
	else
	{
		for(int i=0;i<aszY.GetSize();i++)
			if(!IsIn(szX,aszY[i]))	return FALSE;
		return TRUE;
	}
}
BOOL IsIn(CStringArray& aszX, CString szY, BOOL Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszX);
		return (IsIn(tempS,szY));
	}
	else
	{
		for(int i=0;i<aszX.GetSize();i++)
			if(!IsIn(aszX[i],szY))	return FALSE;
		return TRUE;
	}
}
BOOL IsIn(CStringArray& aszX, CStringArray& aszY,BOOL Flag)
{
	if(Flag)
	{
		CString tempX,tempY;
		tempX = Union(aszX);
		tempY = Union(aszY);
		return (IsIn(tempX,tempY));
	}
	else
	{
		for(int i=0;i<aszX.GetSize();i++)
			if(!IsIn(aszX[i],aszY,FALSE))	return FALSE;

		return TRUE;
	}
}
BOOL IsInF(CString szX, CStringArray& aszY,int& index)
{
	for(int i=0;i<aszY.GetSize();i++)
		if(IsIn(szX,aszY[i]))	
		{
			index=i;
			return TRUE;
		}
	return FALSE;
}
BOOL IsInF(CStringArray& aszX, CString szY,int& index)
{
	for(int i=0;i<aszX.GetSize();i++)
		if(IsIn(aszX[i],szY))	
		{
			index=i;
			return TRUE;
		}
	return FALSE;
}
BOOL IsInF(CStringArray& aszX, CStringArray& aszY,int& index1,int& index2)
{
	//index1 : chi so trong aszX
	//index2 : chi so trong aszY
	for(int i=0;i<aszX.GetSize();i++)
		if(IsInF(aszX[i],aszY,index2))	
		{
			index1=i;
			return TRUE;
		}
	return FALSE;
}

BOOL IsEqual(CString szX, CString szY)//X co bang Y khong
{
	return (IsIn(szX,szY) && IsIn(szY,szX));
}
BOOL IsEqual(CString szX, CStringArray& aszY,BOOL Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszY);
		return (IsEqual(szX,tempS));
	}
	else
		return(IsIn(szX,aszY,FALSE)&&IsIn(aszY,szX,FALSE));
}
BOOL IsEqual(CStringArray& aszX, CString szY,BOOL Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszX);
		return (IsEqual(tempS,szY));
	}
	else
		return(IsIn(aszX,szY,FALSE)&&IsIn(szY,aszX,FALSE));
		
}
BOOL IsEqual(CStringArray& aszX, CStringArray& aszY, BOOL Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszX);
		return(IsEqual(tempS,aszY));
	}
	else
		return(IsIn(aszX,aszY,FALSE) && IsIn(aszY,aszX,FALSE));
}
BOOL IsEqualF(CString szX, CStringArray& aszY,int& index1,int& index2)
{
	BOOL ret=(IsInF(szX,aszY,index1)&&IsInF(aszY,szX,index2));
	return ret&&(index1==index2);
}
BOOL IsEqualF(CStringArray& aszX, CString szY,int& index1,int& index2)
{
	BOOL ret=(IsInF(aszX,szY,index1)&&IsInF(szY,aszX,index2));
	return ret&&(index1==index2);
}
BOOL IsEqualF(CStringArray& aszX, CStringArray& aszY,int& index1,int& index2)
{
	int index3,index4,index5,index6;
	BOOL ret=(IsInF(aszX,aszY,index3,index4) && IsInF(aszY,aszX,index5,index6));
	if(ret)
		if(index5==index4&&index3==index6)
		{
			index1=index3;
			index2=index4;
			return TRUE;
		}
	return FALSE;
}
BOOL IsEqualSpecial(CStringArray& aszX, CStringArray& aszY)
{
	int i,j;
	for(i=0;i<aszX.GetSize();i++)
		for(j=0;j<aszY.GetSize();j++)
		{
			CString tempSi=aszX[i];
			CString tempSj=aszY[j];

			if(IsIn(aszX[i],aszY[j])&&IsIn(aszY[j],aszX[i]))	
						return TRUE;
		}
	return FALSE;
}

//Ham tim to hop cua tap szX
void Combine(CString szX, CString s, int k,CStringArray& aszC)
{
	if(szX.GetLength() > 12)
	{
		AfxMessageBox("So to hop qua lon",MB_OK);
		szX = szX.Left(12);
	}

	int i,j;
	CStringArray  aszTemp;
	for(i=k;i<szX.GetLength();i++)
	{
		aszTemp.Add(s + szX[i]);
		aszC.Add(Union(s , szX[i]));
	}
	k++;
	for(j=0;j<aszTemp.GetSize();j++)
		Combine(szX,aszTemp[j],j+k,aszC);
}

void Combine(CStringArray& aszX, CString s, int k,CStringArray& aszC)
{
	if(aszX.GetSize() > 10)
	{
		AfxMessageBox("So to hop qua lon",MB_OK);
		aszX.SetSize(10);
	}

	int i,j;
	CStringArray  aszTemp;
	for(i=k;i<aszX.GetSize();i++)
	{
		aszTemp.Add(s + aszX[i]);
		aszC.Add(Union(s , aszX[i]));
	}
	k++;
	for(j=0;j<aszTemp.GetSize();j++)
		Combine(aszX,aszTemp[j],j+k,aszC);
}
void Sort(CStringArray& aszX)
{
	int i,j;
	CString x;
	for (i=1;i<aszX.GetSize();i++)
	{
		x=aszX[i];j=i;
		while((j>0)&&(x.GetLength()<aszX[j-1].GetLength()))
		{
			aszX[j]=aszX[j-1];
			j--;
		}
		aszX[j]=x;
	}

}
void Sort(CStringArray* aszX)
{
	int i,j;
	CString x;
	for (i=1;i<aszX->GetSize();i++)
	{
		x=aszX->GetAt(i);j=i;
		while((j>0)&&(x.GetLength()<aszX->GetAt(j-1).GetLength()))
		{
			aszX->SetAt(j,aszX->GetAt(j-1));
			j--;
		}
		aszX->SetAt(j,x);
	}

}

//Ham tim co so toi thieu roi nhau
//Vao: aszX
//Ra : aszY
void Minimum(CStringArray& aszX, CStringArray& aszY )
{
	aszY.RemoveAll();
	CStringArray aszTemp;
	int i;
	aszTemp.Append(aszX);
	while(aszTemp.GetSize())
	{
		CString tempS1,tempS2,S1,S2,S3;
		tempS1 = aszTemp[0];
		aszTemp.RemoveAt(0);

		for(i=0;i<aszTemp.GetSize();i++)
		{
			S1 = Common(tempS1,aszTemp[i]);
			if(!S1.IsEmpty())
				break;
		}
		if(i==aszTemp.GetSize())//Neu X,Y khong co thuoc tinh chung
		{
			if(!tempS1.IsEmpty())
				aszY.Add(tempS1);
		}
		else
		{
			tempS2 = aszTemp[i];
			aszTemp.RemoveAt(i);

			if(!S1.IsEmpty())
				aszTemp.Add(S1);
			S2 = Sub(tempS1,tempS2);
			if((!S2.IsEmpty())&&(S2 != S1))	
				aszTemp.Add(S2);
			S3 = Sub(tempS2,tempS1);
			if((!S3.IsEmpty())&&(S3 != S1)&&(S3 != S2))	
				aszTemp.Add(S3);

		}
	}
}
BOOL CreatePoint(int xr, int yr, int R,CArray<CPoint,CPoint&>& aPoint )
{

	if(R==0) return FALSE;
	aPoint.RemoveAll();

	int x=0,y=R;
	int p;
	int d1,d2;
	int i,n;
	CPoint point;
	CSize  size;
	CArray<CSize,CSize&> aTemp; 

	p=1-R;
	d1=2*x+3;
	d2=2*(x-y)+5;

	size.cx=x;
	size.cy=y;
	aTemp.Add(size);


	while (x<=y)
	{
		if(p<0)
		{
			p+=d1;
			d2+=2;
		}
		else
		{
			p+=d2;
			y--;
			d2+=4;
		}
		x++;
		d1+=2;
		size.cx=x;
		size.cy=y;
		aTemp.Add(size);
	}

	n=aTemp.GetSize();
	if(n==0)
		return FALSE;
	for(i=0;i<n;i++)//thu 1
	{
		point.x=xr+aTemp[i].cx;
		point.y=yr-aTemp[i].cy;
		aPoint.Add(point);
	}
	for(i=n-3;i>=0;i--) //thu2 
	{
		point.x=xr+aTemp[i].cy;
		point.y=yr-aTemp[i].cx;
		aPoint.Add(point);
	}
		
	for(i=1;i<n-1;i++)//thu 3 
	{
		point.x=xr+aTemp[i].cy;
		point.y=yr+aTemp[i].cx;
		aPoint.Add(point);
	}

	for(i=n-2;i>=1;i--)//thu 4
	{
		point.x=yr+aTemp[i].cx;
		point.y=xr+aTemp[i].cy;
		aPoint.Add(point);
	}
	for(i=0;i<n-1;i++)//thu 5
	{
		point.x=xr-aTemp[i].cx;
		point.y=yr+aTemp[i].cy;
		aPoint.Add(point);
	}
	for(i=n-2;i>=1;i--) //thu 6
	{
		point.x=xr-aTemp[i].cy;
		point.y=yr+aTemp[i].cx;
		aPoint.Add(point);
	}
	for(i=0;i<n-1;i++) //thu 7
	{
		point.x=xr-aTemp[i].cy;
		point.y=yr-aTemp[i].cx;
		aPoint.Add(point);
	}

	for(i=n-2;i>=1;i--)//thu 8
	{
		point.x=xr-aTemp[i].cx;
		point.y=yr-aTemp[i].cy;
		aPoint.Add(point);
	}
		
	return TRUE;
}