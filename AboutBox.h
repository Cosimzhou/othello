#if !defined(AFX_ABOUTBOX_H__245B2D1C_4A5A_4422_A187_96FE5EB598B5__INCLUDED_)
#define AFX_ABOUTBOX_H__245B2D1C_4A5A_4422_A187_96FE5EB598B5__INCLUDED_

#include "resource.h"
#include ".\\Midi\\MusicPlayer.h"
#include ".\\Midi\\ZPDocument.h"
#include ".\\Midi\\MidiOutput.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma comment(lib, "msimg32")
// AboutBox.h : header file
//

//#define COS0	0.86602540378443864676372317075294f
//#define SIN0	0.5f
#define PI	3.14

/////////////////////////////////////////////////////////////////////////////
// CAboutBox dialog

class CAboutBox : public CDialog
{
// Construction
public:
	int m_cy;
	CAboutBox(CWnd* pParent = NULL);   // standard constructor
	CMusicPlayer m_MusicPlayer;
	CZPDocument m_ZpDoc;
	CMidiOutput m_MidiOut;
// Dialog Data
	//{{AFX_DATA(CAboutBox)
	enum { IDD = IDD_ABOUTBOX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	LOGFONT m_logFont;
	void DrawText(CDC* pDC, int cy);
	int m_TextTop;
	int m_Degree;
	int m_Radius;
	void RotatVertex();
	int m_cx;
	POINT m_Ver[4];
	CRect m_dRect;

	__inline void OuputLine(CDC*pDC, CString str, int x, int &y, int size, COLORREF cl, int maxy);
	// Generated message map functions
	//{{AFX_MSG(CAboutBox)
	virtual void OnCancel();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTBOX_H__245B2D1C_4A5A_4422_A187_96FE5EB598B5__INCLUDED_)
