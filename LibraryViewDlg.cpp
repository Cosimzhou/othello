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
对局库：WTH_2002.WTB，每年一期
棋手库：WTHOR.JOU，记录各棋手的名字
比赛库：WTHOR.TRN，记录各种比赛的名称

3种文件的结构都很相似：16字节文件头+N条记录

对局库记录结构，对于8*8黑白棋，每条记录68字节
2字节 比赛名称，这里只是个序号，具体名称要查比赛库中的相应记录
2字节 黑方棋手名字，这里只是个序号，具体名字要查棋手库
2字节 白方棋手名字
1字节 对局结束时黑方的棋子数（多余空格归胜方）
1字节 黑方理论最佳得子，即在剩余P3个空格时，进行最佳终局计算，黑方的得子数
60字节 棋步序列，每步棋一个字节，记为行号*10+列号，如A1=11，A2=21。欠行的步不作记录，只是将最后多余字节填0

棋手库记录结构
每条记录20字节，字符串类型（以 结尾），记录棋手名字。对于程序，一般用括号加注程序作者，如Thor(quin/becquet)

比赛库记录结构
每条记录26字节，字符串类型，记录比赛名称。  */

void CLibraryViewDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	ReadData(lpszPathName);
}

void CLibraryViewDlg::ReadData(CString lpszPathName)
{
	CFileException fe;
	if(!m_File.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))	{//以“读”的方式打开文件；
		MessageBox("文件打不开！");
		return;
	}
	WTHOR_FILE_HEADER bmfHeader;//定义文件头结构
	DWORD dwBitsSize;
	dwBitsSize = m_File.GetLength();//得到文件长度
	if (m_File.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) !=sizeof(bmfHeader))
		return ;//读取文件的文件头结构信息；
	if (bmfHeader.type != 0 || bmfHeader.size != 8){ //检查该文件是否为WTB格式的文件
		return ;
	}

/*	CFile file_jou, file_trn;
//	CFileException fe;
	if(!m_File.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))	{//以“读”的方式打开文件；
		MessageBox("文件打不开！");
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
