#if !defined(AFX_TOOL_H__E3FFA861_1E65_11D4_A3E3_9C18786BBE49__INCLUDED_)
#define AFX_TOOL_H__E3FFA861_1E65_11D4_A3E3_9C18786BBE49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Afxtempl.h>

	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

/********************Cac Ham tien ich***********************/
int  FindUInt(UINT x, CUIntArray& aUInt);
BOOL FindUInt(UINT x, CArray<CUIntArray, CUIntArray&>& aUInt);
BOOL FindUInt(UINT x, CArray<CUIntArray, CUIntArray&>& aUInt,int& seg,int& off);

void Alpha(CString szX,CString& szY);//loai bo nhung ky tu thong phai la ky tu Alphabe
void Alpha(CStringArray& aszS);

void SplitString(CString szS,TCHAR ch, CStringArray& aszR);//Tach chuoi
void SplitString(CString szS,LPCTSTR lpszS, CStringArray& aszR);

void StringArrayToString(CStringArray& aszX, CString& szY, LPCTSTR phancach=NULL);
void StringArrayToString(CStringArray* aszX, CString& szY, LPCTSTR phancach=NULL);

CString  Essence(CString szX);//Loai bo nhung phan tu trung nhau
void     Essence(CStringArray& aszX,CStringArray& aszY);//Loai bo nhung phan tu trung nhau
void     Essence(CUIntArray& aX,CUIntArray& aY);//Loai bo nhung phan tu trung nhau

CString  Common(CString szX, CString szY);//Giao cua 2 tap hop
CString  Common(CStringArray& aszX);//Giao cua cac tap hop
CString  Common(CStringArray& aszX, CStringArray& aszY);//Giao cua cac tap hop
CString  Common(CString szX, CStringArray& aszY);//Giao cua cac tap hop
CString  Common(CStringArray& aszX, CString szY);//Giao cua cac tap hop
void     Common(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ );//Giao cua cac tap hop

CString  Union(CString szX, CString szY);//Hop cua 2 tap hop
CString  Union(CStringArray& aszX);//Hop cua cac tap hop
CString  Union(CStringArray& aszX, CStringArray& aszY);//Giao cua cac tap hop
CString  Union(CString szX, CStringArray& aszY);//Giao cua cac tap hop
CString  Union(CStringArray& aszX, CString szY);//Giao cua cac tap hop
void     Union(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ );//Hop cua cac tap hop

CString Sub(CString szX, CString szY);//Hieu cua 2 tap hop
CString Sub(CStringArray& aszX);//Hieu cua cac tap hop
CString Sub(CStringArray& aszX, CStringArray& aszY);//Hieu cua 2 tap hop
CString Sub(CString szX, CStringArray& aszY);//Hieu cua 2 tap hop
CString Sub(CStringArray& aszX, CString szY);//Hieu cua 2 tap hop
void    Sub(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ );//Hieu cua cac tap hop

//X co chua trong Y hay khong
//Qui uoc X=Y van co the xem X chua trong Y
BOOL IsIn(CString szX, CString szY);//szX co nam trong szY khong
BOOL IsIn(CString szX, CStringArray& aszY,BOOL Flag = TRUE);//Flag=FALSE: chi can szX nam trong 1 trong nhung phan tu cua aszY
BOOL IsIn(CStringArray& aszX, CString szY, BOOL Flag = TRUE);
BOOL IsIn(CStringArray& aszX, CStringArray& aszY,BOOL Flag = TRUE);
BOOL IsInF(CString szX, CStringArray& aszY,int& index);
BOOL IsInF(CStringArray& aszX, CString szY,int& index);
BOOL IsInF(CStringArray& aszX, CStringArray& aszY,int& index1,int& index2);

BOOL IsEqual(CString szX, CString szY);//X co bang Y khong
BOOL IsEqual(CString szX, CStringArray& aszY,BOOL Flag = TRUE);//Flag=FALSE: chi can szX nam trong 1 trong nhung phan tu cua aszY
BOOL IsEqual(CStringArray& aszX, CString szY,BOOL Flag = TRUE);
BOOL IsEqual(CStringArray& aszX, CStringArray& aszY, BOOL Flag = TRUE);
BOOL IsEqualF(CString szX, CStringArray& aszY,int& index1,int& index2);
BOOL IsEqualF(CStringArray& aszX, CString szY,int& index1,int& index2);
BOOL IsEqualF(CStringArray& aszX, CStringArray& aszY,int& index1,int& index2);
BOOL IsEqualSpecial(CStringArray& aszX, CStringArray& aszY);

//Ham tim to hop cua tap szX
void Combine(CString szX, CString s, int k,CStringArray& aszC);
void Combine(CStringArray& aszX, CString s, int k,CStringArray& aszC);

//Ham sap xep
void Sort(CStringArray& aszX);
void Sort(CStringArray* aszX);

//Ham tim co so toi thieu roi nhau
//Vao: aszX
//Ra : aszY
void Minimum(CStringArray& aszX, CStringArray& aszY );

//Ham tao toa do cho cac dinh cua do thi sao cho chung deu nhau
BOOL CreatePoint(int xr, int yr, int R,CArray<CPoint,CPoint&>& aPoint );

class CMapStringToString2: public CMapStringToString
{
	CMapStringToString2():CMapStringToString()
	{
	
	}
	CMapStringToString2(CMapStringToString2& map2):CMapStringToString()
	{
		SetMapStringToString2(map2);
	}
	virtual ~CMapStringToString2()
	{
	
	}
	void SetMapStringToString2(CMapStringToString2& map2)
	{
		RemoveAll();
		POSITION	pos=map2.GetStartPosition();
		while(pos!=NULL)
		{
			CString rKey,rValue;
			map2.GetNextAssoc(pos,rKey,rValue);

			SetAt(rKey,rValue);
		}
	}
	CMapStringToString2&	operator =  (CMapStringToString2& map2)
	{
		SetMapStringToString2(map2);
		return *this;
	}
};
#endif // !defined(AFX_TOOL_H__E3FFA861_1E65_11D4_A3E3_9C18786BBE49__INCLUDED_)
