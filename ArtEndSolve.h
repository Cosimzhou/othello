// EndSolve.h: interface for the CEndSolve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENDSOLVE_H__8EA7AEF5_1439_43F1_A849_5C52DB874FBC__INCLUDED_)
#define AFX_ENDSOLVE_H__8EA7AEF5_1439_43F1_A849_5C52DB874FBC__INCLUDED_

#include "ArtBaseSolve.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArtEndSolve  :public CArtBaseSolve
{
public:
	CArtEndSolve();
	virtual ~CArtEndSolve();

	int FastestFirstEndSolve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove);
	int NoParEndSolve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove);
	int ParEndSolve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove);
	double Solve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove);
private:
	unsigned int RegionParity;
	const static int highestScore;
	const static bool WINNER_GETS_EMPTIES;
};

#endif // !defined(AFX_ENDSOLVE_H__8EA7AEF5_1439_43F1_A849_5C52DB874FBC__INCLUDED_)
