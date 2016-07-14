// SevenEngine.h: interface for the CSevenEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEVENENGINE_H__F2A87C0F_603F_4DFE_8940_30D0C14D3A95__INCLUDED_)
#define AFX_SEVENENGINE_H__F2A87C0F_603F_4DFE_8940_30D0C14D3A95__INCLUDED_

#include "EngineMother.h"
#include "Othello.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagTreeNode{
	ChessType* board;
	int	movepos;
	int	value;
}tagTreeNode;

class CSevenEngine  :public CEngineMother
{
public:
	CSevenEngine();
	virtual ~CSevenEngine();
	void Search(ChessType* curboard, ChessType col);
	void SetAI(int);
protected:
	int m_AI;
	ChessType m_MyColor;
	int m_MaxDepth;
	int m_CurDepth;
private:
	void extend_node_one(tagTreeNode *node_ptr, tagTreeNode *parent_ptr, ChessType color);
	void extend_node_two(tagTreeNode *node_ptr, tagTreeNode *parent_ptr, ChessType color);

	const static int m_BasicDepth[];
	const static int m_AdvanceDepth[];
};
//Report(ChessType* b ,ChessType* c);
#endif // !defined(AFX_SEVENENGINE_H__F2A87C0F_603F_4DFE_8940_30D0C14D3A95__INCLUDED_)
