// NankEngine.h: interface for the CNankEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NANKENGINE_H__3F25DDDD_3B3E_4F91_BF78_FE7A63323ADD__INCLUDED_)
#define AFX_NANKENGINE_H__3F25DDDD_3B3E_4F91_BF78_FE7A63323ADD__INCLUDED_

#include "Othello.h"	// Added by ClassView
#include "EngineMother.h"
#include "SevenEngine.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define _TEST

typedef struct {
	int score;
	int preDot;
}NodeBak;



class CNankEngine  :public CEngineMother
{
public:
	void Search(ChessType* board, ChessType col);
	void SetAI(int ai);
	CNankEngine();
	virtual ~CNankEngine();
protected:
	int m_AI;
	int m_CurDepth;
	ChessType m_Color;
	NodeBak m_NodeBak[10];
	ChessType m_Curboard[CH_LEN];
	const static short Index2Best[60];

	int Max_Min_Search(int depth, int alpha, int beta);
	void AIEntry(int maxDepth, int firstDepth, int prenum);

};

#endif // !defined(AFX_NANKENGINE_H__3F25DDDD_3B3E_4F91_BF78_FE7A63323ADD__INCLUDED_)
