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
	static ChessType WinPlayer(ChessType* Mapt);	//��ʤ��

	static bool AnyPotMobility(ChessType* board, int sqnum, ChessType oppcolor);	//Ǳ���ж���
	static int CountChess(ChessType* Mapt, ChessType Player);		//��Playerɫ������
	static void CountChess(ChessType* Mapt, short* ret);			//��˫������
	static int CountAnyFlip(int pos, ChessType PlayerColor, ChessType* Mapt);	//����ת��
	static int CountLocablePt(ChessType PlayerColor, ChessType* Mapt);			//�������ӵ�
	static int DoLoc(int pos, ChessType PlayerColor, ChessType* Mapt, short*& FlipStack);	//����
	static int DoFlips(ChessType* board, int sqnum, ChessType color, ChessType oppcolor);	//��ת
	static int FindLocablePt(ChessType PlayerColor, ChessType* Mapt);		//����һ�������ӵ�
	static int FindLocablePt(ChessType PlayerColor, ChessType* Mapt, int* output);	//���ҿ����ӵ�
	static int GenerateLoc(ChessType PlayerColor, ChessType* Mapt, FlipSpot* vp);		//���������
	static bool IsLocable(int pos, ChessType PlayerColor, ChessType* Mapt);		//�жϿ�����
	static bool IsGameOver(ChessType* Mapt);	//�ж���Ϸ����
	static bool IsStab(ChessType* board, int sqnum, ChessType color);	//�ж��ȶ���
	static void UndoFlips(ChessType* board, int flipCount, ChessType oppcolor);	//����ת
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
