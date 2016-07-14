// BasicEngine.cpp: implementation of the CBasicEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "BasicEngine.h"
//#include "GameScript.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int CBasicEngine::Eval_map[CH_LEN]={
-INF,	-INF,	-INF,	-INF,	-INF,	-INF,	-INF,	-INF,	-INF,
-INF,	0xff,	-128,	200,	100,	100,	200,	-128,	0xff,
-INF,	-128,	-255,	-50,	0x0,	0x0,	-50,	-255,	-128,
-INF,	200,	-50,	150,	 50,	 50,	150,	-50,	200,

-INF,	100,	0x0,	 50,	-INF,	-INF,	 50,	0x0,	100,
-INF,	100,	0x0,	 50,	-INF,	-INF,	 50,	0x0,	100,

-INF,	200,	-50,	150,	 50,	 50,	150,	-50,	200,
-INF,	-128,	-255,	-50,	0x0,	0x0,	-50,	-255,	-128,
-INF,	0xff,	-128,	200,	100,	100,	200,	-128,	0xff,
-INF,	-INF,	-INF,	-INF,	-INF,	-INF,	-INF,	-INF,	-INF,
-INF
};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBasicEngine::CBasicEngine()
{
	m_AI=0;
	m_AIFuncArr[0]=RandomScheme;
	m_AIFuncArr[1]=EatMost;
	m_AIFuncArr[2]=MobilityPrior;
	m_AIFuncArr[3]=StaticEvaluate;
	m_AIFuncArr[4]=StabEvaluate;
	SetAI(m_AI);
}

CBasicEngine::~CBasicEngine()
{

}
void CBasicEngine::SetAI(int ai){
	if(ai>=0 && ai<5){
		m_AI= ai;
		m_AIFunc=m_AIFuncArr[m_AI];
	}
}
void CBasicEngine::Search(ChessType* board, ChessType col){
	ChessType curboard[CH_LEN];
	memcpy(curboard, board, CH_LEN*sizeof(ChessType));
	m_Time =NowTime();
	srand((unsigned int)m_Time);
	(this->*m_AIFunc)(curboard, col);
	m_Time = NowTime() - m_Time ;
	return ;
}

void CBasicEngine::EatMost(ChessType *board, ChessType color)	//大食
{
	FlipSpot colFlipSpot[32];
	int BestIndex, BestValue=0;
	m_Nodes=CGameScript::GenerateLoc(color, board, colFlipSpot);

	for(int i=0; i<m_Nodes; i++){
		if(rand()%10>5)colFlipSpot[i].flips++;
		if(colFlipSpot[i].flips>BestValue){
			BestIndex=i;
			BestValue=colFlipSpot[i].flips;
		}
	}
	if(BestIndex>=0 && BestIndex<m_Nodes){
		m_BestMove=colFlipSpot[BestIndex].square;
		m_BestScore=colFlipSpot[BestIndex].flips;
	}else if(m_Nodes){
		m_BestMove=colFlipSpot[0].square;
		m_BestScore=colFlipSpot[0].flips;
	}else{
		m_BestMove=0;
		m_BestScore=0;
	}
}
void CBasicEngine::RandomScheme(ChessType *board, ChessType color)	//随便
{
	FlipSpot colFlipSpot[32];
	int BestIndex;
	m_Nodes=CGameScript::GenerateLoc(color, board, colFlipSpot);

	if(m_Nodes){
		BestIndex=rand()%m_Nodes;
		m_BestMove=colFlipSpot[BestIndex].square;
		m_BestScore=colFlipSpot[BestIndex].flips;
	}else{
		m_BestMove=0;
		m_BestScore=0;
	}
}

void CBasicEngine::MobilityPrior(ChessType *board, ChessType color)	//制动
{
	FlipSpot colFlipSpot[32];
	int BestIndex, BestValue=64, colFlipCount, tmpValue;
	ChessType oppcolor = Oppl_ch(color);
	m_Nodes=CGameScript::GenerateLoc(color, board, colFlipSpot);

	for(int i=0; i<m_Nodes; i++){
		colFlipCount=CGameScript::DoFlips(board, colFlipSpot[i].square, color, oppcolor);
		board[colFlipSpot[i].square]=color;
		tmpValue=CGameScript::CountLocablePt(oppcolor, board);
		if(rand()%10>5)tmpValue--;
		if(tmpValue<BestValue){
			BestValue=tmpValue;
			BestIndex=i;
		}
		board[colFlipSpot[i].square]=EMPTY;
		CGameScript::UndoFlips(board, colFlipCount, oppcolor);
	}
	m_BestMove=colFlipSpot[BestIndex].square;
	m_BestScore=m_Nodes-BestValue;
}

void CBasicEngine::StaticEvaluate(ChessType *board, ChessType color)	//静估
{
	FlipSpot colFlipSpot[32];
	int BestIndex, BestValue=-INF, tmpValue;
	ChessType oppcolor = Oppl_ch(color);
	m_Nodes=CGameScript::GenerateLoc(color, board, colFlipSpot);

	for(int i=0; i<m_Nodes; i++){
		tmpValue=Eval_map[colFlipSpot[i].square];
		if(rand()%10>5)tmpValue++;
		if(tmpValue>BestValue){
			BestValue=tmpValue;
			BestIndex=i;
		}
	}
	m_BestMove=colFlipSpot[BestIndex].square;
	m_BestScore=m_Nodes-BestValue;
}

void CBasicEngine::StabEvaluate(ChessType *board, ChessType color)	//稳估
{
	FlipSpot colFlipSpot[32], oppFlipSpot[32];
	int BestIndex, empties, BestValue=-INF, colFlipCount, oppFlipCount, oppLocCount;
	ChessType oppcolor = Oppl_ch(color);
	ChessType back[CH_LEN];
	m_Nodes=CGameScript::GenerateLoc(color, board, colFlipSpot);

	empties=CGameScript::CountChess(board, (ChessType)EMPTY);
	for(int i=0; i<m_Nodes; i++){
		colFlipCount=CGameScript::DoFlips(board, colFlipSpot[i].square, color, oppcolor);
		board[colFlipSpot[i].square]=color;
		memcpy(back, board, CH_LEN*sizeof(ChessType));
		if(empties>25){
			oppLocCount=CGameScript::GenerateLoc(oppcolor, board, oppFlipSpot);
			for(int j=0; j<oppLocCount; j++){
				oppFlipCount=CGameScript::DoFlips(board, oppFlipSpot[j].square, oppcolor, color);
				board[colFlipSpot[i].square]=color;
				for(int k=X_UB, u=0; k<CH_LEN-X_UB; k++)
					if(board[k]==color && board[k]==back[k]) u++;
				if(rand()%10>5) u++;
				if(u>BestValue){
					BestValue=u;
					BestIndex=i;
				}
				board[colFlipSpot[i].square]=EMPTY;
				CGameScript::UndoFlips(board, oppFlipCount, color);
			}
		}else{
			for(int k=X_UB, u=0; k<CH_LEN-X_UB; k++){
				if(board[k]==color)
					if(CGameScript::IsStab(board, k, color)) u++;
				if(rand()%10>5)u++;
				if(u>BestValue){
					BestValue=u;
					BestIndex=i;
				}
			}
		}
		board[colFlipSpot[i].square]=EMPTY;
		CGameScript::UndoFlips(board, colFlipCount, oppcolor);
	}
	m_BestMove=colFlipSpot[BestIndex].square;
	m_BestScore=m_Nodes*10-BestValue;
}
