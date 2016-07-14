// OpeningDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Othello.h"
#include "OpeningDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpeningDlg dialog


COpeningDlg::COpeningDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpeningDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpeningDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COpeningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpeningDlg)
	DDX_Control(pDX, IDC_TREEVIEW, m_Tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpeningDlg, CDialog)
	//{{AFX_MSG_MAP(COpeningDlg)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CLICK, IDC_TREEVIEW, OnClickTreeview)
	ON_BN_CLICKED(IDC_RADIO_C4, OnRadioC4)
	ON_BN_CLICKED(IDC_RADIO_D3, OnRadioC4)
	ON_BN_CLICKED(IDC_RADIO_E6, OnRadioC4)
	ON_BN_CLICKED(IDC_RADIO_F5, OnRadioC4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpeningDlg message handlers



void COpeningDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	((CButton *)GetDlgItem(IDC_RADIO_C4))->SetCheck(TRUE);
	InitData();
	m_FirstLoc=GetCheckedRadioButton(IDC_RADIO_C4, IDC_RADIO_F5)-IDC_RADIO_C4;
}



void COpeningDlg::OnClickTreeview(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint point;
	UINT pflags;
	GetCursorPos(&point); 
	m_Tree.ScreenToClient(&point);
	HTREEITEM hItem = m_Tree.HitTest( point, &pflags );
	if(hItem){
		char* start=(char*)m_Tree.GetItemData(hItem);
		char* end=strstr(start,"\r\n");
		int slen=(end-start);
		memcpy(m_StepList, start, slen*sizeof(char));
		m_StepList[slen]=0;
		m_FirstLoc=GetCheckedRadioButton(IDC_RADIO_C4, IDC_RADIO_F5)-IDC_RADIO_C4;
		Rotate();
//		SetDlgItemText(IDC_EDIT_NAME, m_Tree.GetItemText(hItem));
		SetDlgItemText(IDC_STATIC_CONTENT, m_StepList);
	}
	*pResult = 0;
}

void COpeningDlg::InitData()
{
	HINSTANCE handle = ::AfxGetResourceHandle();
	HRSRC hrsrc = ::FindResource(handle,MAKEINTRESOURCE(IDR_TOPENBK1),"TOPENBK");
    DWORD word = ::SizeofResource(handle,hrsrc);
    m_lpBy = (BYTE*)LoadResource(handle,hrsrc);

	m_Images.Create(IDB_TREENODE, 20, 5, RGB(0,255,0));
	m_Tree.SetImageList(&m_Images, TVSIL_NORMAL);
	m_StepList[0]=0;

	
	HTREEITEM pHti[6], cht;
	int hTop;
	char* cstr=(char*)m_lpBy;
	char* ends, *endln;
	char lpstr[64];
	pHti[0]=TVI_ROOT;
	m_Tree.SetItemImage(pHti[0], 0, 0);
	while(*cstr){
		hTop=1;
		ends=strstr(cstr,":");
		ASSERT(ends);
		endln=strstr(ends,"\r\n");
		ASSERT(endln);
		while(*cstr=='\t'){cstr++; hTop++;}
		memcpy(lpstr, cstr, (ends-cstr)*sizeof(char));
		lpstr[ends-cstr]=0;
		pHti[hTop]=cht=m_Tree.InsertItem(lpstr, pHti[hTop-1]);
		m_Tree.SetItemImage(cht, 1, 2);
		m_Tree.SetItemData(cht,(DWORD)(ends+1));
		cstr=endln+2;
	}
}

void COpeningDlg::Rotate()
{
	if(!m_FirstLoc || !m_StepList[0]) return;
	ASSERT(m_FirstLoc>0&&m_FirstLoc<4);
	char *cb=m_StepList;
	char lt, nm, Black, tmp;
	while(*cb){
		lt = *cb;
		Black = ((lt>='A' && lt<='H')?'A':'a');
		lt -=Black;
		nm = *(cb+1)-'1';
		if(m_FirstLoc & 2){
			lt=7-lt;
			nm=7-nm;
		}
		if(m_FirstLoc & 1){
			tmp = lt;
			lt = nm;
			nm =tmp;
		}
		*(cb++)=lt+Black;
		*(cb++)=nm+'1';
	}
}

void COpeningDlg::OnRadioC4() 
{
	HTREEITEM hItem = m_Tree.GetSelectedItem();
	if(hItem){
		char* start=(char*)m_Tree.GetItemData(hItem);
		char* end=strstr(start,"\r\n");
		int slen=(end-start);
		memcpy(m_StepList, start, slen*sizeof(char));
		m_StepList[slen]=0;
		m_FirstLoc=GetCheckedRadioButton(IDC_RADIO_C4, IDC_RADIO_F5)-IDC_RADIO_C4;
		Rotate();
		SetDlgItemText(IDC_STATIC_CONTENT, m_StepList);
	}	
}

void COpeningDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
