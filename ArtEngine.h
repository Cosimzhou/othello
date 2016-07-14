// Engine.h: interface for the CArtEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENGINE_H__D0602D6B_0A27_4088_8735_99C248D12161__INCLUDED_)
#define AFX_ENGINE_H__D0602D6B_0A27_4088_8735_99C248D12161__INCLUDED_

#include "EngineMother.h"
#include "ArtMidSolve.h"
#include "ArtStaSolve.h"
#include "ArtEndSolve.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArtEngine  : public CEngineMother
{
public:
	CArtEngine();
	virtual ~CArtEngine();

private:
	CArtMidSolve m_MidSolve;
	CArtStaSolve m_StaSolve;
	CArtEndSolve m_EndSolve;

public:
	void StopSearch();
	static int MidDepth;
	static int endDepth;
	static int emptiesOfStartGame;
	void SetAI(int ai);
	void Search(ChessType* curboard, ChessType col);
};

#endif // !defined(AFX_ENGINE_H__D0602D6B_0A27_4088_8735_99C248D12161__INCLUDED_)
