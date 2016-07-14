// MidSolve.h: interface for the CArtMidSolve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDSOLVE_H__0DD94358_BD8A_4A4A_BCDE_7012A15D9557__INCLUDED_)
#define AFX_MIDSOLVE_H__0DD94358_BD8A_4A4A_BCDE_7012A15D9557__INCLUDED_

#include "ArtBaseSolve.h"
#include "ArtEvaluation.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArtMidSolve  :public CArtBaseSolve
{
public:
	CArtMidSolve();
	virtual ~CArtMidSolve();

private:
	CArtEvaluation eval;
	const static int MidBetterScore;

private:
	int FastestFirstSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove);
	int QuiescenceSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove);
	int RootMidSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove);
public:
	double Solve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove);

};

#endif // !defined(AFX_MIDSOLVE_H__0DD94358_BD8A_4A4A_BCDE_7012A15D9557__INCLUDED_)
