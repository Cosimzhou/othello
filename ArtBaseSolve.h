// BaseSolve.h: interface for the CBaseSolve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASESOLVE_H__3CDFD339_AD7A_4777_A827_73004C9AC271__INCLUDED_)
#define AFX_BASESOLVE_H__3CDFD339_AD7A_4777_A827_73004C9AC271__INCLUDED_

#include "GameScript.h"
#include "EngineMother.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct Empties{
	int HoleID;
	int Square;
	struct Empties* prev; 
	struct Empties* next; 
}Empties;

class CArtBaseSolve  
{
public:
	void StopSearch();
	CArtBaseSolve();
	virtual ~CArtBaseSolve();

	int BestMove() const;
	int Nodes() const;
	int searchDepth;
	int curDepth;
	void PrepareToSolve(ChessType* board);
	virtual double Solve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove)=0;
	CEngineMother* m_pEng;
protected:
	int count_mobility(ChessType* board, ChessType color) const;
protected:
	int bestMove;
	bool m_bSearchContinue;
	Empties EmHead;
	Empties EmList[0x40];
	unsigned int HoleID[0x5b];
	long nodes;
	const static int worst2best[64];

};

#endif // !defined(AFX_BASESOLVE_H__3CDFD339_AD7A_4777_A827_73004C9AC271__INCLUDED_)
