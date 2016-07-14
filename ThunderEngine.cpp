// ThunderEngine.cpp: implementation of the CThunderEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "ThunderEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThunderEngine::CThunderEngine()
{
	m_hEngine = LoadLibrary("Thunder.dll");
	if(m_hEngine){
		MidSolve = (int(__stdcall*) (int*, int, int, int, int, int*))
					GetProcAddress(m_hEngine, "MidSolve");
		EndSolve = (int (__stdcall *)(int*, int, int, int, int, int, int, int*))
					GetProcAddress(m_hEngine, "EndSolve");
		hash_init= (void (__stdcall *)(int))GetProcAddress(m_hEngine, "hash_init");
		SetTimeOut=(void(__stdcall*)(void))GetProcAddress(m_hEngine, "SetTimeOut");
		hash_init(12);
		__asm add esp, 4
	}
}

CThunderEngine::~CThunderEngine()
{
	if(m_hEngine)
		CloseHandle(m_hEngine);
}

bool CThunderEngine::IsAvalible()
{
	return m_hEngine!=NULL;
}

void CThunderEngine::Search(ChessType *curboard, ChessType col)
{
	int empties, discdiff;
	short bw[2];
	CGameScript::CountChess(curboard, bw);

	Translate(curboard);

	empties=64-bw[0]-bw[1];
	discdiff=bw[0]-bw[1];
	if(col==W_CH) discdiff*=-1;
	
	m_Time =NowTime();

	if(empties<20){
		m_iTmpBestScore = EndSolve((int*)m_board, -640, 640, (col==B_CH? 0: 2), empties, discdiff, m_iTmpBestScore, &m_BestMove);
		__asm add esp, 32
	}else if(empties<22){
		m_iTmpBestScore = EndSolve((int*)m_board, -1, 1, (col==B_CH? 0: 2), empties, discdiff, 0, &m_BestMove);
		__asm add esp, 32
	}else //if(empties<56)
	{
		m_iTmpBestScore = MidSolve((int*)m_board, -10000, 10000, (col==B_CH? 0: 2), 10, &m_BestMove);
		__asm add esp, 24
	}
	m_Time =NowTime()-m_Time;

	m_BestScore = m_iTmpBestScore;
	m_BestMove = Conv(m_BestMove%10, m_BestMove/10);
}

void CThunderEngine::Translate(ChessType *map)
{
	for(int i=0; i<X_UB; i++)m_board[i][0]=m_board[i][YL_UB]=3;
	for(int j=0; j<Y_UB; j++)m_board[0][j]=m_board[XL_UB][j]=3;

	map += PT_A1;
	for(i=1; i<XL_UB; i++){
		for(j=1; j<YL_UB; j++, map++){
			m_board[i][j]=(*map==N_CH? 1: (*map==B_CH? 0: 2));
		}
		map++;
	}
}

void CThunderEngine::SetAI(int ai)
{

}
