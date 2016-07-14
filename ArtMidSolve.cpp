// MidSolve.cpp: implementation of the CArtMidSolve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "ArtMidSolve.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const int CArtMidSolve::MidBetterScore = 0x708;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArtMidSolve::CArtMidSolve()
{
}

CArtMidSolve::~CArtMidSolve()
{
}

int CArtMidSolve::FastestFirstSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove){
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
	Empties* emNext = emHead->next;
	while (emNext != NULL){
		square = emNext->Square;
		int flipCount = CGameScript::DoFlips(board, square, color, oppcolor);
		if (flipCount > 0){
			board[square] = color;
			emHead->next = emNext->next;
			MobilityArray[index]= -count_mobility(board, oppcolor);
			CGameScript::UndoFlips(board, flipCount, oppcolor);
			emHead->next = emNext;
			board[square] = EMPTY;
			emptiesArray[index] = emNext;
			index++;
		}
		emHead = emNext;
		emNext = emNext->next;
	}
	if (index != 0){
		for (int i = 0; i < index; i++){
			int num5;
			int num9 = MobilityArray[i];
			int num10 = i;
			int flipsCounter = i + 1;
			while (flipsCounter < index){
				if (MobilityArray[flipsCounter] > num9){
					num9 = MobilityArray[flipsCounter];
					num10 = flipsCounter;
				}
				flipsCounter++;
			}
			emNext = emptiesArray[num10];
			emptiesArray[num10] = emptiesArray[i];
			MobilityArray[num10] = MobilityArray[i];
			square = emNext->Square;
//				int holeId = emNext->HoleId;
			flipsCounter = CGameScript::DoFlips(board, square, color, oppcolor);
			board[square] = color;
			emNext->prev->next = emNext->next;
			if (emNext->next != NULL)
				emNext->next->prev = emNext->prev;
			nodes++;
			if(m_bSearchContinue){
				m_pEng->ReportTrace(square, ++curDepth);

				if (flag){
					num5 = -FastestFirstSolve(board, -alpha - 1, -alpha, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * flipsCounter)) - 1, square);
					if ((num5 > alpha) && (num5 < beta))
						num5 = -FastestFirstSolve(board, -beta, -num5, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * flipsCounter)) - 1, square);
				}else
					num5 = -FastestFirstSolve(board, -beta, -alpha, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * flipsCounter)) - 1, square);
				curDepth--;
			}
			CGameScript::UndoFlips(board, flipsCounter, oppcolor);
			board[square] = EMPTY;
			emNext->prev->next = emNext;
			if (emNext->next != NULL)
				emNext->next->prev = emNext;
			if (num5 > curMaxEval){
				curMaxEval = num5;
				if (num5 > alpha){
					if (num5 >= beta)
						return curMaxEval;
					alpha = num5;
					flag = true;
				}
			}
		}
	}else{
		if (prevmove == 0){
			if (discdiff > 0)
				return 0x5f5e100;
			if (discdiff < 0)
				return -100000000;
			return 0;
		}
		curMaxEval = -FastestFirstSolve(board, -beta, -alpha, oppcolor, depth, empties, -discdiff, 0);
	}
	return curMaxEval;

}

int CArtMidSolve::QuiescenceSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove){
	int square;
	int curMaxEval = -100000000;
	ChessType oppcolor = Oppl_ch(color);
	Empties* emptiesArray[0x40];
	int MobilityArray[0x40];
	ASSERT(!(empties>60||empties<0));
	int curEval = eval.MidEval2(board, color, oppcolor, empties, &EmHead);
	if (((curEval >= beta) || (curEval >= 0xbb8)) || (depth == 0))
		return curEval;
	if (curEval > alpha)
		alpha = curEval;
	int index = 0;
	Empties* emHead = &EmHead;
	Empties* emNext = emHead->next;
	while (emNext != NULL){
		square = emNext->Square;
		int flipCount = CGameScript::DoFlips(board, square, color, oppcolor);
		if (flipCount > 0){
			board[square] = color;
			emHead->next = emNext->next;
			int num9 = count_mobility(board, oppcolor);
			CGameScript::UndoFlips(board, flipCount, oppcolor);
			emHead->next = emNext;
			board[square] = EMPTY;
			emptiesArray[index] = emNext;
			MobilityArray[index] = -num9;
			index++;
		}
		emHead = emNext;
		emNext = emNext->next;
	}
	if (index != 0){
		for (int i = 0; i < index; i++){
			int num10 = MobilityArray[i];
			int num11 = i;
			int flipsCounter = i + 1;
			while (flipsCounter < index){
				if (MobilityArray[flipsCounter] > num10){
					num10 = MobilityArray[flipsCounter];
					num11 = flipsCounter;
				}
				flipsCounter++;
			}
			emNext = emptiesArray[num11];
			emptiesArray[num11] = emptiesArray[i];
			MobilityArray[num11] = MobilityArray[i];
			square = emNext->Square;
//				int holeId = emNext->HoleId;
			flipsCounter = CGameScript::DoFlips(board, square, color, oppcolor);
			board[square] = color;
			emNext->prev->next = emNext->next;
			if (emNext->next != NULL)
				emNext->next->prev = emNext->prev;
			nodes++;
			ASSERT(!(empties>60||empties<1));
			int num6 = -eval.MidEval2(board, oppcolor, color, empties - 1, &EmHead);
			CGameScript::UndoFlips(board, flipsCounter, oppcolor);
			board[square] = EMPTY;
			emNext->prev->next = emNext;
			if (emNext->next != NULL)
				emNext->next->prev = emNext;
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
			if (discdiff > 0)
				return 0x5f5e100;
			if (discdiff < 0)
				return -100000000;
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

int CArtMidSolve::RootMidSolve(ChessType* board, int alpha, int beta, ChessType color, int depth, int empties, int discdiff, int prevmove){
	int square, curMaxEval = -100000001;
	ChessType oppcolor = Oppl_ch(color);
	Empties* emptiesArray[0x40];
	int MobilityArray[0x40];
	bool flag = false;
	int index = 0;
	Empties* emHead = &EmHead;
	Empties* emNext = emHead->next;
	while (emNext != NULL){
		square = emNext->Square;
		int flipCount = CGameScript::DoFlips(board, square, color, oppcolor);
		if (flipCount > 0){
			board[square] = color;
			emHead->next = emNext->next;
			MobilityArray[index] = -count_mobility(board, oppcolor);
			CGameScript::UndoFlips(board, flipCount, oppcolor);
			emHead->next = emNext;
			board[square] = EMPTY;
			emptiesArray[index] = emNext;
			index++;
		}
		emHead = emNext;
		emNext = emNext->next;
	}
	if (index != 0){
		for (int i = 0; i < index; i++){
			int num5;
			int num9 = MobilityArray[i];
			int num10 = i;
			int flipsCounter = i + 1;
			while (flipsCounter < index){
				if (MobilityArray[flipsCounter] > num9){
					num9 = MobilityArray[flipsCounter];
					num10 = flipsCounter;
				}
				flipsCounter++;
			}
			emNext = emptiesArray[num10];
			emptiesArray[num10] = emptiesArray[i];
			MobilityArray[num10] = MobilityArray[i];
			square = emNext->Square;
			//int holeId = emNext->HoleId;
			flipsCounter = CGameScript::DoFlips(board, square, color, oppcolor);
			board[square] = color;
			emNext->prev->next = emNext->next;
			if (emNext->next != NULL)
				emNext->next->prev = emNext->prev;
			nodes++;
			m_pEng->ReportTrace(square, ++curDepth);
			if (flag){
				num5 = -FastestFirstSolve(board, -alpha - 1, -alpha, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * flipsCounter)) - 1, square);
				if ((num5 > alpha) && (num5 < beta))
					num5 = -FastestFirstSolve(board, -beta, -num5, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * flipsCounter)) - 1, square);
			}else
				num5 = -FastestFirstSolve(board, -beta, -alpha, oppcolor, depth - 1, empties - 1, (-discdiff - (2 * flipsCounter)) - 1, square);
			CGameScript::UndoFlips(board, flipsCounter, oppcolor);
			board[square] = EMPTY;
			curDepth--;
			emNext->prev->next = emNext;
			if (emNext->next != NULL)
				emNext->next->prev = emNext;
			if (num5 > curMaxEval){
				curMaxEval = num5;
				bestMove = square;
				m_pEng->ReportTrace(square, 255);//report best
				if (num5 > alpha){
					if (num5 >= beta)
						return curMaxEval;
					alpha = num5;
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

double CArtMidSolve::Solve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove){
	nodes = 0;
	m_bSearchContinue=true;
	curDepth=0;
	double num = RootMidSolve(board, alpha, beta, color, searchDepth, empties, discdiff, prevmove);
	num /= 100.0;
	if (num > 64.0)
		return 64.0;
	if (num < -64.0)
		return -64.0;
	return num;
}

