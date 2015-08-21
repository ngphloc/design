// Relate.h: interface for the CRelate class.
//
//////////////////////////////////////////////////////////////////////
	  /************************************************
	   * Sinh vien : Nguyen Phuoc Loc    MSSV: 9700454*
	   ************************************************/

#if !defined(AFX_RELATE_H__E9324291_1A09_11D4_A3E3_D1558B86324A__INCLUDED_)
#define AFX_RELATE_H__E9324291_1A09_11D4_A3E3_D1558B86324A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Tool.h"
#include <Afxtempl.h>

#import "c:\Program Files\Common Files\System\ADO\msado20.tlb" \
   no_namespace rename("EOF", "EndOfFile")

#define RECORD	CMapStringToString

//Lop CFunc mo ta phu thuoc ham X->Y 
//hay phu thuoc da tri X->>Y
class CRelate;
class CFunc
{
protected:
	CStringArray	m_aszX;
	CStringArray	m_aszY;
	BOOL			m_bFlag;//TRUE : phu thuoc ham
							//FALSE : phu thuoc da tri
public:
	CFunc();
	CFunc(CFunc& Func);
	virtual ~CFunc();

	CStringArray&	GetX();
	CStringArray&	GetY();
	BOOL			GetFlag();
	CString			GetXStr();
	CString			GetYStr();
	CString			GetXYStr();

	void SetX(CStringArray&  aszX);
	void SetY(CStringArray&  aszY);
	void SetX(CString&  szX);
	void SetY(CString&  szY);
	void SetFlag(BOOL Flag);

	virtual void	SetFunc(CFunc& Func);
	CFunc&	operator =  (CFunc& Func);
	BOOL	operator == (CFunc& Func);
	BOOL	operator != (CFunc& Func);

	virtual void Empty();
	BOOL IsEmpty();
	//Phan ra phu thuoc ham VD: A->BCDE thanh A->B, A->C, A->D, A->E
	BOOL	Dis(CArray<CFunc, CFunc&>& m_aD);

	//Kiem tra phu thuoc ham hien tai co cung X voi phu thuoc ham d khong
	BOOL	IsSameX(CFunc& d);
	//Gom nhom neu nhu cung X, ham nay nguoc voi ham X o tren
	BOOL UnionY(CFunc& d, BOOL bTestX=TRUE);

	//Kiem tra xem phu thuoc ham co nam trong quan he nao do khong
	BOOL IsInRelate(CRelate& R);
	//Xuat phu thuoc ham duoi dang chuoi
	virtual void Output(CString& szS);

}; 

//Moi quan he duoc xem nhu mot doi tuong gom tap thuoc tinh
//va tap phu thuoc ham, phu thuoc da tri
class CRelateName
{
public:
	CString				name;
	CString				idx;
	CMapStringToString	fieldNameMap;
	CRelateName()
	{
		name="R";
		idx="";
	}
	CString FullName()
	{
		return name+idx;
	}
};

class CRelate  
{
protected:
	CRelateName			  m_name;
	CString				  m_szR;//quan he R
	CArray<CFunc, CFunc&> m_aD;//tap phu thuoc ham hay phu thuoc da tri
	CStringArray          m_aszK; //tap cac khoa
public:
	CRelate();
	CRelate(CRelate& Relate);
	CRelate(CArray<CRelate,CRelate&>& aInput);
	virtual ~CRelate();

	virtual void	  SetRelate(CRelate& Relate);
	void	  SetRelate(CArray<CRelate,CRelate&>& aInput);
	CRelate&  operator =  (CRelate& Relate);
	CRelate&  operator =  (CArray<CRelate,CRelate&>& aInput);
	BOOL      operator == (CRelate& Relate);
	BOOL      operator != (CRelate& Relate);
	CRelate&  operator += (CRelate& Relate);
	CRelate	  operator +  (CRelate& Relate);

	CString&				GetR();
	void	GetD(CArray<CFunc, CFunc&>& aD);
	void	GetK(CStringArray& aszK);

	void SetR(CString& R);
	void SetD(CArray<CFunc, CFunc&>& aD);
	void SetK(CStringArray& aszK);
	
	virtual void Empty();
	BOOL IsEmpty();
	virtual void Output(CString& szS);
	virtual void OutputBrief(CString& szS);
	//Ham chuyen chuoi mo ta thanh quan he
	BOOL Update(CString tempR, CString tempD);
	BOOL Update(CString szS);

	void EssenceD();
	void EssenceR();
	void EssenceRD();

	BOOL BagOfX(CString X, CString& XF);//Bao dong
	BOOL BagOfX(CStringArray& aszX, CStringArray& aszY);//Bao dong
	BOOL FindPhuTT(CArray<CFunc, CFunc&>&  aPTT);//Tim phu toi thieu
	BOOL FindKey();//Tim khoa
	BOOL DependOfX(CString X, CStringArray& G);//ham tim tap phu thuoc cua X
/////////////////////////////////////////////////////////////////////////////////////
	//Ham phan ra
	//Vao  Relate:Quan he R
	//Ra   aDisRelate:mang chua cac quan he 
	static void DisRelate(CRelate Relate, CArray<CRelate, CRelate&>& aDisRelate);
				////////////////////////////
	//Ham phan ra cai tien : chon ham phan ra la ham vi pham tieu chuan BCK hay
	//co ve phai khong xuat hien o ve phai cua cac phu thuoc ham khac
	static void DisRelateEnhanced(CRelate Relate, CArray<CRelate, CRelate&>& aDisRelate);
				////////////////////////////
	//Ham tong hop cai tien
	//Vao  Relate:Quan he R
	//Ra   aCollectRelate:mang chua cac quan he 
	static void Collect(CRelate Relate, CArray<CRelate, CRelate&>& aCollectRelate);
				////////////////////////////
	//Thuat toan bieu dien mot phan ra duoi dang do thi
	//Vao : phan ra aInput;
	//Ra  : tap cac nut aOutput
	//      Ma tran ke aGraph

	static BOOL PerformToGraph(CArray<CRelate,CRelate&>& aInput,
						CArray<CRelate,CRelate&>& aOutput,
						CArray<CUIntArray,CUIntArray&>& aGraph);
	//Vao : tap cac quan he aQ
	//      quan he cha Q 
	static BOOL Tableau(CArray<CRelate,CRelate&>& aQ);

	friend class CRelateIns;
	friend class CRelateSchema;
	friend class CRelateSchemaIns;
};


/*************************************************************************************************/

//lop Dai dien cho phu thuoc ham co nguy co mau thuan dang tuyen tinh
class CLinearRiskFunc:public CFunc
{
public:
	CArray<CRelate, CRelate&>	m_aR;	//tap cac quan he co lien quan den phu thuoc ham co nguy co dan den mau thuan dang tuyen tinh
	CUIntArray					m_aRIdx;//tap cac chi muc cua cac quan he co lien quan den phu thuoc ham co nguy co dan den mau thuan dang tuyen tinh

	CLinearRiskFunc();
	CLinearRiskFunc(CLinearRiskFunc& LinearRiskD);
	virtual ~CLinearRiskFunc();
	//Xoa trang 
	virtual void Empty();

	virtual void SetLinearRiskFunc(CLinearRiskFunc& RiskD);
	CLinearRiskFunc&  operator =  (CLinearRiskFunc& Relate);

	virtual void Output(CString& szS);
	void OutputBrief(CString& szS);//dang ngan gon
} ;

//Luoc do co so du lieu: la mot mang ma moi phan tu la 1 Relate
class CRelateSchema
{
public:
	CArray<CRelate,CRelate&>				m_aR;//tap cac quan he
	CArray<CFunc, CFunc&>					m_aD;//tap phu thuoc ham hay phu thuoc da tri tu cac phu thuoc ham(da tri trong m_aR)
	CArray<CLinearRiskFunc, CLinearRiskFunc&>		m_aLinearRiskD;//tap cac phu thuoc ham co nguy co dan den mau thuan dang tuyen tinh

	BOOL UpdateD();
	BOOL UpdateR(CString szS);
public:
	CRelateSchema();
	CRelateSchema(CRelateSchema& RelateSchema)
	{
		SetRelateSchema(RelateSchema);
	}
	virtual ~CRelateSchema();
	void SetRelateSchema(CRelateSchema& RelateSchema)
	{
		LONG m;
		LONG i;

		m=RelateSchema.m_aR.GetSize();
		m_aR.RemoveAll();
		for(i=0; i<m; i++)
			m_aR.Add(RelateSchema.m_aR.ElementAt(i));

		m=RelateSchema.m_aD.GetSize();
		m_aD.RemoveAll();
		for(i=0; i<m; i++)
			m_aD.Add(RelateSchema.m_aD.ElementAt(i));

		m=RelateSchema.m_aLinearRiskD.GetSize();
		m_aLinearRiskD.RemoveAll();
		for(i=0; i<m; i++)
			m_aD.Add(RelateSchema.m_aLinearRiskD.ElementAt(i));
	}
	CRelateSchema&  operator =  (CRelateSchema& RelateSchema)
	{
		SetRelateSchema(RelateSchema);
		return *this;
	}

	//Xoa trang luoc do quan he
	void Empty();
	//Nhung ham xuat
	void OutputaR(CString& szaR);//Xuat cac quan he
	void OutputaD(CString& szaD);//Xuat tat ca phu thuoc ham
	void OutputaLinearRiskD(CString& szaLinearRiskD);//Xuat nhung phu thuoc ham co nguy co dan den mau thuan
	void OutputaLinearRiskDBrief(CString& szaLinearRiskD);//Xuat nhung phu thuoc ham co nguy co dan den mau thuan dang ngan gon
	virtual void Output(CString& szS);//Xuat ra tat ca

	//Ham chuyen chuoi mo ta thanh cac quan he
	BOOL Update(CString szS);

	//Ham tim khoa
	BOOL FindKey()
	{
		LONG n=m_aR.GetSize();
		if(n==0)
			return FALSE;
		for(LONG i=0; i<n; i++)
			m_aR.ElementAt(i).FindKey();
		return TRUE;
	}
	//Ham tim phu thuoc ham co nguy co dan den mau thuan(thuc su ham nay cap nhat m_aLinearRiskD)
	BOOL FindLinearRiskD();
};

class CCheckFunc:public CFunc
{
protected:
	BOOL m_bCheck;
public:
	CCheckFunc():CFunc()
	{
		m_bCheck=FALSE;
	}
	CCheckFunc(CCheckFunc& CheckFunc)
	{
		SetCheckFunc(CheckFunc);
	}
	virtual ~CCheckFunc()
	{
		Empty();
	}
	virtual void Empty()
	{
		m_bCheck=FALSE;
		CFunc::Empty();
	}
	
	void SetCheckFunc(CCheckFunc& CheckFunc)
	{
		CFunc::SetFunc(CheckFunc);
		m_bCheck=CheckFunc.m_bCheck;
	}
	virtual void SetFunc(CFunc& Func)
	{
		CFunc::SetFunc(Func);
		m_bCheck=FALSE;
	}
	CCheckFunc&	operator =  (CCheckFunc& CheckFunc)
	{
		SetCheckFunc(CheckFunc);
		return *this;
	}
	BOOL IsChecked()
	{
		return m_bCheck;
	}
	void Check()
	{
		m_bCheck=TRUE;
	}
	void Uncheck()
	{
		m_bCheck=FALSE;
	}
};
class CCheckLinearRiskFunc:public CLinearRiskFunc
{
protected:
	BOOL m_bCheck;
public:
	CCheckLinearRiskFunc():CLinearRiskFunc()
	{
		m_bCheck=FALSE;
	}
	CCheckLinearRiskFunc(CCheckLinearRiskFunc& CheckLinearRiskFunc)
	{
		SetCheckLinearRiskFunc(CheckLinearRiskFunc);
	}
	virtual ~CCheckLinearRiskFunc()
	{
		Empty();
	}
	virtual void Empty()
	{
		m_bCheck=FALSE;
		CLinearRiskFunc::Empty();
	}
	
	void SetCheckLinearRiskFunc(CCheckLinearRiskFunc& CheckLinearRiskFunc)
	{
		CLinearRiskFunc::SetLinearRiskFunc(CheckLinearRiskFunc);
		m_bCheck=CheckLinearRiskFunc.m_bCheck;
	}
	virtual void SetLinearRiskFunc(CLinearRiskFunc& RiskD)
	{
		CLinearRiskFunc::SetLinearRiskFunc(RiskD);
		m_bCheck=FALSE;
	}
	CCheckLinearRiskFunc&	operator =  (CCheckLinearRiskFunc& CheckLinearRiskFunc)
	{
		SetCheckLinearRiskFunc(CheckLinearRiskFunc);
		return *this;
	}
	BOOL IsChecked()
	{
		return m_bCheck;
	}
	void Check()
	{
		m_bCheck=TRUE;
	}
	void Uncheck()
	{
		m_bCheck=FALSE;
	}
};

//Quan he nay co hop le khong; Khong xet den phu thuoc ham co nguy co dan den mau thuan
class CCheckRelate:public CRelate
{
public:
	CArray<CCheckFunc, CCheckFunc&>	m_aCheckD;
	BOOL							m_bCheck;
public:
	CCheckRelate():CRelate()
	{
		m_bCheck=FALSE;
	}
	CCheckRelate(CCheckRelate& CheckRelate)
	{
		SetCheckRelate(CheckRelate);
	}
	virtual ~CCheckRelate()
	{
		Empty();
	}
	virtual void Empty()
	{
		m_aCheckD.RemoveAll();
		m_bCheck=FALSE;
		CRelate::Empty();
	}

	void SetCheckRelate(CCheckRelate& CheckRelate)
	{
		CRelate::SetRelate(CheckRelate);
		LONG n=CheckRelate.m_aCheckD.GetSize();
		m_aCheckD.RemoveAll();
		for(LONG i=0; i<n; i++)
		{
			m_aCheckD.Add(CheckRelate.m_aCheckD.ElementAt(i));
		}
		m_bCheck=CheckRelate.m_bCheck;

	}
	virtual void SetRelate(CRelate& Relate)
	{
		CRelate::SetRelate(Relate);
		LONG n=m_aD.GetSize();

		m_aCheckD.RemoveAll();
		for(LONG i=0; i<n; i++)
		{
			CCheckFunc d;
			d.SetFunc(m_aD.ElementAt(i));
			m_aCheckD.Add(d);
		}
		m_bCheck=FALSE;
	}
	CCheckRelate&	operator =  (CCheckRelate& CheckRelate)
	{
		SetCheckRelate(CheckRelate);
		return *this;
	}
	BOOL IsChecked()
	{
		return m_bCheck;
	}
	void Check()
	{
		m_bCheck=TRUE;
		CheckAllD();
	}
	void Uncheck()
	{
		m_bCheck=FALSE;
		UncheckAllD();
	}
	void CheckAllD()
	{
		LONG n=m_aCheckD.GetSize();
		for(LONG i=0; i<n; i++)
			m_aCheckD.ElementAt(i).Check();
	}
	void UncheckAllD()
	{
		LONG n=m_aCheckD.GetSize();
		for(LONG i=0; i<n; i++)
			m_aCheckD.ElementAt(i).Uncheck();
	}
	void CheckD(LONG idx)
	{
		LONG n=m_aCheckD.GetSize();
		if(idx<0 || idx>=n)
			return;
		m_aCheckD.ElementAt(idx).Check();
	}
	void UncheckD(LONG idx)
	{
		LONG n=m_aCheckD.GetSize();
		if(idx<0 || idx>=n)
			return;
		m_aCheckD.ElementAt(idx).Uncheck();
	}
};

//Quan he nay co hop le khong; Co xet den phu thuoc ham co nguy co dan den mau thuan
class CCheckLinearRiskRelate:public CRelate
{
public:
	CArray<CCheckLinearRiskFunc, CCheckLinearRiskFunc&>	m_aCheckLinearRiskD;//Tap pth co nguy co duoc bao trong
	BOOL												m_bCheck;
public:
	CCheckLinearRiskRelate():CRelate()
	{
		m_bCheck=FALSE;
	}
	CCheckLinearRiskRelate(CCheckLinearRiskRelate& CheckLinearRiskRelate)
	{
		SetCheckLinearRiskRelate(CheckLinearRiskRelate);
	}
	virtual ~CCheckLinearRiskRelate()
	{
		Empty();
	}
	virtual void Empty()
	{
		m_aCheckLinearRiskD.RemoveAll();
		m_bCheck=FALSE;
		CRelate::Empty();
	}

	void SetCheckLinearRiskRelate(CCheckLinearRiskRelate& CheckLinearRiskRelate)
	{
		SetRelate(CheckLinearRiskRelate);
		LONG n=CheckLinearRiskRelate.m_aCheckLinearRiskD.GetSize();
		m_aCheckLinearRiskD.RemoveAll();
		for(LONG i=0; i<n; i++)
		{
			m_aCheckLinearRiskD.Add(CheckLinearRiskRelate.m_aCheckLinearRiskD.ElementAt(i));
		}
		m_bCheck=CheckLinearRiskRelate.m_bCheck;

	}
	CCheckLinearRiskRelate&	operator =  (CCheckLinearRiskRelate& CheckLinearRiskRelate)
	{
		SetCheckLinearRiskRelate(CheckLinearRiskRelate);
		return *this;
	}
	BOOL IsChecked()
	{
		return m_bCheck;
	}
	void Check()
	{
		m_bCheck=TRUE;
		CheckAllD();
	}
	void Uncheck()
	{
		m_bCheck=FALSE;
		UncheckAllD();
	}
	void CheckAllD()
	{
		LONG n=m_aCheckLinearRiskD.GetSize();
		for(LONG i=0; i<n; i++)
			m_aCheckLinearRiskD.ElementAt(i).Check();
	}
	void UncheckAllD()
	{
		LONG n=m_aCheckLinearRiskD.GetSize();
		for(LONG i=0; i<n; i++)
			m_aCheckLinearRiskD.ElementAt(i).Uncheck();
	}
	void CheckD(LONG idx)
	{
		LONG n=m_aCheckLinearRiskD.GetSize();
		if(idx<0 || idx>=n)
			return;
		m_aCheckLinearRiskD.ElementAt(idx).Check();
	}
	void UncheckD(LONG idx)
	{
		LONG n=m_aCheckLinearRiskD.GetSize();
		if(idx<0 || idx>=n)
			return;
		m_aCheckLinearRiskD.ElementAt(idx).Uncheck();
	}
};

//The hien cua tung quan he
class CRelateIns
{
protected:
	CString ChangeCommandToSQL(CMapStringToString& rec);
public:
	CArray<CMapStringToString,  CMapStringToString&>	m_aDat;
	CCheckRelate										m_CheckR;
	CCheckLinearRiskRelate								m_CheckLinearRiskR;
	BOOL												m_bCheck;
	BOOL												m_bCheckLinearRisk;
	CRelateIns()
	{
		m_bCheck=m_bCheckLinearRisk=FALSE;
	}
	CRelateIns(CRelateIns& RelateIns)
	{
		SetRelateIns(RelateIns);
	}
	virtual ~CRelateIns()
	{
		Empty();
	}
	void SetRelateIns(CRelateIns& RelateIns)
	{
		LONG n=RelateIns.m_aDat.GetSize();
		m_aDat.RemoveAll();
		m_aDat.SetSize(n);

		for(LONG i=0; i<n; i++)
		{
			POSITION	pos=RelateIns.m_aDat.ElementAt(i).GetStartPosition();
			m_aDat.ElementAt(i).RemoveAll();
			while(pos!=NULL)
			{
				CString rKey,rValue;
				RelateIns.m_aDat.ElementAt(i).GetNextAssoc(pos,rKey,rValue);
				m_aDat.ElementAt(i).SetAt(rKey,rValue);
			}
		}
		m_CheckR.SetCheckRelate(RelateIns.m_CheckR);
		m_CheckLinearRiskR.SetCheckLinearRiskRelate(RelateIns.m_CheckLinearRiskR);
		m_bCheck=RelateIns.m_bCheck;
		m_bCheckLinearRisk=RelateIns.m_bCheckLinearRisk;
	}
	void SetRelateIns(CCheckRelate&	CheckR, CCheckLinearRiskRelate&	CheckLinearRiskR)
	{
		m_aDat.RemoveAll();
		m_CheckR.SetCheckRelate(CheckR);
		m_CheckLinearRiskR.SetCheckLinearRiskRelate(CheckLinearRiskR);
		m_bCheck=FALSE;
		m_bCheckLinearRisk=FALSE;
	}
	CRelateIns&	operator =  (CRelateIns& RelateIns)
	{
		SetRelateIns(RelateIns);
		return *this;
	}
	virtual void Output(CString& szS);//Xuat ra tat ca
	
	//Xoa trang
	void Empty()
	{
		m_aDat.RemoveAll();
		m_CheckR.Empty();
		m_CheckLinearRiskR.Empty();
		m_bCheck=m_bCheckLinearRisk=FALSE;
	}
	void Clear()
	{
		m_aDat.RemoveAll();
		CheckAll();
	}

	//The hien cua quan he thoa man phu thuoc ham duoc bao
	void Check()
	{
		m_CheckR.Check();
		m_bCheck=TRUE;
	}
	//The hien cua quan he thoa man phu thuoc ham duoc bao va pth co nguy co dang tuyen tinh
	void CheckAll()
	{
		Check();
		m_CheckLinearRiskR.Check();
		m_bCheckLinearRisk=TRUE;
	}

	//The hien cua quan he khong thoa man phu thuoc ham duoc bao
	void Uncheck()
	{
		m_CheckR.Uncheck();
		m_bCheck=FALSE;
	}
	//The hien cua quan he khong thoa man phu thuoc ham duoc bao va pth co nguy co dang tuyen tinh
	void UncheckAll()
	{
		Uncheck();
		m_CheckLinearRiskR.Uncheck();
		m_bCheckLinearRisk=FALSE;
	}
	BOOL IsChecked()
	{
		return m_bCheck;
	}
	BOOL IsCheckedAll()
	{
		return m_bCheck && m_bCheckLinearRisk;
	}
	

	//Chieu inRec xuong 1 so thuoc tinh
	static BOOL ProjectRec(CString fieldNames, CMapStringToString& inRec, CMapStringToString& outRec);
	//Chieu inRec xuong 1 so thuoc tinh
	static BOOL ProjectRec(CStringArray afieldNames, CMapStringToString& inRec, CMapStringToString& outRec);

	//Chieu 1 record xuong the hien qua he nay
	BOOL ProjectRec(CMapStringToString& inRec, CMapStringToString& outRec);
	//Chieu 1 record xuong 1 pth
	static BOOL ProjectRec(CFunc& d, CMapStringToString& inRec, CMapStringToString& outRec);
	//Chieu 1 record xuong 1 pth theo X(trong X->Y)
	static BOOL ProjectRecX(CFunc& d, CMapStringToString& inRec, CMapStringToString& outRec);
	//Chieu 1 record xuong 1 pth theo Y(trong X->Y)
	static BOOL ProjectRecY(CFunc& d, CMapStringToString& inRec, CMapStringToString& outRec);

	//Kiem tra xem 1 record co nam trong mang the hien khong
	static LONG IsRecIn(CArray<CMapStringToString,  CMapStringToString&>& m_aDat, CMapStringToString& rec, LONG beginIdx=0);//Tra ve khac -1 neu nhu do la chi muc cua record trong the hien chua rec
	//Kiem tra xem 1 record co nam trong the hien nay khong
	LONG IsRecIn(CMapStringToString& rec, LONG beginIdx=0);//Tra ve khac -1 neu nhu do la chi muc cua record trong the hien chua rec

	//Hop  record 2 vao record 1 VD : ta co record 1la abcdefg va record 2 la d'e' thi record ket qua la abcd'e'fg
	static BOOL UnionRec(CMapStringToString& inRec1, CMapStringToString& inRec2, CMapStringToString& outRec);
	//Hop 1 record ben ngoai voi record hien hanh VD : ta co record hien hanh la abcdefg va record ben ngoai la d'e' thi record ket qua la abcd'e'fg
	BOOL UnionRec(CMapStringToString& inRec, LONG inIdx, CMapStringToString& outRec);
	//Them mot record
	BOOL Insert(CMapStringToString& rec);
	//Xoa mot record
	BOOL Del(LONG idx);
	//Sua mot record
	BOOL Edit(CMapStringToString& rec, LONG idx);

	//Kiem tra xem record do co thoa man khong chi gioi han trong pth duoc bao
	BOOL TestUpdate(CMapStringToString& rec, LONG idx=-1);//idx chinh la chi muc khong can phai xet record tai do, voi idx=-1 thi xel tat ca record

	friend class CRelateSchemaIns;
};

//The hien cua luoc do
class CRelateSchemaIns
{
protected:
	//Ham chuyen chuoi mo ta thanh cac quan he va khoi tao luon m_aDat(la rong)
	BOOL UpdateContrainst();//Ham nay cap nhat rang buoc tim cac rang buoc, vi the phai cap nhat m_RSchema truoc
	/*
	Vao :
		idxRIns: chi muc cua The hien quan he can kiem tra, the hien nay 
		idxRec : chi muc cua record(chi dung trong truong hop cap nhat)
		TempSchemaIns: The hien luoc do, the hien nay vua la in vua la out(khi thanh cong chinh la the hien cua toan bo quan he), no duoc khoi tao bang chinh lop nay
		rec: du lieu cua vung can cap nhat
		recName: chuoi ten cuA CMapStringToString rec
		updatingRIdx: Nhung quan he dang duoc sua, day cung la tham so ra, voi ngu nghia la qua he dang duoc capnhat
		bInsert : TRUE cho Them va FALSE cho Sua
	Ra :
		aSQL : tap cac cau len SQL can thi hanh
	Truoc khi goi ham nay phai khoi tao TempSchemaIns chinh la the hien luoc do nay luon,
		updatingRIdx se rong, va goi ham TempSchemaIns.Uncheck()
		Dong thoi bao dam rang m_aDat phai duoc khoi tao tuc ham Update phai duoc goi(co the UpdateDB duoc goi sau) tuc la tap pth co nguy co phai duoc bao trong tung quan he co lien qua
		Sau khi ham nay duoc thuc hien phai goi ham Check()
	*/
	static BOOL TestUpdate(LONG idxRIns, LONG idxRec, CRelateSchemaIns& TempSchemaIns, CMapStringToString& rec, CString& recName, CUIntArray& updatingRIdx, BOOL bInsert, CStringArray* paCommand);

	BOOL TestInsert(LONG idxRIns, CRelateSchemaIns& TempSchemaIns, CMapStringToString& rec, CStringArray* paCommand=NULL);
	BOOL TestEdit(LONG idxRIns, LONG idxRec, CRelateSchemaIns& TempSchemaIns, CMapStringToString& rec, CStringArray* paCommand=NULL);

	BOOL TestInsert(LONG idxRIns, CRelateSchemaIns& TempSchemaIns, LPCTSTR prec, LPTSTR* pCommand=NULL);
	BOOL TestEdit(LONG idxRIns, LONG idxRec, CRelateSchemaIns& TempSchemaIns, LPCTSTR prec, LPTSTR* pCommand=NULL);
public:
	CArray<CRelateIns, CRelateIns&>		m_aDat;
	CRelateSchema						m_RSchema;
	BOOL								m_bCheck;

	CRelateSchemaIns()
	{
		m_bCheck=FALSE;
	}
	CRelateSchemaIns(CRelateSchemaIns& RelateSchemaIns)
	{
		SetRelateSchemaIns(RelateSchemaIns);
	}
	virtual ~CRelateSchemaIns()
	{
	}
	CRelateSchemaIns&	operator =  (CRelateSchemaIns& RelateSchemaIns)
	{
		SetRelateSchemaIns(RelateSchemaIns);
		return *this;
	}
	virtual void Output(CString& szS);//Xuat ra tat ca

	void Check()//Xem nhu luoc do hop ly
	{
		LONG m=m_aDat.GetSize();
		for(LONG i=0; i<m; i++)
			m_aDat.ElementAt(i).CheckAll();
		m_bCheck=TRUE;
	}
	void Uncheck()//Xem nhu luoc do hop ly
	{
		LONG m=m_aDat.GetSize();
		for(LONG i=0; i<m; i++)
			m_aDat.ElementAt(i).UncheckAll();
		m_bCheck=FALSE;
	}
	BOOL IsChecked()
	{
		return m_bCheck;
	}

	//Xoa trang tat ca
	void Empty()
	{
		m_aDat.RemoveAll();
		m_RSchema.Empty();
		m_bCheck=FALSE;
	}
	//Xoa trang du lieu
	void Clear()
	{
		LONG m=m_aDat.GetSize();
		for(LONG i=0; i<m; i++)
			m_aDat.ElementAt(i).Clear();
		m_bCheck=TRUE;
	}

	//Khoi tao the hien cua luoc do tu RelateSchemaIns;
	void SetRelateSchemaIns(CRelateSchemaIns& RelateSchemaIns)
	{
		LONG n=RelateSchemaIns.m_aDat.GetSize();
		m_aDat.RemoveAll();
		for(LONG i=0; i<n; i++)
			m_aDat.Add(RelateSchemaIns.m_aDat.ElementAt(i));

		m_RSchema.SetRelateSchema(RelateSchemaIns.m_RSchema);
		m_bCheck=RelateSchemaIns.m_bCheck;
	}
	void SetRelateSchemaIns(CRelateSchemaIns* pRelateSchemaIns)
	{
		LONG n=pRelateSchemaIns->m_aDat.GetSize();
		m_aDat.RemoveAll();
		for(LONG i=0; i<n; i++)
			m_aDat.Add(pRelateSchemaIns->m_aDat.ElementAt(i));

		m_RSchema.SetRelateSchema(pRelateSchemaIns->m_RSchema);
		m_bCheck=pRelateSchemaIns->m_bCheck;
	}
	BOOL Update(CString szS);
	//BOOL UpdateDDB(ADODB.Connection cn)

	BOOL TestInsert(LONG idxRIns, CMapStringToString& rec, CStringArray* paCommand=NULL);
	BOOL TestEdit(LONG idxRIns, LONG idxRec, CMapStringToString& rec, CStringArray* paCommand=NULL);
	BOOL InsertSafe(LONG idxRIns, CMapStringToString& rec);
	BOOL EditSafe(LONG idxRIns, LONG idxRec, CMapStringToString& rec);

	BOOL TestInsert(LONG idxRIns, LPCTSTR prec, LPTSTR* pCommand=NULL);
	BOOL TestEdit(LONG idxRIns, LONG idxRec, LPCTSTR prec, LPTSTR* pCommand=NULL);
	BOOL InsertSafe(LONG idxRIns, LPCTSTR prec);
	BOOL EditSafe(LONG idxRIns, LONG idxRec, LPCTSTR prec);
};
#endif // !defined(AFX_RELATE_H__E9324291_1A09_11D4_A3E3_D1558B86324A__INCLUDED_)
