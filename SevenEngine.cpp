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


//�����̵�һ��״̬��������չ�˽�㣬�����ش˽��Ĳ��ֻ���ֵ
void CSevenEngine::extend_node_one(tagTreeNode *node_ptr, tagTreeNode *parent_ptr, ChessType color)
{
	tagTreeNode childnode;
	FlipSpot flipSpot[32];
	int num, FlipCount;
	ChessType oppcolor=Oppl_ch(color);
	num = CGameScript::GenerateLoc(color, node_ptr->board, flipSpot);
	if(++m_CurDepth == m_MaxDepth || num==0 ) {	//������վ�״̬���򷵻�״̬��ֵ������ֵ
		node_ptr->value = m_pEM->Evaluate(node_ptr->board, m_MyColor);//����ѷ�PASS��û����ֽ���,Ҫ�۷�
		if(!num) {
			if(!CGameScript::FindLocablePt(oppcolor, node_ptr->board)) return;//���˫����û����
			if(color == m_MyColor) {
				node_ptr->value -= 15;
				return ;
			}
			node_ptr->value += 15;
		}
		return;		   
	}
	//��ʼ������ֵ
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
		if(color == m_MyColor){		//����˽��������һ�����򲿷ֻ���ֵ���ӽ��������һ��
			if(childnode.value > node_ptr->value){
				node_ptr->value = childnode.value; 
				node_ptr->movepos = flipSpot[num].square;
				if(m_CurDepth==1) SetBest(node_ptr->movepos);//report best
			}
		}else{	//����Ƕ���һ�������ֻ���ֵ���ӽ������С��һ��
			if(childnode.value < node_ptr->value){
				node_ptr->value = childnode.value;
				node_ptr->movepos = flipSpot[num].square;
				if(m_CurDepth==1) SetBest(node_ptr->movepos);//report best
			}
		}
		if(parent_ptr){
			if(color != m_MyColor){
				if(node_ptr->value <= parent_ptr->value)return;//���ü�
			} else {
				if(node_ptr->value >= parent_ptr->value)return;//�²ü�
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
	if(num==0) {	//������վ�״̬���򷵻�״̬��ֵ������ֵ
		short bw[2];
		CGameScript::CountChess(node_ptr->board, bw);
		node_ptr->value=bw[0]-bw[1];
		if(m_MyColor == WHITE)node_ptr->value*=-1;
		if(!num) {
			if(!CGameScript::FindLocablePt(oppcolor, node_ptr->board)) return;//���˫����û����
			if(color == m_MyColor) {
				node_ptr->value -= 10;
				return ;
			}
			node_ptr->value += 10;
		}
		return;		   
	}
	//��ʼ������ֵ
	node_ptr->value = (color == m_MyColor)? -INF : INF;
	while(num){
		FlipCount = CGameScript::DoFlips(node_ptr->board, flipSpot[--num].square, color, oppcolor);
		node_ptr->board[flipSpot[num].square]=color;
		//�ݹ���㲿�ֻ���ֵ
		int depth = ++m_CurDepth;
		childnode.board=node_ptr->board;
		m_Nodes++;
		ReportTrace(flipSpot[num].square, depth);
		if(m_bSearchContinue)extend_node_one(&childnode, node_ptr, oppcolor);
		m_CurDepth = depth;

		node_ptr->board[flipSpot[num].square]=EMPTY;
		CGameScript::UndoFlips(node_ptr->board, FlipCount, oppcolor);
		if(color == m_MyColor){		//����˽��������һ�����򲿷ֻ���ֵ���ӽ��������һ��
			if(childnode.value > node_ptr->value){
				node_ptr->value = childnode.value; 
				node_ptr->movepos = flipSpot[num].square;
				if(m_CurDepth==0) SetBest(node_ptr->movepos);
			}
		}else{	//����Ƕ���һ�������ֻ���ֵ���ӽ������С��һ��
			if(childnode.value < node_ptr->value){
				node_ptr->value = childnode.value;
				node_ptr->movepos = flipSpot[num].square;
				if(m_CurDepth==0) SetBest(node_ptr->movepos);
			}
		}

		if(parent_ptr){
			if(color != m_MyColor){
				if(node_ptr->value <= parent_ptr->value)return;//���ü�
			} else {
				if(node_ptr->value >= parent_ptr->value)return;//�²ü�
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
