// MTDSolve.cpp: implementation of the CArtMTDSolve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "ArtMTDSolve.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArtMTDSolve::CArtMTDSolve()
{

}

CArtMTDSolve::~CArtMTDSolve()
{

}
/*private int bestMove;
private static string engineName = Settings.Default.EGEngine;
private bool existEGEngine;
private int nodes = 0;

public MTDSolve(){
	try{
		existEGEngine = File.Exists(engineName);
	}catch{
		existEGEngine = false;
	}
}

[DllImport("EGEngine", EntryPoint="AI_GetBestMove", SetLastError=true)]
public static extern int MyDllAI_GetBestMove();
[DllImport("EGEngine", EntryPoint="AI_GetEval", SetLastError=true)]
public static extern int MyDllAI_GetEval();
[DllImport("EGEngine", EntryPoint="AI_GetNodes", SetLastError=true)]
public static extern int MyDllAI_GetNodes();
[DllImport("EGEngine", EntryPoint="SetDepth", SetLastError=true)]
public static extern void MyDllAI_SetDepth(int mid, int wld, int end);
[DllImport("EGEngine", EntryPoint="AI_Slove", SetLastError=true)]
public static extern void MyDllAI_Slove(int[] curboard, int color, int mode, int n_bits);
public void SetDepth(int midDepth, int wldDepth, int endDepth)
{
	if (existEGEngine){
		MyDllAI_SetDepth(midDepth, wldDepth, endDepth);
	}
}*/

double CArtMTDSolve::Solve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove){
//	int curboard[0x5b];
	double num = 0.0;
	nodes = 0;
	bestMove = 0;
//	int num2 = (color == WHITE) ? 1 : 0;
/*	if (existEGEngine){
		for (int i = 0; i < 0x5b; i++){
			curboard[i] = (int) board[i];
		}
		MyDllAI_Slove(curboard, num2, (int) mode, nbits);
		bestMove = MyDllAI_GetBestMove();
	}
	if (((bestMove >= 10) && (bestMove <= 80)) && ((board[bestMove] == ChessType.EMPTY) && Board.AnyFlips(board, bestMove, color, ChessType.BLACK - color))){
		nodes = MyDllAI_GetNodes();
		num = MyDllAI_GetEval();
		if (num <= 64.0)
			return num;
		return 64.0;
	}*/
	if (empties > 20){
		m_pMidSolve->searchDepth = 6;
		m_pMidSolve->PrepareToSolve(board);
		num = m_pMidSolve->Solve(board, -100000000, 100000000, color, empties, discdiff, 1);
		bestMove = m_pMidSolve->BestMove();
		nodes = m_pMidSolve->Nodes();
		return num;
	}
//	m_pEndSolve->searchDepth = 6;

	m_pEndSolve->PrepareToSolve(board);
	if (empties > 16)
		num = m_pEndSolve->Solve(board, -1, 1, color, empties, discdiff, 1);
	else
		num = m_pEndSolve->Solve(board, -64, 64, color, empties, discdiff, 1);
	bestMove = m_pEndSolve->BestMove();
	nodes = m_pEndSolve->Nodes();
	return num;
}

void CArtMTDSolve::SetSolver(CArtEndSolve* ep, CArtMidSolve* mp){
	m_pEndSolve=ep;
	m_pMidSolve=mp;
}
