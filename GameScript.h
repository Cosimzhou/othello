// GameScript.h: interface for the CGameScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMESCRIPT_H__076C68B2_218F_474E_B68F_07003CB4EB39__INCLUDED_)
#define AFX_GAMESCRIPT_H__076C68B2_218F_474E_B68F_07003CB4EB39__INCLUDED_

#include "Othello.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGameScript  
{
public:
	void StartClean();
	CGameScript();
	virtual ~CGameScript();

//	namespace  {
	static ChessType WinPlayer(ChessType* Mapt);	//获胜方

	static bool AnyPotMobility(ChessType* board, int sqnum, ChessType oppcolor);	//潜在行动力
	static int CountChess(ChessType* Mapt, ChessType Player);		//数Player色的棋子
	static void CountChess(ChessType* Mapt, short* ret);			//数双方棋子
	static int CountAnyFlip(int pos, ChessType PlayerColor, ChessType* Mapt);	//数翻转数
	static int CountLocablePt(ChessType PlayerColor, ChessType* Mapt);			//数可落子点
	static int DoLoc(int pos, ChessType PlayerColor, ChessType* Mapt, short*& FlipStack);	//落子
	static int DoFlips(ChessType* board, int sqnum, ChessType color, ChessType oppcolor);	//翻转
	static int FindLocablePt(ChessType PlayerColor, ChessType* Mapt);		//查找一个可落子点
	static int FindLocablePt(ChessType PlayerColor, ChessType* Mapt, int* output);	//查找可落子点
	static int GenerateLoc(ChessType PlayerColor, ChessType* Mapt, FlipSpot* vp);		//生成行棋点
	static bool IsLocable(int pos, ChessType PlayerColor, ChessType* Mapt);		//判断可落子
	static bool IsGameOver(ChessType* Mapt);	//判断游戏结束
	static bool IsStab(ChessType* board, int sqnum, ChessType color);	//判断稳定子
	static void UndoFlips(ChessType* board, int flipCount, ChessType oppcolor);	//反翻转
	const static int DrctInc[8];
	const static unsigned __int8 CanSchInDrct[8];
	const static unsigned __int8 QuickDirMask[CH_LEN];
//	}GameScript;
protected:
	static int DrctnlStab(ChessType* board, int boardIndex, int inc, ChessType color);
	static int DrctnlFlips(ChessType* board, ChessType* sq, int inc, ChessType color, ChessType oppcolor);
	static int DirectLoc(ChessType *sq, ChessType* Mapt, int inc, ChessType color, ChessType oppcol, short*& FlipStack);
	static int DirectLoc(ChessType *sq, int inc, ChessType color, ChessType oppcol);
	volatile static BYTE m_FlipStack[1000];
	volatile static BYTE* m_FlipTop;
};

#endif // !defined(AFX_GAMESCRIPT_H__076C68B2_218F_474E_B68F_07003CB4EB39__INCLUDED_)
