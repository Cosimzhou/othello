// StaSolve.cpp: implementation of the CArtStaSolve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "ArtStaSolve.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArtStaSolve::CArtStaSolve()
{
	searchDepth = 6;
	existBook = false;
	foundInBook = false;
}

CArtStaSolve::~CArtStaSolve()
{

}


int CArtStaSolve::FastestFirstSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove){
	int square, curMaxEval = -100000001;
	ChessType oppcolor = Oppl_ch(color);
	Empties* emptiesArray[0x40];
	int MobilityArray[0x40];
	bool flag = false;
	if (depth == 0){
		nodes++;
		return QuiescenceSolve(board, alpha, beta, color, 2, empties, discdiff, prevmove);
	}
	int index = 0;
	Empties* emHead = &EmHead;
	Empties* next = emHead->next;
	while (next != NULL){
		square = next->Square;
		int flipCount = CGameScript::DoFlips(board, square, color, oppcolor);
		if (flipCount > 0){
			board[square] = color;
			emHead->next = next->next;
			MobilityArray[index] = -count_mobility(board, oppcolor);
			CGameScript::UndoFlips(board, flipCount, oppcolor);
			emHead->next = next;
			board[square] = EMPTY;
			emptiesArray[index] = next;
			index++;
		}
		emHead = next;
		next = next->next;
	}
	if (index != 0){
		for (int i = 0; i < index; i++){
			int curResult, max_mobility = MobilityArray[i], num10 = i, num2 = i + 1;
			while (num2 < index){
				if (MobilityArray[num2] > max_mobility){
					max_mobility = MobilityArray[num2];
					num10 = num2;
				}
				num2++;
			}
			next = emptiesArray[num10];
			emptiesArray[num10] = emptiesArray[i];
			MobilityArray[num10] = MobilityArray[i];
			square = next->Square;
//				int holeId = next->HoleID;
			num2 = CGameScript::DoFlips(board, square, color, oppcolor);
			board[square] = color;

			next->prev->next = next->next;
			if (next->next != NULL)
				next->next->prev = next->prev;

			nodes++;
			if(m_bSearchContinue){
				m_pEng->ReportTrace(square, ++curDepth);
				if (flag){
					curResult = -FastestFirstSolve(board, -alpha - 1, -alpha, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * num2)) - 1, square);
					if ((curResult > alpha) && (curResult < beta))
						curResult = -FastestFirstSolve(board, -beta, -curResult, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * num2)) - 1, square);
				}else
					curResult = -FastestFirstSolve(board, -beta, -alpha, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * num2)) - 1, square);
				curDepth--;
			}
			CGameScript::UndoFlips(board, num2, oppcolor);
			board[square] = EMPTY;

			next->prev->next = next;
			if (next->next != NULL)
				next->next->prev = next;

			if (curResult > curMaxEval){
				curMaxEval = curResult;
				if (curResult > alpha){
					if (curResult >= beta)
						return curMaxEval;
					alpha = curResult;
					flag = true;
				}
			}
		}
	}else{
		if (prevmove == 0){
			if (discdiff > 0) return 100000000;
			if (discdiff < 0) return -100000000;
			return 0;
		}
		m_pEng->ReportTrace(square, ++curDepth);
		curMaxEval = -FastestFirstSolve(board, -beta, -alpha, oppcolor, depth, empties, -discdiff, 0);
		curDepth--;
	}
	return curMaxEval;

}

int CArtStaSolve::QuiescenceSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove){

	int square;
	int curMaxEval = -100000000;
	ChessType oppcolor = Oppl_ch(color);
	Empties* emptiesArray[0x40];
	int MobilityArray[0x40];
	int curEval = eval.StaEval2(board, color, oppcolor, empties, &EmHead);
	if (((curEval >= beta) || (curEval >= 0xfa0)) || (depth == 0)) return curEval;
	if (curEval > alpha) alpha = curEval;
	int index = 0;
	Empties* emHead = &EmHead;
	Empties* next = emHead->next;
	while (next != NULL){
		square = next->Square;
		int flipCount = CGameScript::DoFlips(board, square, color, oppcolor);
		if (flipCount > 0){
			board[square] = color;
			emHead->next = next->next;
			int max_mobility = count_mobility(board, oppcolor);
			CGameScript::UndoFlips(board, flipCount, oppcolor);
			emHead->next = next;
			board[square] = EMPTY;
			emptiesArray[index] = next;
			MobilityArray[index] = -max_mobility;
			index++;
		}
		emHead = next;
		next = next->next;
	}
	if (index != 0){
		for (int i = 0; i < index; i++){
			int num10 = MobilityArray[i];
			int num11 = i;
			int num2 = i + 1;
			while (num2 < index){
				if (MobilityArray[num2] > num10){
					num10 = MobilityArray[num2];
					num11 = num2;
				}
				num2++;
			}
			next = emptiesArray[num11];
			emptiesArray[num11] = emptiesArray[i];
			MobilityArray[num11] = MobilityArray[i];
			square = next->Square;
			//int holeId = next->HoleID;
			num2 = CGameScript::DoFlips(board, square, color, oppcolor);
			board[square] = color;
			next->prev->next = next->next;
			if (next->next != NULL)
				next->next->prev = next->prev;
			nodes++;
			int num6 = -eval.StaEval2(board, oppcolor, color, empties - 1, &EmHead);
			CGameScript::UndoFlips(board, num2, oppcolor);
			board[square] = EMPTY;
			next->prev->next = next;
			if (next->next != NULL)
				next->next->prev = next;
			if (num6 > curMaxEval){
				curMaxEval = num6;
				if (num6 > alpha){
					if (num6 >= beta)
						return curMaxEval;
					alpha = num6;
				}
			}
		}
	}else{
		if (prevmove == 0){
			if (discdiff > 0) return 0x5f5e100;
			if (discdiff < 0) return -100000000;
			return 0;
		}
		nodes++;
		m_pEng->ReportTrace(square, ++curDepth);
		curMaxEval=-QuiescenceSolve(board, -beta, -alpha, oppcolor, depth, empties, -discdiff, 0);
		curDepth--;
		return curMaxEval;
	}
	return (((2 * curEval) + curMaxEval) / 3);
}

int CArtStaSolve::RootStaSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove){
	int square, index = 0, curMaxEval = -100000001;
	ChessType oppcolor = Oppl_ch(color);
	Empties* emptiesArray[0x40];
	int MobilityArray[0x40];
	bool flag = false;
	Empties* emHead = &EmHead;
	Empties* next = emHead->next;
	while (next != NULL){
		square = next->Square;
		int flipCount = CGameScript::DoFlips(board, square, color, oppcolor);
		if (flipCount > 0){
			board[square] = color;
			emHead->next = next->next;
			MobilityArray[index] = -count_mobility(board, oppcolor);
			CGameScript::UndoFlips(board, flipCount, oppcolor);
			board[square] = EMPTY;
			emptiesArray[index] = next;
			emHead->next = next;
			index++;
		}
		emHead = next;
		next = next->next;
	}
	if (index != 0){
		for (int i = 0; i < index; i++){
			int curResult, num10 = i, num2 = i + 1, max_mobility = MobilityArray[i];
			while (num2 < index){
				if (MobilityArray[num2] > max_mobility){
					max_mobility = MobilityArray[num2];
					num10 = num2;
				}
				num2++;
			}
			next = emptiesArray[num10];
			emptiesArray[num10] = emptiesArray[i];
			MobilityArray[num10] = MobilityArray[i];
			square = next->Square;
//			int holeId = next->HoleID;
			num2 = CGameScript::DoFlips(board, square, color, oppcolor);
			board[square] = color;

			next->prev->next = next->next;
			if (next->next != NULL)
				next->next->prev = next->prev;

			nodes++;
			m_pEng->ReportTrace(square, ++curDepth);
			if (flag){
				curResult = -FastestFirstSolve(board, -alpha - 1, -alpha, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * num2)) - 1, square);
				if ((curResult > alpha) && (curResult < beta))
					curResult = -FastestFirstSolve(board, -beta, -curResult, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * num2)) - 1, square);
			}else
				curResult = -FastestFirstSolve(board, -beta, -alpha, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * num2)) - 1, square);
			curDepth--;
			CGameScript::UndoFlips(board, num2, oppcolor);
			board[square] = EMPTY;
			next->prev->next = next;
			if (next->next != NULL)
				next->next->prev = next;

			if (curResult > curMaxEval){
				curMaxEval = curResult;
				bestMove = square;
				m_pEng->ReportTrace(square, 255);//report best
				if (curResult > alpha){
					if (curResult >= beta)
						return curMaxEval;
					alpha = curResult;
					flag = true;
				}
			}
		}
	}else{
		m_pEng->ReportTrace(square, ++curDepth);
		curMaxEval = -FastestFirstSolve(board, -beta, -alpha, oppcolor, depth, empties, -discdiff, 0);
		curDepth--;
		if (depth == searchDepth)
			bestMove = 0;
	}
	return curMaxEval;

}

double CArtStaSolve::Solve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove){
	nodes = 0;

	m_bSearchContinue=true;
	curDepth=0;
	double num = RootStaSolve(board, alpha, beta, color, searchDepth, empties, discdiff, prevmove);
	num /= 100.0;
	if (num <= 64.0)
		return num;
	return 64.0;
}
