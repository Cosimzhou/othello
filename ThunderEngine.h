// ThunderEngine.h: interface for the CThunderEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THUNDERENGINE_H__BDFAE64A_FAAB_47D3_BD18_CAF8C6655460__INCLUDED_)
#define AFX_THUNDERENGINE_H__BDFAE64A_FAAB_47D3_BD18_CAF8C6655460__INCLUDED_

#include "EngineMother.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CThunderEngine  : public CEngineMother
{
public:
	void Search(ChessType* curboard, ChessType col);
	void SetAI(int ai);
	bool IsAvalible();
	CThunderEngine();
	virtual ~CThunderEngine();

protected:
	int m_iTmpBestScore;
	void Translate(ChessType* map);
	int m_board[X_UB][Y_UB];
	int (__stdcall *MidSolve)(int*, int, int, int, int, int*);
	int (__stdcall *EndSolve)(int*, int, int, int, int, int, int, int*);
	void (__stdcall *hash_init)(int);
	void(__stdcall*SetTimeOut)(void);
	HINSTANCE m_hEngine;
};

#endif // !defined(AFX_THUNDERENGINE_H__BDFAE64A_FAAB_47D3_BD18_CAF8C6655460__INCLUDED_)
