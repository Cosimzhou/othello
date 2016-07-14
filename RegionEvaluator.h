// RegionEvaluator.h: interface for the CRegionEvaluator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGIONEVALUATOR_H__B949F4F5_82EA_44C2_B20E_81AD155177A3__INCLUDED_)
#define AFX_REGIONEVALUATOR_H__B949F4F5_82EA_44C2_B20E_81AD155177A3__INCLUDED_

#include "EvaluatorMother.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegionEvaluator  :public CEvaluatorMother
{
public:
	int Evaluate(ChessType* curboard, ChessType col, int empties, bool end);

	CRegionEvaluator();
	virtual ~CRegionEvaluator();

protected:
	__inline int C2Val(ChessType c, ChessType x, ChessType o, int xv, int ov, int m=0) const;
	int Score(ChessType* board, ChessType color, int emptiesNum) const;
private:
	int CountScore(ChessType* board, ChessType color, ChessType oppcolor, int emptiesNum) const;
	int InnerBorderScore(ChessType *board, ChessType color, ChessType oppcolor) const;
	int CenterScore(ChessType* board, ChessType color, ChessType oppcolor) const;
	int BorderScore(ChessType* board, ChessType color, ChessType oppcolor) const;
	int AngleScore(ChessType* board, ChessType color, ChessType oppcolor) const;
};

#endif // !defined(AFX_REGIONEVALUATOR_H__B949F4F5_82EA_44C2_B20E_81AD155177A3__INCLUDED_)
