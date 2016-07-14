// RowEvaluator.cpp: implementation of the CRowEvaluator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "RowEvaluator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRowEvaluator::CRowEvaluator()
{

}

CRowEvaluator::~CRowEvaluator()
{

}

int CRowEvaluator::Evaluate(ChessType* board, ChessType col, int empties, bool end)
{
	if(end || !empties){
		return FinalScore(board, col);
	}

//	int emptiesNum=CGameScript::CountChess(board, (ChessType)EMPTY);
	return Score(board, col);
}



//找出所有在水平方向受保护的color方的棋子，并累计分数
int CRowEvaluator::scan_horizontal_aixes(ChessType *board, ChessType color) const{
	ChessType *cur_ptr;
	int piece[XH_UB][2];
	int score=0, count=0, cnter=0, tmpscore=0;
	BOOL bFull;
	for(int row=1; row<=YC_UB; row++)	{
		tmpscore = (row == 1 || row == XC_UB) ? 10:2;
		cur_ptr = board+Conv(1,row);
		bFull = TRUE;	cnter=count=0;
		while(*cur_ptr != BLOCK){
			ASSERT(!(cnter>8));
			if(*cur_ptr == color){
				piece[count][0] = cnter;
				while(*cur_ptr == color){cur_ptr++; cnter++;}
				piece[count++][1] = cnter;
			}else{
				cur_ptr++; 
				cnter++;
			}
			if(*cur_ptr==EMPTY) bFull = FALSE; 
		}
		while(count--){
			int nums = (piece[count][1]-piece[count][0]);
			if(bFull || piece[count][0]==0 || piece[count][1] == XC_UB)
				score += nums;
			if(piece[count][0]==0 || piece[count][1] == XC_UB)
				score += tmpscore;
			else if(!bFull && (piece[count][0] == 1 || piece[count][1] == XC_UB-1) && (row == 1 || row == XC_UB))
				score -= tmpscore;
		}
	}

	 return score;
}

//找出所有在垂直方向受保护的color方的棋子，并累计分数
int CRowEvaluator::scan_vertical_aixes(ChessType *board, ChessType color) const{
	ChessType *cur_ptr;
	int piece[YH_UB][2];
	int score=0, count=0, cnter=0, tmpscore=0;
	BOOL bFull;
	for(ChessType col=1; col<=XC_UB; col++){
        tmpscore = (col == 1 || col == 8) ? 10:2;
		cur_ptr = board+Conv(col,1);
		bFull = TRUE;	cnter=count=0;
		while(*cur_ptr != BLOCK){
			ASSERT(!(cnter>8));
			if(*cur_ptr == color){
				piece[count][0]  = cnter;
				while(*cur_ptr == color){ cur_ptr += GO_DOWN; cnter++;}
				piece[count++][1] = cnter;
			}else{
				cur_ptr += GO_DOWN;
				cnter++;
			}
			if(*cur_ptr==EMPTY) 
				bFull = FALSE;
			
		}
		while(count--){
			int nums = (piece[count][1]-piece[count][0]);
			if(bFull || piece[count][0]==0 || piece[count][1] == YC_UB)
				score += nums;
			if(piece[count][0]==0 || piece[count][1] == YC_UB)
				score += tmpscore;
			else if(!bFull && (piece[count][0] == 1 || piece[count][1] == YC_UB-1) && (col == 1 || col == YC_UB))
				score -= (tmpscore<<1);
		}
	}
   	return score;
}

//找出所有在右上到左下方向受保护的color方的棋子，并累//////计分数//
int CRowEvaluator::scan_diagonal_RL_aixes(ChessType *board, ChessType color) const{
    ChessType *cur_ptr;
	int piece[4][2];
	int score =0, count=0, cnter=0, tmpscore;
	BOOL bFull;
	for(int aixes = -(XC_UB-3); aixes <= (YC_UB-3); aixes++){
        tmpscore = (aixes == 0) ? 10:2;
		if(aixes <=0) cur_ptr = board+Conv(XC_UB+aixes,1);
		else cur_ptr = board+Conv(XC_UB,aixes+1);
		bFull = TRUE;	cnter=count=0;
		while(*cur_ptr !=BLOCK){
			ASSERT(!(cnter>8));
			if(*cur_ptr == color){
				piece[count][0]  = cnter;
				while(*cur_ptr == color) {cur_ptr += GO_DOWNLEFT;cnter++;}
				piece[count++][1] = cnter;
			}else{
				cur_ptr += GO_DOWNLEFT;
				cnter++;
			}
			if(*cur_ptr==EMPTY)
				bFull = FALSE;
		}
		while(count--){
			int nums = piece[count][1]-piece[count][0];
			BOOL  toborder = (piece[count][0] ==0 || piece[count][1] == cnter);
			if(bFull || toborder) score += nums;
			if((aixes == 1 || aixes == -1) && toborder)
				score -= tmpscore;
			else if(toborder)//如果是这块棋到达边界
				score += tmpscore;
			//如果有棋在角边上，则扣分
			else if(!bFull && aixes==0 && (piece[count][0] == 1 || piece[count][1] == 6))
				score -= (tmpscore<<1);
		}
	}

	//如果角边有棋子，扣分
	if(board[LUC_in] == color) score += 10;
	else {
		if(board[LUC_C1] == color) score -=2;
		if(board[LUC_C2] == color) score -=2;
		if(board[LUC_X]== color) score -=2;
	}
     
	if(board[RDC_in] == color) score +=10;
	else{
		if(board[RDC_C1]  == color) score -=2;
		if(board[RDC_C2]== color) score -=2;
		if(board[RDC_X]== color) score -= 2;
	}    
    return score;
}
//找出所有在左上到右下方向受保护的color方的棋子，并累计分数//
int CRowEvaluator::scan_diagonal_LR_aixes(ChessType *board,  ChessType color) const{
    ChessType *cur_ptr;
	int piece[4][2];
	int score =0, count=0, cnter=0, tmpscore;
	BOOL bFull;
	for(int aixes = -5; aixes <= 5; aixes++){
        tmpscore = (aixes == 0) ? 10:2;
		if(aixes <=0) cur_ptr = board+Conv(1-aixes,1);
		else cur_ptr = board+Conv(1,aixes+1);
		bFull = TRUE; cnter=count=0;
		while(*cur_ptr !=BLOCK){
			ASSERT(!(cnter>8));
			if(*cur_ptr == color){
				piece[count][0] = cnter;
				while(*cur_ptr == color){ cur_ptr += GO_DOWNRIGHT; cnter++;}
				piece[count++][1] = cnter;
			}else{
				cur_ptr += GO_DOWNRIGHT;
				cnter++;
			}
			if(*cur_ptr==EMPTY)
				bFull = FALSE;
		} 
		while(count--){
			int nums = piece[count][1]-piece[count][0];
			BOOL  toborder = (piece[count][0] == 0|| piece[count][1] == cnter);
			if(bFull || toborder) score += nums;
			//如果角边有棋子，扣分//
			if((aixes == 1 || aixes == -1) && toborder)
			    score -= tmpscore;
			else if(toborder)	//如果是这块棋到达边界
				score += tmpscore;
			//如果有棋在角边上，则扣分, 主对角线方向//
			else if(!bFull && aixes && (piece[count][0] == 1 || piece[count][1] == 6))
				score -= (tmpscore<<1);
		}
	}
	//如果角边有棋子，扣分
	if(board[RUC_in] == color) score += 10;
	else {
		if(board[RUC_C1] == color) score -=2;
		if(board[RUC_C2] == color) score -=2;
		if(board[RUC_X] == color) score -=2;
	}
	if(board[LDC_in] == color) score +=10;
	else{
		if(board[LDC_C1] == color) score -=2;
		if(board[LDC_C2] == color) score -=2;
		if(board[LDC_X] == color) score -= 2;
	}    
    return score;
}
//计算棋局board的状态分//
int CRowEvaluator::Score(ChessType *board, ChessType color) const
{
	int score=0;
	score += scan_vertical_aixes(board, color);
	score += scan_horizontal_aixes(board,  color);
	score += scan_diagonal_LR_aixes(board, color);
	score += scan_diagonal_RL_aixes(board, color);
	ChessType oppcol = Oppl_ch(color);
	if(board[LUC_in] == oppcol) score -= 44;
	if(board[LDC_in] == oppcol) score -= 44;
	if(board[RUC_in] == oppcol) score -= 44;
	if(board[RDC_in] == oppcol) score -= 44;
	return score;
}
