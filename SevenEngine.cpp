// SevenEngine.cpp: implementation of the CSevenEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "GameScript.h"
#include "SevenEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int CSevenEngine::m_BasicDepth[]={6, 7, 8};
const int CSevenEngine::m_AdvanceDepth[]={5, 6, 7};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSevenEngine::CSevenEngine()
{
	m_AI=1;
	m_CurDepth = 0;
	m_MaxDepth = 4;
	m_MyColor = BLACK;
}

CSevenEngine::~CSevenEngine()
{

}


//从棋盘的一个状态出发，扩展此结点，并返回此结点的部分回溯值
void CSevenEngine::extend_node_one(tagTreeNode *node_ptr, tagTreeNode *parent_ptr, ChessType color)
{
	tagTreeNode childnode;
	FlipSpot flipSpot[32];
	int num, FlipCount;
	ChessType oppcolor=Oppl_ch(color);
	num = CGameScript::GenerateLoc(color, node_ptr->board, flipSpot);
	if(++m_CurDepth == m_MaxDepth || num==0 ) {	//如果是终局状态，则返回状态估值函数的值
		node_ptr->value = m_pEM->Evaluate(node_ptr->board, m_MyColor);//如果已方PASS但没到棋局结束,要扣分
		if(!num) {
			if(!CGameScript::FindLocablePt(oppcolor, node_ptr->board)) return;//如果双方都没棋下
			if(color == m_MyColor) {
				node_ptr->value -= 15;
				return ;
			}
			node_ptr->value += 15;
		}
		return;		   
	}
	//初始化回溯值
	node_ptr->value = (color == m_MyColor)? -INF : INF;
	while(num){
		FlipCount = CGameScript::DoFlips(node_ptr->board, flipSpot[--num].square, color, oppcolor);
		node_ptr->board[flipSpot[num].square]=color;
		int depth = m_CurDepth;
		childnode.board=node_ptr->board;
		m_Nodes++;
		ASSERT(depth);
		ReportTrace(flipSpot[num].square, depth);
		if(m_bSearchContinue)extend_node_one(&childnode, node_ptr, oppcolor);
		m_CurDepth = depth;
		node_ptr->board[flipSpot[num].square]=EMPTY;
		CGameScript::UndoFlips(node_ptr->board, FlipCount, oppcolor);
		if(color == m_MyColor){		//如果此结点是棋手一方，则部分回溯值是子结点中最大的一个
			if(childnode.value > node_ptr->value){
				node_ptr->value = childnode.value; 
				node_ptr->movepos = flipSpot[num].square;
				if(m_CurDepth==1) SetBest(node_ptr->movepos);//report best
			}
		}else{	//如果是对手一方，部分回溯值是子结点中最小的一个
			if(childnode.value < node_ptr->value){
				node_ptr->value = childnode.value;
				node_ptr->movepos = flipSpot[num].square;
				if(m_CurDepth==1) SetBest(node_ptr->movepos);//report best
			}
		}
		if(parent_ptr){
			if(color != m_MyColor){
				if(node_ptr->value <= parent_ptr->value)return;//α裁减
			} else {
				if(node_ptr->value >= parent_ptr->value)return;//β裁减
			}
		}
	}
	return;
}


void CSevenEngine::extend_node_two(tagTreeNode *node_ptr, tagTreeNode *parent_ptr,ChessType color)
{
	tagTreeNode childnode;
	FlipSpot flipSpot[32];
	int num, FlipCount;
	ChessType oppcolor=Oppl_ch(color);
	num = CGameScript::GenerateLoc(color, node_ptr->board, flipSpot);
	if(num==0) {	//如果是终局状态，则返回状态估值函数的值
		short bw[2];
		CGameScript::CountChess(node_ptr->board, bw);
		node_ptr->value=bw[0]-bw[1];
		if(m_MyColor == WHITE)node_ptr->value*=-1;
		if(!num) {
			if(!CGameScript::FindLocablePt(oppcolor, node_ptr->board)) return;//如果双方都没棋下
			if(color == m_MyColor) {
				node_ptr->value -= 10;
				return ;
			}
			node_ptr->value += 10;
		}
		return;		   
	}
	//初始化回溯值
	node_ptr->value = (color == m_MyColor)? -INF : INF;
	while(num){
		FlipCount = CGameScript::DoFlips(node_ptr->board, flipSpot[--num].square, color, oppcolor);
		node_ptr->board[flipSpot[num].square]=color;
		//递归计算部分回溯值
		int depth = ++m_CurDepth;
		childnode.board=node_ptr->board;
		m_Nodes++;
		ReportTrace(flipSpot[num].square, depth);
		if(m_bSearchContinue)extend_node_one(&childnode, node_ptr, oppcolor);
		m_CurDepth = depth;

		node_ptr->board[flipSpot[num].square]=EMPTY;
		CGameScript::UndoFlips(node_ptr->board, FlipCount, oppcolor);
		if(color == m_MyColor){		//如果此结点是棋手一方，则部分回溯值是子结点中最大的一个
			if(childnode.value > node_ptr->value){
				node_ptr->value = childnode.value; 
				node_ptr->movepos = flipSpot[num].square;
				if(m_CurDepth==0) SetBest(node_ptr->movepos);
			}
		}else{	//如果是对手一方，部分回溯值是子结点中最小的一个
			if(childnode.value < node_ptr->value){
				node_ptr->value = childnode.value;
				node_ptr->movepos = flipSpot[num].square;
				if(m_CurDepth==0) SetBest(node_ptr->movepos);
			}
		}

		if(parent_ptr){
			if(color != m_MyColor){
				if(node_ptr->value <= parent_ptr->value)return;//α裁减
			} else {
				if(node_ptr->value >= parent_ptr->value)return;//β裁减
			}
		}
	}
	return;
}

void CSevenEngine::Search(ChessType* curboard, ChessType col){
	tagTreeNode node;
	ChessType board[CH_LEN];
	memcpy(board, curboard, CH_LEN*sizeof(ChessType));
	m_Time =NowTime();
	m_bSearchContinue=true;
	int empties = CGameScript::CountChess(board, (ChessType)EMPTY);
	m_MyColor = col;
	node.board=board;
	node.movepos =0;
	m_CurDepth =0;
	m_Nodes = 1;
	SetBest(0);
	if(empties<= 12) {
		extend_node_two(&node, NULL, m_MyColor);
	} else if(empties < 50) {
		m_MaxDepth = m_AdvanceDepth[m_AI];
		extend_node_one(&node, NULL, m_MyColor);
	} else {
		m_MaxDepth = m_BasicDepth[m_AI];
		extend_node_one(&node, NULL, m_MyColor);
	}
	if(node.movepos == 0){
		node.movepos = CGameScript::FindLocablePt(col, board);
	}
	SetBest(node.movepos);
	m_BestScore=node.value;
	m_Time =NowTime()-m_Time;
} 

void CSevenEngine::SetAI(int ai){
	if(ai<0||ai>=3)return;
	m_AI=ai;
}
