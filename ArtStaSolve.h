// StaSolve.h: interface for the CArtStaSolve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STASOLVE_H__DB65E8AB_CE31_408E_B753_6B6C18144CA6__INCLUDED_)
#define AFX_STASOLVE_H__DB65E8AB_CE31_408E_B753_6B6C18144CA6__INCLUDED_

#include "ArtBaseSolve.h"
#include "ArtEvaluation.h"
//#include "ArtOpeningReader.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArtStaSolve  : public CArtBaseSolve
{
public:
	CArtStaSolve();
	virtual ~CArtStaSolve();
private:
	CArtEvaluation eval;
	bool existBook;
	bool foundInBook;
//	CArtOpeningReader openingBook;

private:
	int FastestFirstSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove);
	int QuiescenceSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove);
	int RootStaSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove);
public:
	double Solve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove);

};

#endif // !defined(AFX_STASOLVE_H__DB65E8AB_CE31_408E_B753_6B6C18144CA6__INCLUDED_)
