// ComputerThink.h: interface for the CComputerThink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPUTERTHINK_H__537F0B98_DCFF_45D3_920F_9118410CE6FC__INCLUDED_)
#define AFX_COMPUTERTHINK_H__537F0B98_DCFF_45D3_920F_9118410CE6FC__INCLUDED_

#include "game.h"
#include "EngineMother.h"	// Added by ClassView
#include "OpeningReader.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComputerThink  
{
public:
	bool GetPause();
	void PauseGame();
	void EndThinking();
	void StartToThink();
	void SetUseBook(bool);
	void StopSearch();
	void SetOwner(HWND hwnd);
	bool SetStyle(int*);
	void SetGame(CGame*);
	void SetTimeLimit(int);
	void SetOpeningReader(COpeningReader*);
	CComputerThink();
	virtual ~CComputerThink();

private:
	HWND m_Owner;
	HANDLE m_hAIThread;
	HANDLE m_hTimeThread;

	COpeningReader* m_pOR;
	CGame* m_pG;
	int m_Player[2];
	char m_PlayColor;
	CEngineMother* m_Eng[2];
	const static char m_EngMap[ENGINE_NUM];
	const static int m_EngAI[6];

protected:
	bool m_UseBook;
	int m_InUse;
	int m_iTimeLimit;
	bool m_DonotEcho;
	void MakeDecision();
	static HANDLE m_hXLock;
	static int m_RLockCount;
	static bool m_CSInited;
	static CRITICAL_SECTION m_CS;
	static DWORD WINAPI AIThreadFunc(LPVOID lpParam);
	static DWORD WINAPI TimeLimitThreadFunc(LPVOID lpParam);
};

#endif // !defined(AFX_COMPUTERTHINK_H__537F0B98_DCFF_45D3_920F_9118410CE6FC__INCLUDED_)
