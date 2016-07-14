// Evaluation.h: interface for the CArtEvaluation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVALUATION_H__0AAC607E_41F2_46DA_8EE9_47F95F0B0A46__INCLUDED_)
#define AFX_EVALUATION_H__0AAC607E_41F2_46DA_8EE9_47F95F0B0A46__INCLUDED_

#include "Othello.h"
#include "ArtBaseSolve.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define BLACK	2
//#define EMPTY	1
//#define WHITE	0
#define IND_MYDISC		0
#define IND_OPDISC		1
#define IND_MYMOB		2
#define IND_OPMOB		3
#define IND_MYPOTMOB	4
#define IND_OPPOTMOB	5
#define IND_MYSTAB		6
#define IND_OPSTAB		7
#define IND_UNSTAB		8
#define IND_KEYNO		9
#define IND_NUM			10
#define midBoardLength	32
#define midGameLength	49
#define lineStateNUM	D3_8
#define D3_8			6561
#define SUM_D1_D7		3780	//		(D3_8-1)/2
#define D3_7			2187
#define D3_6			729
#define D3_5			243
#define D3_4			81
#define D3_3			27
#define D3_2			9
#define D3_1			3
#define D3_0			1
#define	EMPTY_IN_TEMPLATE	1

class CArtEvaluation  
{
public:
	CArtEvaluation();
	virtual ~CArtEvaluation();
private:
	static int score_edge[lineStateNUM][midGameLength];
	const static int midBoard[midBoardLength];
	const static int weight_train[midGameLength][IND_NUM];
private:
	void Initial();
	static bool edge_IsStab(int* edge, int sq, int color);
	int get_score_edge(int* edge, int emptiesIndex, int color);
	int get_score_edge_all(ChessType* board, ChessType color, int empties);
	static int getDeltaKeyano(ChessType* board, ChessType color, ChessType oppcolor);
	static int getUnStab(ChessType* board, ChessType color);
//	static int getUnStab_Start(ChessType* board, ChessType color);
public:
	void InitRecursion(int*edge, int depth);
	int MidEval2(ChessType* board, ChessType color, ChessType oppcolor, int empties, Empties* EmHead);
	int StaEval2(ChessType* board, ChessType color, ChessType oppcolor, int empties, Empties* EmHead);
};

#endif // !defined(AFX_EVALUATION_H__0AAC607E_41F2_46DA_8EE9_47F95F0B0A46__INCLUDED_)
