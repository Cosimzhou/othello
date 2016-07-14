// BaseSolve.cpp: implementation of the CArtBaseSolve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "ArtBaseSolve.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



const int CArtBaseSolve::worst2best[64] ={ 
			20, 0x19, 0x41, 70, 11, 0x10, 0x13, 0x1a, 0x40, 0x47, 0x4a, 0x4f, 0x15, 0x18, 0x1d, 0x22, 
			0x38, 0x3d, 0x42, 0x45, 0x16, 0x17, 0x26, 0x2b, 0x2f, 0x34, 0x43, 0x44, 0x1f, 0x20, 0x27, 0x2a, 
			0x30, 0x33, 0x3a, 0x3b, 13, 14, 0x25, 0x2c, 0x2e, 0x35, 0x4c, 0x4d, 30, 0x21, 0x39, 60, 
			12, 15, 0x1c, 0x23, 0x37, 0x3e, 0x4b, 0x4e, 10, 0x11, 0x49, 80, 40, 0x29, 0x31, 50
		 };


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArtBaseSolve::CArtBaseSolve()
{
	bestMove = 0;
	nodes = 0;
	searchDepth= 6;
}

CArtBaseSolve::~CArtBaseSolve()
{

}

int CArtBaseSolve::count_mobility(ChessType* board, ChessType color) const
{	//可落子的格数
	int num = 0;
	for(Empties* empties = EmHead.next; empties != NULL; empties = empties->next)
		if (CGameScript::CountAnyFlip(empties->Square, color, board))	num++;
	return num;
}

void CArtBaseSolve::PrepareToSolve(ChessType* board){
	unsigned int a = 1;
	int index = 10;
	while (index <= 80){
		if (board[index] == EMPTY){
			if (board[index - 10] == EMPTY)
				HoleID[index] = HoleID[index - 10];
			else if (board[index - 9] == EMPTY)
				HoleID[index] = HoleID[index - 9];
			else if (board[index - 8] == EMPTY)
				HoleID[index] = HoleID[index - 8];
			else if (board[index - 1] == EMPTY)
				HoleID[index] = HoleID[index - 1];
			else{
				HoleID[index] = a;  a <<= 1;
			}
		}else
			HoleID[index] = 0;
		index++;
	}
	for (int i = 1; i > 0; i--){
		index = 80;
		while (index >= 10){
			if (board[index] == EMPTY){
				a = HoleID[index];
				if (board[index + 10] == EMPTY)
					HoleID[index] = (a>HoleID[index + 10]? HoleID[index + 10]: a);
				if (board[index + 9] == EMPTY)
					HoleID[index] = (a>HoleID[index + 9]? HoleID[index + 9]: a);
				if (board[index + 8] == EMPTY)
					HoleID[index] = (a>HoleID[index + 8]? HoleID[index + 8]: a);
				if (board[index + 1] == EMPTY)
					HoleID[index] = (a>HoleID[index + 1]? HoleID[index + 1]: a);
			}
			index--;
		}
		index = 10;
		while (index <= 80){
			if (board[index] == EMPTY){
				a = HoleID[index];
				if (board[index - 10] == EMPTY)
					HoleID[index] = (a>HoleID[index - 10]? HoleID[index - 10]: a);
				if (board[index - 9] == EMPTY)
					HoleID[index] = (a>HoleID[index - 9]? HoleID[index - 9]: a);
				if (board[index - 8] == EMPTY)
					HoleID[index] = (a>HoleID[index - 8]? HoleID[index - 8]: a);
				if (board[index - 1] == EMPTY)
					HoleID[index] = (a>HoleID[index - 1]? HoleID[index - 1]: a);
			}
			index++;
		}
	}
	a = 0;
	Empties* emHead = &EmHead;
	for (index = 0x3b; index >= 0; index--)	{
		int num2 = worst2best[index];
		if (board[num2] == EMPTY){
			emHead->next = &EmList[a];
			EmList[a++].prev = emHead;
			emHead = emHead->next;
			emHead->Square = num2;
			emHead->HoleID = HoleID[num2];
		}
		emHead->next = NULL;
	}
}

int CArtBaseSolve::BestMove() const{
	return bestMove;
}
int CArtBaseSolve::Nodes() const{
	return nodes;
}

void CArtBaseSolve::StopSearch()
{
	m_bSearchContinue=false;
}
