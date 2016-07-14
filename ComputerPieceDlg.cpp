// ComputerPieceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Othello.h"
#include "ComputerPieceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComputerPieceDlg dialog


CComputerPieceDlg::CComputerPieceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComputerPieceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComputerPieceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CComputerPieceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComputerPieceDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComputerPieceDlg, CDialog)
	//{{AFX_MSG_MAP(CComputerPieceDlg)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE, OnButtonExchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComputerPieceDlg message handlers



void CComputerPieceDlg::OnOK() 
{
	int level1=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	int level2=((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
	if(level1 && level2 && level1==level2){
		MessageBox("相同的电脑棋手不能同时执黑白两方！","提示",MB_ICONINFORMATION);
		return;
	}
	m_BlackPlayer=level1;
	m_WhitePlayer=level2;
	CDialog::OnOK();
}


void CComputerPieceDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
//	CComboBox* tmp=(CComboBox*)::GetDlgItem (this->m_hWnd,IDC_COMBO2);//IDC_COMBO1));
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(m_BlackPlayer);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(m_WhitePlayer);
}

void CComputerPieceDlg::OnButtonExchange() 
{
	// TODO: Add your control notification handler code here
	int tmp1, tmp2;
	tmp1=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	tmp2=((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();	
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(tmp2);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(tmp1);	
}
