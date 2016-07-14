// SetTimeLimitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Othello.h"
#include "SetTimeLimitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetTimeLimitDlg dialog


CSetTimeLimitDlg::CSetTimeLimitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetTimeLimitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetTimeLimitDlg)
	m_iTime = 0;
	//}}AFX_DATA_INIT
}


void CSetTimeLimitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetTimeLimitDlg)
	DDX_Text(pDX, IDC_EDIT1, m_iTime);
	DDV_MinMaxUInt(pDX, m_iTime, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetTimeLimitDlg, CDialog)
	//{{AFX_MSG_MAP(CSetTimeLimitDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetTimeLimitDlg message handlers

