// EvaluatorMother.h: interface for the CEvaluatorMother class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVALUATORMOTHER_H__ACF43AEF_2A93_4D73_896C_CA1CFD7883C3__INCLUDED_)
#define AFX_EVALUATORMOTHER_H__ACF43AEF_2A93_4D73_896C_CA1CFD7883C3__INCLUDED_

#include "GameScript.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEvaluatorMother  
{
public:
	CEvaluatorMother();
	virtual ~CEvaluatorMother();
	virtual int Evaluate(ChessType* curboard, ChessType col, int empties=-1, bool end=false)=0;

protected:
	int FinalScore(ChessType* board, ChessType color) const;
};

#endif // !defined(AFX_EVALUATORMOTHER_H__ACF43AEF_2A93_4D73_896C_CA1CFD7883C3__INCLUDED_)
