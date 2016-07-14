// OthelloDlg.h : header file
//
#if !defined(AFX_OTHELLODLG_H__E6EB001D_BA90_490C_B57F_92B4EB7E8DB9__INCLUDED_)
#define AFX_OTHELLODLG_H__E6EB001D_BA90_490C_B57F_92B4EB7E8DB9__INCLUDED_

#include "Graphic.h"	// Added by ClassView
#include "Game.h"	// Added by ClassView
#include "ComputerThink.h"	// Added by ClassView
#include "OpeningReader.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COthelloDlg dialog

class COthelloDlg : public CDialog
{
// Construction
public:
	int m_TimeLimit;
	bool m_bAnimation;
	int m_CostTime[2];
	bool m_UseBook;
	bool m_Keep;
	bool m_LocSound;
	bool m_ShowHint;
	bool m_WBBW;
	bool m_TopMost;
	bool m_ShowData;
	int m_PlayerType[2];

	COthelloDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COthelloDlg)
	enum { IDD = IDD_OTHELLO_DIALOG };
	CListCtrl	m_lstStep;
	CListBox	m_lstConsole;
	CString	m_CInfo;
	CStatusBarCtrl	m_StatusBar;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COthelloDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void OnListConsoleRButtonUp(CPoint);

	// Generated message map functions
	//{{AFX_MSG(COthelloDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnGameMessager(WPARAM wParam,  LPARAM lParam); 
	afx_msg void OnMenuNewGame();
	afx_msg void OnRegret();
	afx_msg void OnRedo();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnSetComputerPiece();
	afx_msg void OnMenuBoardAbnormal();
	afx_msg void OnMenuBoardNormal();
	afx_msg void OnMenuTopmost();
	afx_msg void OnMenuOpeningbook();
	afx_msg void OnMenuOpenlibrary();
	afx_msg void OnMenuComputerRefresh();
	afx_msg void OnAboutbox();
	afx_msg void OnMenuLocsound();
	afx_msg void OnMenuStopsearch();
	afx_msg void OnMenuHintpoint();
	virtual void OnCancel();
	afx_msg void OnMenuHelpContent();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMenuChessbook();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuShowdata();
	afx_msg void OnMenuAnimation();
	afx_msg void OnMenuShowdiagram();
	afx_msg void OnMenuOpendiagram();
	afx_msg void OnMenuSavediagram();
	afx_msg void OnMenuSetlimited();
	virtual void OnOK();
	afx_msg void OnMenuConsoleClear();
	afx_msg void OnMenuConsoleSave();
	afx_msg void OnMenuPausegame();
	afx_msg void OnMenuTurnL();
	afx_msg void OnMenuTurnR();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMenuTraining();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void EchoLocChess(int x, int y);
	//AFX_INNER_OPERATION_MAP{{
	void EchoCmdLine();
	void EchoEndCommand();
	void EchoGM_GameOver(LPARAM lParam);
	//}}AFX_INNER_OPERATION_MAP
	void SearchResult(SearchReport*);

//	int m_SReportTop;
	SearchReport m_SReport[60];
	CBrush m_Brush;
	CString m_LibraryName;
	HACCEL m_hAccel;
	RECT m_GBRc;
	CGame m_Game;
	COpeningReader *m_pOpeningReader;
	CGraphic m_Graph;
	CComputerThink m_CT;
	char m_StackTrace[20];
	const static char* m_PlayerName[ENGINE_NUM];
//	DWORD __stdcall AIThreadFunc(LPVOID lpParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHELLODLG_H__E6EB001D_BA90_490C_B57F_92B4EB7E8DB9__INCLUDED_)
