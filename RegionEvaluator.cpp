// RegionEvaluator.cpp: implementation of the CRegionEvaluator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "RegionEvaluator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegionEvaluator::CRegionEvaluator()
{

}

CRegionEvaluator::~CRegionEvaluator()
{

}

int CRegionEvaluator::Evaluate(ChessType* board, ChessType col, int empties, bool end)
{
	if(end || !empties){
		return FinalScore(board, col);
	}

	int emptiesNum=CGameScript::CountChess(board, (ChessType)EMPTY);
	return Score(board, col, emptiesNum);
}

int CRegionEvaluator::C2Val(ChessType c, ChessType x, ChessType o, int xv, int ov, int m) const
{
	return (c!=x?(c!=o?m:ov):xv);
}


int CRegionEvaluator::Score(ChessType* board, ChessType color, int emptiesNum) const
{
	ChessType oppcolor = Oppl_ch(color);
	int tmpEval = BorderScore(board, color, oppcolor);		//四边
	tmpEval += AngleScore(board, color, oppcolor);			//四角
	tmpEval += CenterScore(board, color, oppcolor);			//中心区域
	tmpEval += InnerBorderScore(board, color, oppcolor);	//中心区域
	tmpEval += CountScore(board, color, oppcolor, emptiesNum);

	return tmpEval;
}

int CRegionEvaluator::AngleScore(ChessType* board, ChessType color, ChessType oppcolor) const
{
	int tmpEval = 0;
	if(board[LUC_in] == EMPTY){
		tmpEval += C2Val(board[LUC_X], color, oppcolor, -50, 50, (CGameScript::IsLocable(LUC_X, color, board) ? -5 : 0));
		tmpEval += C2Val(board[LUC_C1], color, oppcolor, (board[PT_C1] != EMPTY ? -5 : -10), (board[PT_C1] != EMPTY ? 5 : 10), (CGameScript::IsLocable(LUC_C1, color, board) ? -2 : 0));
		tmpEval += C2Val(board[LUC_C2], color, oppcolor, (board[PT_A3] != EMPTY ? -5 : -10), (board[PT_A3] != EMPTY ? 5 : 10), (CGameScript::IsLocable(LUC_C2, color, board) ? -2 : 0));
		if(CGameScript::IsLocable(LUC_in, color, board))
			tmpEval += 12;
		if(board[LUC_C1] != EMPTY || board[LUC_C2] != EMPTY)
			tmpEval += C2Val(board[LUC_X], color, oppcolor, -4, 4);
	} else{
		if(board[LUC_C1] != EMPTY || board[LUC_C2] != EMPTY){
			tmpEval += board[LUC_in] != color ? -80 : 80;
			tmpEval += C2Val(board[LUC_C1], color, oppcolor, 40, -40);
			tmpEval += C2Val(board[LUC_C2], color, oppcolor, 40, -40);
		}else{
			tmpEval += board[LUC_in] != color ? -60 : 60;
		}
		tmpEval += C2Val(board[LUC_X], color, oppcolor, 2, -2);
	}
	if(board[RUC_in] == EMPTY){
		tmpEval += C2Val(board[RUC_X], color, oppcolor, -50, 50, (CGameScript::IsLocable(RUC_X, color, board) ? -5 : 0));
		tmpEval += C2Val(board[RUC_C1], color, oppcolor, (board[PT_F1] != EMPTY ? -5 : -10), (board[PT_F1] != EMPTY ? 5 : 10), (CGameScript::IsLocable(RUC_C1, color, board) ? -2 : 0));
		tmpEval += C2Val(board[RUC_C2], color, oppcolor, (board[PT_H3] != EMPTY ? -5 : -10), (board[PT_H3] != EMPTY ? 5 : 10), (CGameScript::IsLocable(RUC_C2, color, board) ? -2 : 0));
		if(CGameScript::IsLocable(RUC_in, color, board))
			tmpEval += 12;
		if(board[RUC_C1] != EMPTY || board[RUC_C2] != EMPTY)
			tmpEval += C2Val(board[RUC_X], color, oppcolor, -4, 4);
	} else{
		if(board[RUC_C1] != EMPTY || board[RUC_C2] != EMPTY) {
			tmpEval += board[RUC_in] != color ? -80 : 80;
			tmpEval += C2Val(board[RUC_C1], color, oppcolor, 40, -40);
			tmpEval += C2Val(board[RUC_C2], color, oppcolor, 40, -40);
		} else {
			tmpEval += board[RUC_in] != color ? -60 : 60;
		}
		tmpEval += C2Val(board[RUC_X], color, oppcolor, 2, -2);
	}
	if(board[LDC_in] == EMPTY){
		tmpEval += C2Val(board[LDC_X], color, oppcolor, -50, 50, (CGameScript::IsLocable(LDC_X, color, board) ? -5 : 0));
		tmpEval += C2Val(board[LDC_C1], color, oppcolor, (board[PT_C8] != EMPTY ? -5 : -10), (board[PT_C8] != EMPTY ? 5 : 10), (CGameScript::IsLocable(LDC_C1, color, board)? -2: 0));
		tmpEval += C2Val(board[LDC_C2], color, oppcolor, (board[PT_A6] != EMPTY ? -5 : -10), (board[PT_A6] != EMPTY ? 5 : 10), (CGameScript::IsLocable(LDC_C2, color, board)? -2: 0));
		if(CGameScript::IsLocable(LDC_in, color, board))
			tmpEval += 12;
		if(board[LDC_C2] != EMPTY || board[LDC_C1] != EMPTY)
			tmpEval += C2Val(board[LDC_X], color, oppcolor, -4, 4);
	} else{
		if(board[LDC_C1] != EMPTY || board[LDC_C2] != EMPTY){
			tmpEval += board[LDC_in] != color ? -80 : 80;
			tmpEval += C2Val(board[LDC_C1], color, oppcolor, 40, -40);
			tmpEval += C2Val(board[LDC_C2], color, oppcolor, 40, -40);
		} else {
			tmpEval += board[LDC_in] != color ? -60 : 60;
		}
		tmpEval += C2Val(board[LDC_X], color, oppcolor, 2, -2);
	}
	if(board[RDC_in] == EMPTY){
		tmpEval += C2Val(board[RDC_X], color, oppcolor, -50, 50, (CGameScript::IsLocable(RDC_X, color, board) ? -5 : 0));
		tmpEval += C2Val(board[RDC_C2], color, oppcolor, (board[PT_H6] != EMPTY ? -5 : -10), (board[PT_H6] != EMPTY ? 5 : 10), (CGameScript::IsLocable(RDC_C2, color, board) ? -2 : 0));
		tmpEval += C2Val(board[RDC_C1], color, oppcolor, (board[PT_F8] != EMPTY ? -5 : -10), (board[PT_F8] != EMPTY ? 5 : 10), (CGameScript::IsLocable(RDC_C1, color, board) ? -2 : 0));
		if(CGameScript::IsLocable(RDC_in, color, board))
			tmpEval += 12;
		if(board[RDC_C2] != EMPTY || board[RDC_C1] != EMPTY)
			tmpEval += C2Val(board[RDC_X], color, oppcolor, -4, 4);
	} else{
		if(board[RDC_C2] != EMPTY || board[RDC_C1] != EMPTY){
			tmpEval += board[RDC_in] != color ? -80 : 80;
			tmpEval += C2Val(board[RDC_C2], color, oppcolor, 40, -40);
			tmpEval += C2Val(board[RDC_C1], color, oppcolor, 40, -40);
		} else{
			tmpEval += board[RDC_in] != color ? -60 : 60;
		}
		tmpEval += C2Val(board[RDC_X], color, oppcolor, 2, -2);
	}
	return tmpEval;
}

int CRegionEvaluator::BorderScore(ChessType *board, ChessType color, ChessType oppcolor) const
{
	int i;
	int tmpEval = 0;
	if(board[LUC_in] != EMPTY || board[RUC_in] != EMPTY)  {
		for(i = PT_C1; i <= PT_F1; i+= GO_RIGHT)
			tmpEval += C2Val(board[i], color, oppcolor, 20, -20);
	} else{
		for(i = PT_C1; i <= PT_F1; i+= GO_RIGHT)
			tmpEval += C2Val(board[i], color, oppcolor, -2, 2);
	}

	if(board[RDC_in] != EMPTY || board[RUC_in] != EMPTY){
		for(i = PT_H3; i <= PT_H6; i += GO_DOWN)
			tmpEval += C2Val(board[i], color, oppcolor, 20, -20);
	} else{
		for(i = PT_H3; i <= PT_H6; i += GO_DOWN)
			tmpEval += C2Val(board[i], color, oppcolor, -2, 2);
	}

	if(board[RDC_in] != EMPTY || board[LDC_in] != EMPTY){
		for(i = PT_C8; i <= PT_F8; i+= GO_RIGHT)
			tmpEval += C2Val(board[i], color, oppcolor, 20, -20);
	} else{
		for(i = PT_C8; i <= PT_F8; i+= GO_RIGHT)
			tmpEval += C2Val(board[i], color, oppcolor, -2, 2);
	}

	if(board[LUC_in] != EMPTY || board[LDC_in] != EMPTY){
		for(i = PT_A3; i <= PT_A6; i += GO_DOWN)
			tmpEval += C2Val(board[i], color, oppcolor, 20, -20);
	} else{
		for(i = PT_A3; i <= PT_A6; i += GO_DOWN)
			tmpEval += C2Val(board[i], color, oppcolor, -2, 2);
	}
	return tmpEval;
}

int CRegionEvaluator::CenterScore(ChessType *board, ChessType color, ChessType oppcolor) const
{
	int tmpEval=0;
	for(int i = PT_C3; i <= PT_F6;){	//中心区域
		tmpEval += C2Val(board[i], color, oppcolor, -2, 2);
		if(i % XL_UB == 6)
			i += 6;
		else
			i+= GO_RIGHT;
	}
	return tmpEval;
}

int CRegionEvaluator::InnerBorderScore(ChessType *board, ChessType color, ChessType oppcolor) const
{
	int tmpEval = 0;
	int j = PT_C2;		//内边
	for(int i = PT_B3; j <= PT_F2; i += GO_DOWN){
		tmpEval += C2Val(board[j], color, oppcolor, -2, 2);
		tmpEval += C2Val(board[j+45], color, oppcolor, -2, 2);
		tmpEval += C2Val(board[i], color, oppcolor, -2, 2);
		tmpEval += C2Val(board[i+5], color, oppcolor, -2, 2);
		j+= GO_RIGHT;
	}
	return tmpEval;
}

int CRegionEvaluator::CountScore(ChessType *board, ChessType color, ChessType oppcolor, int emptiesNum) const
{
	int i, j;
	int tmpEval = 0;
	if(emptiesNum > 29){
		for(i = LUC_in; i <= RDC_in; i+= GO_RIGHT){
			if(board[i] == oppcolor){
				for(j = 0; j < 8; j++) {
					if(!CGameScript::IsLocable(i + CGameScript::DrctInc[j], color, board))
						continue;
					tmpEval += 20;
					break;
				}
			} else if(board[i] == color) {
				int sum = 0;
				for(j = 0; j < 8; j++)
					if(board[i + CGameScript::DrctInc[j]] == color || board[i + CGameScript::DrctInc[j]] == BLOCK)
						sum++;

				if(sum <= 2)
					tmpEval -= 10;
			}
		}
	} else {
		for(i = LUC_in; i <= RDC_in; i+= GO_RIGHT)
			if(CGameScript::IsLocable(i, color, board))
				tmpEval += 30;
			else if(board[i] == EMPTY || board[i] == oppcolor){
				int sum = 0;
				for(j = 0; j < 8; j++)
					if(board[i + CGameScript::DrctInc[j]] == color || board[i + CGameScript::DrctInc[j]] == BLOCK) sum++;
				if(sum >= 5)
					tmpEval -= 15;
			}
	}
	return tmpEval;
}
