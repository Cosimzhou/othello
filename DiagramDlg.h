#if !defined(AFX_DIAGRAMDLG_H__431F64E2_0DD2_43ED_B323_FA221C274EDE__INCLUDED_)
#define AFX_DIAGRAMDLG_H__431F64E2_0DD2_43ED_B323_FA221C274EDE__INCLUDED_

#include "Game.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DiagramDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDiagramDlg dialog

class CDiagramDlg : public CDialog
{
// Construction
public:
	int m_SRTop;
	SearchReport* m_SRHead;
	CDiagramDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDiagramDlg)
	enum { IDD = IDD_DIAGRAM_DIALOG };
	int		m_ShowType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagramDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DrawDiagram(CDC *pdc);
	CRect m_dRect;
	CPen m_apen, m_wpen, m_bpen, m_cpen;
	LOGFONT m_logFont;
	CFont m_Font;

	// Generated message map functions
	//{{AFX_MSG(CDiagramDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnRadioType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	__inline long GetValueInSR(SearchReport*);
//	const static int m_Offset[8];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGRAMDLG_H__431F64E2_0DD2_43ED_B323_FA221C274EDE__INCLUDED_)
