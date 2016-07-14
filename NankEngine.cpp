// NankEngine.cpp: implementation of the CNankEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "NankEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//#define C2Val(c,x,o,xv,ov,m)	(c!=x?(c!=o?m:ov):xv)

const short CNankEngine::Index2Best[60]={
	10,	17,	73,	80,	21,	24,	29,	56,	66,	69,	34,	61,	22,	23,	38,	47,	67,	
	68,	43,	52,	30,	60,	33,	57,	31,	32,	39,	48,	58,	59,	42,	51,	12,	15,	
	28,	55,	75,	78,	35,	62,	13,	14,	37,	46,	76,	77,	44,	53,	11,	16,	19,	
	64,	74,	79,	26,	71,	20,	70,	25,	65
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNankEngine::CNankEngine()
{
	m_AI=0;
	m_CurDepth = 0;
}

CNankEngine::~CNankEngine()
{

}


void CNankEngine::Search(ChessType* board, ChessType color){
	memcpy(m_Curboard, board, CH_LEN*sizeof(ChessType));
	m_Time =NowTime();
	m_Nodes=0;
	m_CurDepth = 0;
	m_bSearchContinue=true;
//	srand((unsigned int)m_Time);

	int emptiesnum=CGameScript::CountChess(m_Curboard,(ChessType)EMPTY);
	m_Color = color;
	if(emptiesnum <= 20){
		if(emptiesnum < 13)
			AIEntry( emptiesnum + 1, 0, 0);
		else if(emptiesnum == 13)
			AIEntry(emptiesnum + 1, 5, 3);
		else if(emptiesnum == 14)
			AIEntry(emptiesnum + 1, 5, 3);
		else if(emptiesnum == 15)
			AIEntry(9+m_AI, 5, 4);
		else if(emptiesnum < 18)
			AIEntry(9+m_AI, 5, 4);
		else
			AIEntry(8+m_AI, 5, 2);
	} else
		AIEntry(6+m_AI, 4, 3);
	if(m_BestScore>32000)m_BestScore-=32000;
	else if(m_BestScore<-32000)m_BestScore+=32000;
	else m_BestScore=m_BestScore*50/32000;
	if(!m_BestMove){
		SetBest(CGameScript::FindLocablePt(color,board));
	}
	m_Time = NowTime() - m_Time;
	return ;
}

void CNankEngine::SetAI(int ai){
	if(ai<0||ai>=3)return;
	m_AI=ai;
}

int CNankEngine::Max_Min_Search(int depth, int alpha, int beta){
	int i, cnter, curRes;
	ChessType oppcolor=Oppl_ch(m_Color);

	if(depth == 0)
		return -(m_pEM->Evaluate(m_Curboard, m_Color));
	bool flag = false;
	for( i = 0; i < 60; i++){
		int sqnum = Index2Best[i];
		if(m_Curboard[sqnum]) continue;

		cnter = CGameScript::DoFlips(m_Curboard, sqnum, m_Color, oppcolor);
		if(cnter){
			m_Nodes++;
			m_Curboard[sqnum] =m_Color;
			flag = true;

			m_Color=oppcolor;
			ReportTrace(sqnum, ++m_CurDepth);
			if(m_bSearchContinue)
				curRes = Max_Min_Search(depth - 1, -beta, -alpha);
			m_CurDepth--;
			m_Color=Oppl_ch(m_Color);

			m_Curboard[sqnum] =EMPTY;
			CGameScript::UndoFlips(m_Curboard, cnter, oppcolor);
			if(curRes > alpha){
				alpha = curRes;
				if(curRes >= beta)
					return -alpha;
			}
		}
	}

	if(!flag){
		if(CGameScript::CountLocablePt(oppcolor, m_Curboard)==0)
			return m_pEM->Evaluate(m_Curboard, oppcolor, 0);
		else{
			m_Color=oppcolor;
			if(m_bSearchContinue) curRes=-Max_Min_Search(depth + 1, -beta, -alpha);
			m_Color=Oppl_ch(m_Color);
			return curRes;
		}
	} else
		return -alpha;
}

void CNankEngine::AIEntry(int maxDepth, int firstDepth, int prenum){
	int alpha = -32767;
	int beta = 32767;
	int i, j, sqnum, cnter, curRes;
	short SecondSearchCount = 0;
	ChessType oppcolor = Oppl_ch(m_Color);
	SetBest(0);
	if(firstDepth == 0){
		for(i = 0; i < 60; i++){
			sqnum = Index2Best[i];
			if(m_Curboard[sqnum]) continue;
			cnter=CGameScript::DoFlips(m_Curboard, sqnum, m_Color, oppcolor);
			if(cnter){
				m_Curboard[sqnum] =m_Color;
				m_Nodes++;
				m_Color=oppcolor;
				curRes = Max_Min_Search((maxDepth - 1), -beta, -alpha);
				m_Color=Oppl_ch(m_Color);

				if(curRes > alpha) {
					alpha = curRes;
					SetBest(sqnum);
					m_BestScore = curRes;
				}
				m_Curboard[sqnum] = EMPTY;
				CGameScript::UndoFlips(m_Curboard, cnter, oppcolor);
			}
		}
		return;
	}

	for(i = 0; i < 60; i++){
		sqnum = Index2Best[i];
		if(m_Curboard[sqnum]) continue;
		cnter=CGameScript::DoFlips(m_Curboard, sqnum, m_Color, oppcolor);
		if(cnter){
			m_Curboard[sqnum] =m_Color;
			m_Nodes++;
			m_Color = oppcolor;
			curRes = Max_Min_Search((firstDepth - 1), -beta, -alpha);
			m_Color = Oppl_ch(m_Color);
			if(curRes > alpha) {
				NodeBak nodebak;
				nodebak.score = curRes;
				nodebak.preDot = sqnum;
				for(j = SecondSearchCount - 1; j >= 0; j--) {
					if(curRes <= m_NodeBak[j].score)
						break;
					if(j != prenum)
						m_NodeBak[j+1] = m_NodeBak[j];
				}

				if(j+1 == 0){
					SetBest(sqnum);
					m_BestScore = curRes;
				}
				m_NodeBak[j+1] = nodebak;
				if(SecondSearchCount <= prenum)
					SecondSearchCount++;
				if(SecondSearchCount > prenum)
					alpha = m_NodeBak[prenum].score;
			}
			m_Curboard[sqnum] = EMPTY;
			CGameScript::UndoFlips(m_Curboard, cnter, oppcolor);
		}
	}

	alpha = -32767;
	for(i = 0; i < SecondSearchCount; i++){ 
		sqnum=m_NodeBak[i].preDot;
		if(m_Curboard[sqnum]) continue;
		cnter=CGameScript::DoFlips(m_Curboard, sqnum, m_Color, oppcolor);
		m_Curboard[sqnum] =m_Color;
		m_Color=oppcolor;
		curRes = Max_Min_Search((maxDepth - 1), -beta, -alpha);
		if(curRes > alpha)  {
			alpha = curRes;
			SetBest(m_NodeBak[i].preDot);
			m_BestScore = curRes;
		}
		m_Color=Oppl_ch(m_Color);
		m_Curboard[sqnum] = EMPTY;
		CGameScript::UndoFlips(m_Curboard, cnter, oppcolor);
	}
}
