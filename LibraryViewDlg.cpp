// LibraryViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Othello.h"
#include "LibraryViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibraryViewDlg dialog


CLibraryViewDlg::CLibraryViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLibraryViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLibraryViewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLibraryViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLibraryViewDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLibraryViewDlg, CDialog)
	//{{AFX_MSG_MAP(CLibraryViewDlg)
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibraryViewDlg message handlers


/*
�Ծֿ⣺WTH_2002.WTB��ÿ��һ��
���ֿ⣺WTHOR.JOU����¼�����ֵ�����
�����⣺WTHOR.TRN����¼���ֱ���������

3���ļ��Ľṹ�������ƣ�16�ֽ��ļ�ͷ+N����¼

�Ծֿ��¼�ṹ������8*8�ڰ��壬ÿ����¼68�ֽ�
2�ֽ� �������ƣ�����ֻ�Ǹ���ţ���������Ҫ��������е���Ӧ��¼
2�ֽ� �ڷ��������֣�����ֻ�Ǹ���ţ���������Ҫ�����ֿ�
2�ֽ� �׷���������
1�ֽ� �Ծֽ���ʱ�ڷ���������������ո��ʤ����
1�ֽ� �ڷ�������ѵ��ӣ�����ʣ��P3���ո�ʱ����������վּ��㣬�ڷ��ĵ�����
60�ֽ� �岽���У�ÿ����һ���ֽڣ���Ϊ�к�*10+�кţ���A1=11��A2=21��Ƿ�еĲ�������¼��ֻ�ǽ��������ֽ���0

���ֿ��¼�ṹ
ÿ����¼20�ֽڣ��ַ������ͣ��� ��β������¼�������֡����ڳ���һ�������ż�ע�������ߣ���Thor(quin/becquet)

�������¼�ṹ
ÿ����¼26�ֽڣ��ַ������ͣ���¼�������ơ�  */

void CLibraryViewDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	ReadData(lpszPathName);
}

void CLibraryViewDlg::ReadData(CString lpszPathName)
{
	CFileException fe;
	if(!m_File.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))	{//�ԡ������ķ�ʽ���ļ���
		MessageBox("�ļ��򲻿���");
		return;
	}
	WTHOR_FILE_HEADER bmfHeader;//�����ļ�ͷ�ṹ
	DWORD dwBitsSize;
	dwBitsSize = m_File.GetLength();//�õ��ļ�����
	if (m_File.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) !=sizeof(bmfHeader))
		return ;//��ȡ�ļ����ļ�ͷ�ṹ��Ϣ��
	if (bmfHeader.type != 0 || bmfHeader.size != 8){ //�����ļ��Ƿ�ΪWTB��ʽ���ļ�
		return ;
	}

/*	CFile file_jou, file_trn;
//	CFileException fe;
	if(!m_File.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))	{//�ԡ������ķ�ʽ���ļ���
		MessageBox("�ļ��򲻿���");
		return;
	}*/
	LIBRARY_RECORD librec;
	CString str;
	int index=0;
	while (m_File.Read((LPSTR)&librec, sizeof(librec)) == sizeof(librec)){
		str.Format("%-6d %.5d-%.5d[%2d:%2d](%.5d)", ++index, librec.bla_no,
			librec.whi_no, librec.black, 64- librec.black, librec.match_no);
		m_List.AddString(str);
	}
	return ;
}

void CLibraryViewDlg::OnSelchangeList() 
{
	long start=m_List.GetCurSel()*68+24;
	char context[61], *sp, *isp;
	m_File.Seek(start, 0);
	m_File.Read(context, 60);
	context[60] = 0;
	sp = context;
	isp= m_Item;
	while(*sp){
		*(isp++) = (*sp % 10) + 'A' - 1;
		*(isp++) = (*(sp++) / 10) + '0';
	}
	*isp = 0;
	SetDlgItemText(IDC_STATIC_CONTEXT, m_Item);
}
