// Othello.h : main header file for the OTHELLO application
//

#if !defined(AFX_OTHELLO_H__A5D7C4A0_603F_4942_B68A_E438D4E02BE2__INCLUDED_)
#define AFX_OTHELLO_H__A5D7C4A0_603F_4942_B68A_E438D4E02BE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define	_AS_GREEN_SOFTWARE


#define	WM_GAMEMESSAGER	WM_USER+365

#define GM_LEGAL_OPERATION	2
#define GM_COMPUTER_RUN		3
#define GM_GAME_OVER		4
#define GM_HAVE_TO_SKIP		5
#define GM_STATUSBAR		6
#define GM_STEPLIST			7
#define GM_EVALUATE			8
#define GM_NODES			9
#define GM_SOLVED			10
#define GM_REPORTTRACE		11
#define GM_SHOWDIAGRAM		12
#define GM_GETREPORT		13
#define GM_TIMEOUT			14

#define GM_UNDO_REDO		99
#define GM_SETPIECE			100


#define B_CH	1
#define	W_CH	-1
#define	N_CH	0
#define TRANSUM	(B_CH+W_CH)
#define	BLOCK	2
#define	WHITE	W_CH
#define	EMPTY	N_CH
#define	BLACK	B_CH
#define	DUMMY	BLOCK

#define	GO_RIGHT		1				//=1
#define	GO_DOWNRIGHT	X_UB			//=10
#define	GO_DOWN			XL_UB			//=9
#define	GO_DOWNLEFT		XC_UB			//=8
#define	GO_LEFT			(-GO_RIGHT)		//=-1
#define	GO_UPRIGHT		(-GO_DOWNLEFT)	//=-8
#define	GO_UP			(-GO_DOWN)		//=-9
#define	GO_UPLEFT		(-GO_DOWNRIGHT)	//=-10

#define	YES		2
#define	MAYBE	1
#define	NO		0

#define INF		0x7fff			//=32767

#define XC_UB	8
#define	YC_UB	8
#define XH_UB	(XC_UB/2)		//=4
#define	YH_UB	(YC_UB/2)		//=4
#define XL_UB	(XC_UB+1)		//=9
#define	YL_UB	(YC_UB+1)		//=9
#define X_UB	(XC_UB+2)		//=10
#define	Y_UB	(YC_UB+2)		//=10
#define CH_LEN	(XL_UB*Y_UB+1)	//=91

#define Oppl_ch(p)	(TRANSUM-p)	//=3-p
#define GetX_ch(p)	(p%(XL_UB))	//=p%9
#define GetY_ch(p)	(p/(XL_UB))	//=p/9

#define Conv(x,y)	(x+(y)*XL_UB)//=x+9*y

#define LUC_in	X_UB				//=10
#define RUC_in	(XL_UB+XC_UB)		//=17
#define LDC_in	(XL_UB*YC_UB+1)		//=73
#define RDC_in	(XL_UB*YC_UB+XC_UB)	//=80

#define LUC_C1	(LUC_in+GO_RIGHT)		//=11
#define LUC_C2	(LUC_in+GO_DOWN)		//=19
#define LUC_X	(LUC_in+GO_DOWNRIGHT)	//=20
#define RUC_C1	(RUC_in+GO_LEFT)		//=16
#define RUC_C2	(RUC_in+GO_DOWN)		//=26
#define RUC_X	(RUC_in+GO_DOWNLEFT)	//=25
#define LDC_C1	(LDC_in+GO_RIGHT)		//=74
#define LDC_C2	(LDC_in+GO_UP)			//=64
#define LDC_X	(LDC_in+GO_UPRIGHT)		//=65
#define RDC_C1	(RDC_in+GO_LEFT)		//=81
#define RDC_C2	(RDC_in+GO_UP)			//=71
#define RDC_X	(RDC_in+GO_UPLEFT)		//=70

#define PT_A1	10
#define PT_B1	11
#define PT_C1	12
#define PT_D1	13
#define PT_E1	14
#define PT_F1	15
#define PT_G1	16
#define PT_H1	17

#define PT_A2	19
#define PT_B2	20
#define PT_C2	21
#define PT_D2	22
#define PT_E2	23
#define PT_F2	24
#define PT_G2	25
#define PT_H2	26

#define PT_A3	28
#define PT_B3	29
#define PT_C3	30
#define PT_D3	31
#define PT_E3	32
#define PT_F3	33
#define PT_G3	34
#define PT_H3	35

#define PT_A4	37
#define PT_B4	38
#define PT_C4	39
#define PT_D4	40
#define PT_E4	41
#define PT_F4	42
#define PT_G4	43
#define PT_H4	44

#define PT_A5	46
#define PT_B5	47
#define PT_C5	48
#define PT_D5	49
#define PT_E5	50
#define PT_F5	51
#define PT_G5	52
#define PT_H5	53

#define PT_A6	55
#define PT_B6	56
#define PT_C6	57
#define PT_D6	58
#define PT_E6	59
#define PT_F6	60
#define PT_G6	61
#define PT_H6	62

#define PT_A7	64
#define PT_B7	65
#define PT_C7	66
#define PT_D7	67
#define PT_E7	68
#define PT_F7	69
#define PT_G7	70
#define PT_H7	71

#define PT_A8	73
#define PT_B8	74
#define PT_C8	75
#define PT_D8	76
#define PT_E8	77
#define PT_F8	78
#define PT_G8	79
#define PT_H8	80
#define ENGINE_NUM  19
typedef __int8 ChessType;

typedef struct FlipSpot{
	int square;
	int flips;
}FlipSpot;



/////////////////////////////////////////////////////////////////////////////
// COthelloApp:
// See Othello.cpp for the implementation of this class
//

class COthelloApp : public CWinApp
{
public:
	COthelloApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COthelloApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COthelloApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHELLO_H__A5D7C4A0_603F_4942_B68A_E438D4E02BE2__INCLUDED_)
