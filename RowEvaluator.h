// RowEvaluator.h: interface for the CRowEvaluator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROWEVALUATOR_H__C3350064_33EA_4E20_AC72_605AACFC95D4__INCLUDED_)
#define AFX_ROWEVALUATOR_H__C3350064_33EA_4E20_AC72_605AACFC95D4__INCLUDED_

#include "EvaluatorMother.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRowEvaluator  :public CEvaluatorMother
{
public:
	int Evaluate(ChessType* curboard, ChessType col, int empties, bool end);

	CRowEvaluator();
	virtual ~CRowEvaluator();

protected:
	int scan_horizontal_aixes(ChessType *board, ChessType color) const;
	int scan_vertical_aixes(ChessType *board, ChessType color) const;
	int scan_diagonal_RL_aixes(ChessType *board, ChessType color) const;
	int scan_diagonal_LR_aixes(ChessType *board,  ChessType color) const;
	int Score(ChessType *board, ChessType color) const;
};

#endif // !defined(AFX_ROWEVALUATOR_H__C3350064_33EA_4E20_AC72_605AACFC95D4__INCLUDED_)
