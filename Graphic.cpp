// Graphic.cpp: implementation of the CGraphic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "Graphic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CGraphic::CGraphic()
{
	m_bmp[0].LoadBitmap(IDB_WCH);
	m_bmp[1].LoadBitmap(IDB_BLANK);
	m_bmp[2].LoadBitmap(IDB_BCH);
	m_bmp[3].LoadBitmap(IDB_WHC);
	m_bmp[4].LoadBitmap(IDB_BHC);
	m_bmp[5].LoadBitmap(IDB_HTW);
	m_bmp[6].LoadBitmap(IDB_HTB);
	m_bmp[7].LoadBitmap(IDB_BHD);
	m_bmp[8].LoadBitmap(IDB_BBM);
	m_bmp[9].LoadBitmap(IDB_BLF);
	m_bmp[10].LoadBitmap(IDB_BRT);
	m_bmp[11].LoadBitmap(IDB_B2W);
	m_WBBW=true;
	m_ShowHint=true;
	m_ShowData= false;
	m_pGame=NULL;
	m_OpeningBook=NULL;
	m_Maybe = 0;
	m_Rotation =0;
}
CGraphic::~CGraphic()
{
	for(int i=0; i<12; i++)
		m_bmp[i].DeleteObject();
	for(i=0; i<12; i++)
		m_memDC[i].DeleteDC();
}

void CGraphic::Paint(){
	int i, j, x, pos, memDC_Index, HintPt_Index;
	HintPt_Index=0;
	pos=X_UB;
	int loccolor=(m_pGame->m_BlackLoc?5:6);
	for(j=0; j<8; j++) {
		for(i=0; i<8; i++){
			memDC_Index=m_pGame->m_map[pos];
			if(memDC_Index==N_CH){
				if(m_ShowHint){
					if(m_pGame->m_HintPt[HintPt_Index]==pos && HintPt_Index<m_pGame->m_HintCounter){
						HintPt_Index++;
						memDC_Index=loccolor;
					}else 
						memDC_Index=1;
				}else 
					memDC_Index=1;
			}else if(m_pGame->m_CurLoc==pos) 
				memDC_Index=(memDC_Index==B_CH?4:3);
			else	
				memDC_Index=(memDC_Index==B_CH?2:0);
/*
			if(m_WBBW)
				x=i*48+m_GRct.left;
			else
				x=336-i*48+m_GRct.left;
*/
			m_pDC->BitBlt(TransformX(i,j)*48+m_GRct.left, TransformY(i,j)*48+m_GRct.top, 48, 48, &m_memDC[memDC_Index], 0, 0, SRCCOPY);
			if(m_Maybe == pos){
				m_pDC->Ellipse(TransformX(i,j)*48+m_GRct.left+10, TransformY(i,j)*48+m_GRct.top+10, TransformX(i,j)*48+m_GRct.left+38, TransformY(i,j)*48+m_GRct.top+38);
			}
			pos++;
		}
		pos++;
	}
	m_pDC->BitBlt(m_GRct.left-31,m_GRct.top-31,447,31,&m_memDC[7],0,0,SRCCOPY);
	m_pDC->BitBlt(m_GRct.left-31,m_GRct.bottom,447,31,&m_memDC[8],0,0,SRCCOPY);
	m_pDC->BitBlt(m_GRct.left-31,m_GRct.top,32,48*8,&m_memDC[9],0,0,SRCCOPY);
	m_pDC->BitBlt(m_GRct.right+1,m_GRct.top,32,48*8,&m_memDC[10],0,0,SRCCOPY);

	if(m_pGame->m_B2W > 0){
		short *flips = m_pGame->m_FlipHistoryTop;
		short count = *(m_pGame->m_FlipSecTop-1);
		int x= m_pGame->m_B2W-1;
		if(m_pGame->m_BlackLoc) x=3-x;
		while(count--){
			flips--;
			i=GetX_ch(*flips)-1;
			if(!m_WBBW) i=7-i;
			j=GetY_ch(*flips)-1;
			m_pDC->BitBlt(m_GRct.left+i*48, m_GRct.top+j*48, 48, 48, &m_memDC[11], x*48, 0, SRCCOPY);

		}
	}

	if(m_ShowData && m_OpeningBook){
		int len; char buf[10];
		short *trace=m_pGame->GetLocTrace(len);
		FlipSpot output[32];
		len = m_OpeningBook->SearchShow(trace, len, output);
		while(len--){
			sprintf(buf, "%d", output[len].flips);
			i=GetX_ch(output[len].square)-1;
			if(!m_WBBW) i=7-i;
			j=GetY_ch(output[len].square)-1;
			m_pDC->TextOut(m_GRct.left+i*48+24, m_GRct.top+j*48+24, buf);
		}
	}
}

void CGraphic::SetDC(CDC* dc){
	m_pDC = dc;
	for(int i=0; i<12; i++){
		m_memDC[i].CreateCompatibleDC(m_pDC);
		m_memDC[i].SelectObject(&m_bmp[i]);
	}
}

void CGraphic::SetGame(CGame* pg)
{
	m_pGame=pg;
}

void CGraphic::SetRect(RECT &r)
{
	m_GRct=r;
}

void CGraphic::SetOpeningBook(COpeningReader *p)
{
	m_OpeningBook=p;
}

int CGraphic::TransformXY(int x, int y)
{
	if(!m_WBBW){
		if(m_Rotation & 1)
			y=9-y;
		else
			x=9-x;
	}

	switch(m_Rotation){
	case 3:
		return Conv((9-y),(x));//
	case 2:
		return Conv((9-x),(9-y));//
	case 1:
		return Conv(y,9-x);//
	}
	return 	Conv(x,y);//
}

int CGraphic::TransformX(int x, int y)
{
	if(!m_WBBW)x=7-x;

	switch(m_Rotation){
	case 1:
		return (7-y);
	case 2:
		return (7-x);
	case 3:
		return y;
	}
	return 	x;
}

int CGraphic::TransformY(int x, int y)
{
	if(!m_WBBW)x=7-x;

	switch(m_Rotation){
	case 1:
		return (x);//
	case 2:
		return (7-y);//
	case 3:
		return 7-x;
	}
	return 	y;
}

void CGraphic::Rotate(bool d)
{
	if(d)
		(++m_Rotation)%=4;
	else{
		m_Rotation--;
		if(m_Rotation<0) 
			m_Rotation=3;
	}
}
