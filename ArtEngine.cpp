// Engine.cpp: implementation of the CArtEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArtEngine.h"
//#include <windows.h> 
//#include "Othello.h"
/*#include "m_EndSolve.h"
#include "m_MidSolve.h"
//#include "MTDSolve.h"
#include "m_StaSolve.h"
*/
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int CArtEngine::MidDepth=6;
int CArtEngine::endDepth=20;
int CArtEngine::emptiesOfStartGame;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArtEngine::CArtEngine()
{
	m_StaSolve.searchDepth = MidDepth;
	m_MidSolve.searchDepth = MidDepth;
	emptiesOfStartGame = 40;
	m_MidSolve.m_pEng=this;
	m_StaSolve.m_pEng=this;
	m_EndSolve.m_pEng=this;
}

CArtEngine::~CArtEngine()
{

}

void CArtEngine::SetAI(int ai){
	switch (ai){
	case 0:
		m_StaSolve.searchDepth = 2;
		m_MidSolve.searchDepth = 2;
		MidDepth = 2;
		return;
	case 1:
		m_StaSolve.searchDepth = 4;
		m_MidSolve.searchDepth = 4;
		MidDepth = 4;
		return;
	case 2:
		m_StaSolve.searchDepth = 6;
		m_MidSolve.searchDepth = 6;
		MidDepth = 6;
		return;
	case 3:
		m_StaSolve.searchDepth = 8;
		m_MidSolve.searchDepth = 8;
		MidDepth = 8;
		return;
	case 4:
		m_StaSolve.searchDepth = 9;
		m_MidSolve.searchDepth = 9;
		MidDepth = 9;
		return;
	case 5:
		m_StaSolve.searchDepth = 10;
		m_MidSolve.searchDepth = 10;
		MidDepth = 10;
		return;
	}
	m_StaSolve.searchDepth = 6;
	m_MidSolve.searchDepth = 6;
	MidDepth = 6;
}



void CArtEngine::Search(ChessType* curboard, ChessType col){
	int empties = 0, num2 = 0, num3 = 0;
	ChessType board[CH_LEN];
	memcpy(board, curboard, CH_LEN*sizeof(ChessType));
	for (int j = 10; j <= 80; j++)
		switch (board[j]){
		case WHITE:
			num2++;
			break;
		case EMPTY:
			empties++;
			break;
		case BLACK:
			num3++;
			break;
		}

	int discdiff = (col == BLACK) ? (num3 - num2) : (num2 - num3);
	double num5 = NowTime();
	if (empties > emptiesOfStartGame){	//40
		m_StaSolve.PrepareToSolve(board);
		m_BestScore = m_StaSolve.Solve(board, -100000000, 100000000, col, empties, discdiff, 1);
		m_BestMove = m_StaSolve.BestMove();
		m_Nodes = m_StaSolve.Nodes();
	}else if (empties > endDepth){	//20
		m_MidSolve.PrepareToSolve(board);
		m_BestScore = m_MidSolve.Solve(board, -100000000, 100000000, col, empties, discdiff, 1);
		m_BestMove = m_MidSolve.BestMove();
		m_Nodes = m_MidSolve.Nodes();
	}else{
		m_EndSolve.PrepareToSolve(board);
		if (empties > 16){
			m_BestScore = m_EndSolve.Solve(board, -1, 1, col, empties, discdiff, 1);
		}else{
			m_BestScore = m_EndSolve.Solve(board, -64, 64, col, empties, discdiff, 1);
		}
		m_BestMove = m_EndSolve.BestMove();
		m_Nodes = m_EndSolve.Nodes();
	}
	if(m_BestMove == 0){
		m_BestMove = CGameScript::FindLocablePt(col, board);
	}
	m_Time = (NowTime() - num5);
}

void CArtEngine::StopSearch()
{
	CEngineMother::StopSearch();
	m_MidSolve.StopSearch();
	m_StaSolve.StopSearch();
	m_EndSolve.StopSearch();
}
