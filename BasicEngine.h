// BasicEngine.h: interface for the CBasicEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASICENGINE_H__6EA72D99_B11C_44BB_A7C5_984012E2A456__INCLUDED_)
#define AFX_BASICENGINE_H__6EA72D99_B11C_44BB_A7C5_984012E2A456__INCLUDED_

#include "EngineMother.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBasicEngine  :public CEngineMother
{
public:
	CBasicEngine();
	virtual ~CBasicEngine();

public:
	void Search(ChessType* curboard, ChessType col);
	void SetAI(int ai);
private:
	void (CBasicEngine::*m_AIFunc)(ChessType*, ChessType);
	void (CBasicEngine::*m_AIFuncArr[5])(ChessType*, ChessType);
	void StabEvaluate(ChessType* board, ChessType color);
	void StaticEvaluate(ChessType *board, ChessType color);
	void MobilityPrior(ChessType *board, ChessType color);
	void RandomScheme(ChessType* board, ChessType color);
	void EatMost(ChessType* board, ChessType color);
	int m_AI;
	const static int Eval_map[CH_LEN];
};

#endif // !defined(AFX_BASICENGINE_H__6EA72D99_B11C_44BB_A7C5_984012E2A456__INCLUDED_)
