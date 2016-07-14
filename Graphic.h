// Graphic.h: interface for the CGraphic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHIC_H__A70A2A0B_4A5E_4E64_AD0E_D058E3D84F6B__INCLUDED_)
#define AFX_GRAPHIC_H__A70A2A0B_4A5E_4E64_AD0E_D058E3D84F6B__INCLUDED_

#include "Game.h"	// Added by ClassView
#include "OpeningReader.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGraphic  
{
public:
	void Rotate(bool);
	int TransformXY(int, int);
	void SetOpeningBook(COpeningReader *p);
	int m_Maybe;
	bool m_WBBW;
	bool m_ShowHint;
	bool m_ShowData;

	void Paint();
	void SetDC(CDC*);
	void SetRect(RECT& r);
	void SetGame(CGame* pg);

	CGraphic();
	virtual ~CGraphic();

protected:
	__inline int TransformY(int, int);
	__inline int TransformX(int, int);
	int m_Rotation;
	CDC m_memDC[12];
	RECT m_GRct;
	CBitmap m_bmp[12];
	CGame* m_pGame;
	CDC*	m_pDC;
private:
	COpeningReader* m_OpeningBook;
};

#endif // !defined(AFX_GRAPHIC_H__A70A2A0B_4A5E_4E64_AD0E_D058E3D84F6B__INCLUDED_)
