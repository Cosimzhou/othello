// EndSolve.cpp: implementation of the CArtEndSolve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "ArtEndSolve.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int CArtEndSolve::highestScore = 0x5f5e100;
const bool CArtEndSolve::WINNER_GETS_EMPTIES = true;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArtEndSolve::CArtEndSolve()
{

}

CArtEndSolve::~CArtEndSolve()
{

}

int CArtEndSolve::FastestFirstEndSolve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove){
	int square = -1, index = 0, curMaxEval = -100000000;
	int MobilityArray[0x40];
	ChessType oppcolor = Oppl_ch(color);
	Empties* emptiesArray[0x40];
	Empties* emHead = &EmHead;
	Empties* emNext = emHead->next;
	while (emNext != NULL){
		nodes++;
		square = emNext->Square;
		int flipCount = CGameScript::DoFlips(board, square, color, oppcolor);
		if (flipCount > 0){
			board[square] = color;
			emHead->next = emNext->next;
			int Mobility = count_mobility(board, oppcolor);
			CGameScript::UndoFlips(board, flipCount, oppcolor);
			emHead->next = emNext;
			board[square] = EMPTY;
			emptiesArray[index] = emNext;
			MobilityArray[index] = -Mobility;
			index++;
		}
		emHead = emNext;
		emNext = emNext->next;
	}
	if (index != 0){
		for (int i = 0; i < index; i++){
			int tmpEval, maxMobility = MobilityArray[i], maxMobilityIndex = i, j = i + 1;
			while (j < index){
				if (MobilityArray[j] > maxMobility){
					maxMobility = MobilityArray[j];
					maxMobilityIndex = j;
				}
				j++;
			}
			emNext = emptiesArray[maxMobilityIndex];
			emptiesArray[maxMobilityIndex] = emptiesArray[i];
			MobilityArray[maxMobilityIndex] = MobilityArray[i];
			square = emNext->Square;
			int holeId = emNext->HoleID;
			j = CGameScript::DoFlips(board, square, color, oppcolor);///////////////////////////////////
			board[square] = color;
			RegionParity ^= (unsigned int) holeId;
			emNext->prev->next = emNext->next;
			if (emNext->next != NULL)
				emNext->next->prev = emNext->prev;
			if(m_bSearchContinue){
				m_pEng->ReportTrace(square, ++curDepth);
				if (empties <= 8)
					tmpEval = -ParEndSolve(board, -beta, -alpha, oppcolor, empties - 1, (-discdiff - (2 * j)) - 1, square);
				else
					tmpEval = -FastestFirstEndSolve(board, -beta, -alpha, oppcolor, empties - 1, (-discdiff - (2 * j)) - 1, square);
				curDepth--;
			}
			CGameScript::UndoFlips(board, j, oppcolor);
			RegionParity ^= (unsigned int) holeId;
			board[square] = EMPTY;
			emNext->prev->next = emNext;
			if (emNext->next != NULL)
				emNext->next->prev = emNext;
			if (tmpEval > curMaxEval){
				curMaxEval = tmpEval;
				if (empties == searchDepth){
					bestMove = square;
					m_pEng->ReportTrace(square, 255);//report best
				}
				if (tmpEval > alpha){
					if (tmpEval >= beta)
						return curMaxEval;
					alpha = tmpEval;
				}
			}
		}
		return curMaxEval;
	}
	if (prevmove == 0){
		if (discdiff > 0)
			return (discdiff + empties);
		if (discdiff < 0)
			return (discdiff - empties);
		return 0;
	}
	m_pEng->ReportTrace(square, ++curDepth);
	curMaxEval = -FastestFirstEndSolve(board, -beta, -alpha, oppcolor, empties, -discdiff, 0);
	curDepth--;
	if (empties == searchDepth)
		bestMove = 0;
	return curMaxEval;
}

int CArtEndSolve::NoParEndSolve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove){
	int curMaxEval = -100000000;
	ChessType oppcolor = Oppl_ch(color);
	int square = -1;
	nodes++;
	Empties *emHead = &EmHead;
	for (Empties* empties2 = emHead->next; empties2 != NULL; empties2 = empties2->next){
		square = empties2->Square;
		int flipCount = CGameScript::DoFlips(board, square, color, oppcolor);
		if (flipCount > 0){
			int result;
			board[square] = color;
			emHead->next = empties2->next;

			if (empties == 2){
				int cnter = CGameScript::CountAnyFlip(EmHead.next->Square, oppcolor, board);
				if (cnter > 0)
					result = discdiff + (2 * (flipCount - cnter));
				else{
					cnter = CGameScript::CountAnyFlip(EmHead.next->Square, color, board);
					result = discdiff + (2 * flipCount);
					if (cnter > 0)
						result += 2 * (cnter + 1);
					else if (result >= 0)
						result += 2;
				}
			}else{
				m_pEng->ReportTrace(square, ++curDepth);
				result = -NoParEndSolve(board, -beta, -alpha, oppcolor, empties - 1, (-discdiff - (2 * flipCount)) - 1, square);
				curDepth--;
			}

			CGameScript::UndoFlips(board, flipCount, oppcolor);
			board[square] = EMPTY;
			emHead->next = empties2;

			if (result > curMaxEval){
				curMaxEval = result;
				if (empties == searchDepth){
					bestMove = square;
					m_pEng->ReportTrace(square, 255);//report best
				}
				if (result > alpha){
					if (result >= beta)
						return curMaxEval;
					alpha = result;
				}
			}
		}
		emHead = empties2;
	}
	if (curMaxEval != -100000000)
		return curMaxEval;
	if (empties == searchDepth)
		bestMove = 0;
	if (prevmove != 0){
		m_pEng->ReportTrace(square, ++curDepth);
		curMaxEval=-NoParEndSolve(board, -beta, -alpha, oppcolor, empties, -discdiff, 0);
		curDepth--;
		return curMaxEval;
	}
	if (discdiff > 0)
		return (discdiff + empties);
	if (discdiff < 0)
		return (discdiff - empties);
	return 0;
}

int CArtEndSolve::ParEndSolve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove){
	int square = -1, num6 = 1, curMaxEval = -100000000;
	ChessType oppcolor = Oppl_ch(color);
	nodes++;

	for (unsigned int i = RegionParity; num6 >= 0; i = ~i){
		Empties* emHead = &EmHead;
		for (Empties* empties2 = emHead->next; empties2 != NULL; empties2 = empties2->next){
			int holeId = empties2->HoleID;
			//holeId = empties2->Square;
			//holeId = empties2->HoleID;
			square = empties2->Square;
			int flipCount = CGameScript::DoFlips(board, square, color, oppcolor);
			if (flipCount > 0){
				int result;
				board[square] = color;
				RegionParity ^= (unsigned int) holeId;
				emHead->next = empties2->next;

				m_pEng->ReportTrace(square, ++curDepth);
				if (empties <= 5)
					result = -NoParEndSolve(board, -beta, -alpha, oppcolor, empties - 1, (-discdiff - (2 * flipCount)) - 1, square);
				else
					result = -ParEndSolve(board, -beta, -alpha, oppcolor, empties - 1, (-discdiff - (2 * flipCount)) - 1, square);
				curDepth--;
			
				CGameScript::UndoFlips(board, flipCount, oppcolor);
				RegionParity ^= (unsigned int) holeId;
				board[square] = EMPTY;
				emHead->next = empties2;
				
				if (result > curMaxEval) {
					curMaxEval = result;
					if (empties == searchDepth){
						bestMove = square;
						m_pEng->ReportTrace(square, 255);//report best
					}
					if (result > alpha){
						if (result >= beta)
							return curMaxEval;
						alpha = result;
					}
				}
			}
			emHead = empties2;
		}
		num6--;
	}
	if (curMaxEval != -100000000)
		return curMaxEval;
	if (empties == searchDepth)
		bestMove = 0;
	if (prevmove != 0){
		m_pEng->ReportTrace(square, ++curDepth);
		curMaxEval=-ParEndSolve(board, -beta, -alpha, oppcolor, empties, -discdiff, 0);
		curDepth--;

		return curMaxEval;
	}
	if (discdiff > 0)
		return (discdiff + empties);
	if (discdiff < 0)
		return (discdiff - empties);
	return 0;
}

double CArtEndSolve::Solve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove){
	RegionParity = 0;
	for (int i = 10; i <= 80; i++){
		RegionParity ^= HoleID[i];
	}
	searchDepth = empties;
	m_bSearchContinue=true;
	nodes = 0;
	curDepth=0;
	if (empties > 7)
		return FastestFirstEndSolve(board, alpha, beta, color, empties, discdiff, prevmove);
	if (empties <= 4)
		return NoParEndSolve(board, alpha, beta, color, empties, discdiff, prevmove);
	return ParEndSolve(board, alpha, beta, color, empties, discdiff, prevmove);
}



