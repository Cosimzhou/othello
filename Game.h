// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__8DDD382A_B024_4441_ADD7_39A3AC94C49B__INCLUDED_)
#define AFX_GAME_H__8DDD382A_B024_4441_ADD7_39A3AC94C49B__INCLUDED_

#include "GameScript.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MARK_KEYWORD		0x70716f

typedef struct {
	double time;
	double value;
	long nodes;
	short bw[2];
	short innerbw[2];
	short best;
	BYTE color;
}SearchReport;

class CGame  
{
public:
	void EndGame();
	void GetSearchReport(SearchReport*) const;
	bool m_bDynamicShow;
	bool m_PlaySound;
	bool m_bEnd;
	bool Redo();
	bool Undo();
	int GetLocTraceTop() const;
	int GetColor() const;
	int GetGameState() const;
	void SetAnimation(bool a);
	void GetChessCount(short* ret) const;
	short* GetLocTrace(int &len) const;
	void OpeningGame(char*);		//Text Rebuild board
	bool RebuildGame(const char*);	//Open save document
	bool SaveGame(const char*) const;		//Save document

	void SetComputerSide(int*);		//Computer action
	void SetOwner(HWND);			//Set Owner's HANDLE
	void StartGame();				//Start New Game
	bool EchoClick(int pos, char c=0);

	CGame();
	virtual ~CGame();
	friend class CGraphic;		//class CGraphic is CGame's friend
	friend class CComputerThink;//class CComputerThink is CGame's friend

protected:
	bool BuildGame(short*);
	bool InnerLoc(ChessType* map, int pos, ChessType *col, int cs, short *&FlipTp, short *&pFlip, LPARAM* &lp, WPARAM* &wp);
	short m_FlipHistory[1000];	//stack to store the squares where be flipped
	short*m_FlipHistoryTop;		// the top of stack m_FlipHistory
	short m_FlipSec[60];	// stack to store division of stack m_FlipHistory
	short* m_FlipSecTop;		// the top of stack m_FlipSec
	short m_LocHistory[60];
	short* m_LocTop;
	short* m_LocMaxTop;
	int m_CurLoc;	//the square where located last
	CGameScript m_GS;	// the set of othello game rules
	bool m_ComputerAct[2];
	int m_B2W;
	int m_BlackLoc;
	int m_GameState;
	int m_HintPt[32];	// queue to store the hint points
	int m_HintCounter;		// counter for queue m_HintPt
	ChessType m_map[CH_LEN];	// the board of othello game

private:
	HWND m_Owner;
	SearchReport m_SReport[60];

	__inline void ClearBoard(ChessType *map);
	__inline void Statistics() const;
	__inline void ListStep(int pos, int i, char Player) const;
	__inline void GameOver();

	const static ChessType Init_Board[CH_LEN];
};

#endif // !defined(AFX_GAME_H__8DDD382A_B024_4441_ADD7_39A3AC94C49B__INCLUDED_)
