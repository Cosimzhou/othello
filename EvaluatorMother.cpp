// EvaluatorMother.cpp: implementation of the CEvaluatorMother class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "EvaluatorMother.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvaluatorMother::CEvaluatorMother()
{

}

CEvaluatorMother::~CEvaluatorMother()
{

}

int CEvaluatorMother::FinalScore(ChessType* board, ChessType color) const
{
	short cnter[2];
	short empties;
	CGameScript::CountChess(board, cnter);
	int tmpEval = cnter[0]-cnter[1];
	empties=64-cnter[0]-cnter[1];
	tmpEval *= (color==B_CH? 1: -1);
    if(tmpEval > 0)
        return (32000 + tmpEval + empties);
    if(tmpEval < 0)
        return (-32000 + tmpEval - empties);
    else
        return 0;
}
