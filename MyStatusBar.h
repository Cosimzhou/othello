#if !defined(AFX_MYSTATUSBAR_H__F3F52151_FC24_4631_9799_7B0C2A32E47F__INCLUDED_)
#define AFX_MYSTATUSBAR_H__F3F52151_FC24_4631_9799_7B0C2A32E47F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatusBar.h : header file
//
#include "StatusBar.h"
/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar window

class CMyStatusBar : public CStatusBarCtrl, public CStatusBar1
{
// Construction
public:
	CMyStatusBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatusBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATUSBAR_H__F3F52151_FC24_4631_9799_7B0C2A32E47F__INCLUDED_)
