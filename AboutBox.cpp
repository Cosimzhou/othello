// AboutBox.cpp : implementation file
//

#include "stdafx.h"
#include "Othello.h"
#include "AboutBox.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutBox dialog


CAboutBox::CAboutBox(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutBox::IDD, pParent)
{
//	logFont.lfWidth = 10;  
//	logFont.lfHeight = 20;
	m_logFont.lfCharSet = GB2312_CHARSET;  //字符集
	m_logFont.lfOutPrecision = 3;  
	m_logFont.lfClipPrecision = 2;  
	m_logFont.lfQuality = PROOF_QUALITY;  
	m_logFont.lfPitchAndFamily = 49;
	m_logFont.lfEscapement = 0;  
	m_logFont.lfOrientation = 0;  
	m_logFont.lfPitchAndFamily = DEFAULT_PITCH|FF_ROMAN;  
	m_logFont.lfUnderline = FALSE;  //下划线
	m_logFont.lfStrikeOut=FALSE;     //删除线  
	m_logFont.lfItalic= FALSE;      //斜体  
	m_logFont.lfWeight= FW_THIN;

	//{{AFX_DATA_INIT(CAboutBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutBox, CDialog)
	//{{AFX_MSG_MAP(CAboutBox)
//	ON_WM_CANCEL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutBox message handlers

void CAboutBox::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	OnCancel();
}

BOOL CAboutBox::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&m_dRect);
	ScreenToClient(&m_dRect);

	m_cx=m_dRect.Width();
	m_TextTop= m_cy=m_dRect.Height();

	m_Degree=0;
	m_Radius=(int)(sqrt(m_cx*m_cx+m_cy*m_cy));
	m_cx/=2;
	m_cy/=2;
	
	RotatVertex();
	SetTimer(0,150, NULL);

	m_MidiOut.MIDIOutOpen(0);
	m_ZpDoc.m_pMidi = &m_MidiOut;
	m_MusicPlayer.PlayDocument(&m_ZpDoc);
	//m_MusicPlayer.di.doc 
	return TRUE;
}

void CAboutBox::OnTimer(UINT nIDEvent)
{
	if(nIDEvent==0){
		RotatVertex();
		Invalidate();
		UpdateWindow();
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CAboutBox::OnEraseBkgnd(CDC* pDC)
{
	int nWidth;
	int nHeight;

	CRect rect;
	GetWindowRect(&rect);
	nWidth = rect.Width();
	nHeight= rect.Height();

	CDC MemDC;
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC (NULL);
	MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);

	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(41,115,66));

	MemDC.SetBkMode(TRANSPARENT);
	int y=270;
	strcpy(m_logFont.lfFaceName, "宋体");
	OuputLine(&MemDC, "双击退出", 22, y, 7, 0x90F7F9, 300);
	y=270;
	OuputLine(&MemDC, "联系作者: E-mail:", 100, y, 7, 0xffffff, 300);
	m_logFont.lfUnderline=TRUE;
	y=270;
	OuputLine(&MemDC, "ufis8@hotmail.com", 250, y, 7, 0xff00, 300);
	m_logFont.lfUnderline=FALSE;
	///////////////////////////////////////////////////////
	//// 以上为画背景色 //////////////
	///////////////////////////////////////////////////////
	//// 以下为画背景图 //////////////
	///////////////////////////////////////////////////////
	CDC DCforFrame;
	CBitmap mbmp;
	DCforFrame.CreateCompatibleDC(NULL);
	mbmp.CreateCompatibleBitmap(pDC,nWidth,nHeight);

	DCforFrame.SelectObject(&mbmp);
	DCforFrame.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));

	TRIVERTEX Vertex[4];
	GRADIENT_TRIANGLE gtr[2];

	Vertex[0].x=m_Ver[0].x;
	Vertex[0].y=m_Ver[0].y;
	Vertex[0].Alpha=0xff00;
	Vertex[0].Blue =0x7f00;
	Vertex[0].Red  =0x7f00;
	Vertex[0].Green=0x7f00;

	Vertex[1].x=m_Ver[1].x;
	Vertex[1].y=m_Ver[1].y;
	Vertex[1].Alpha=0xff00;
	Vertex[1].Blue =0xff00;
	Vertex[1].Red  =0xff00;
	Vertex[1].Green=0xff00;
	
	Vertex[2].x=m_Ver[2].x;
	Vertex[2].y=m_Ver[2].y;
	Vertex[2].Alpha=0xff00;
	Vertex[2].Blue =0x7f00;
	Vertex[2].Red  =0x7f00;
	Vertex[2].Green=0x7f00;

	Vertex[3].x=m_Ver[3].x;
	Vertex[3].y=m_Ver[3].y;
	Vertex[3].Alpha=0xff00;
	Vertex[3].Blue =0x0000;
	Vertex[3].Red  =0x0000;
	Vertex[3].Green=0x0000;

	gtr[0].Vertex1=0;
	gtr[0].Vertex2=1;
	gtr[0].Vertex3=2;
	gtr[1].Vertex1=0;
	gtr[1].Vertex2=3;
	gtr[1].Vertex3=2;
	BOOL ret= GradientFill(DCforFrame.GetSafeHdc(), Vertex, 4, gtr, 2, GRADIENT_FILL_TRIANGLE); 
	DrawText(&DCforFrame, m_dRect.Height());

	MemDC.BitBlt(m_dRect.left, m_dRect.top, m_dRect.Width(), m_dRect.Height(), &DCforFrame, 0, 0, SRCCOPY);

	CBitmap bmpLogo;
	bmpLogo.LoadBitmap(IDB_LOGO);
	DCforFrame.SelectObject(&bmpLogo);
	MemDC.BitBlt(10, 70, 82, 74, &DCforFrame, 0, 0, SRCCOPY);
	///////////////////////////////////////////////////////
	//// 以上为画背景图 //////////////
	///////////////////////////////////////////////////////
	
	pDC->BitBlt(0, 0, nWidth, nHeight, &MemDC, 0, 0, SRCCOPY);

	bmpLogo.DeleteObject();
	mbmp.DeleteObject();
	DCforFrame.DeleteDC();
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	return TRUE;
}

void CAboutBox::RotatVertex()
{
	for(int i=0; i<4; i++){
		m_Ver[i].x=(long)(m_Radius*cos((PI/6)*m_Degree+i*(PI/2))+m_cx);
		m_Ver[i].y=(long)(m_Radius*sin((PI/6)*m_Degree+i*(PI/2))+m_cy);
	}
	if(++m_Degree>=12) m_Degree=0;
}

void CAboutBox::DrawText(CDC *pDC, int cy)
{
	int y=m_TextTop;
	int x=m_cx;
	int height;
	pDC->SetTextAlign(TA_CENTER);
	pDC->SetBkMode(TRANSPARENT);

	strcpy(m_logFont.lfFaceName, "黑体");  
	OuputLine(pDC, "黑白棋游研系统V1.0", x, y, 10, 0xff, cy);

	strcpy(m_logFont.lfFaceName, "宋体");
	OuputLine(pDC, "南昌航空大学计算机学院软件工程", x, y, 7, 0x90F7F9, cy);
	OuputLine(pDC, "2009年毕业设计", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "052012 36  周志超", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "指导教师: 刘晓蓉", x, y, 7, 0xffffff, cy);
	y+= 25;
	strcpy(m_logFont.lfFaceName, "黑体");  
	OuputLine(pDC, "鸣  谢", x, y, 10, 0xff, cy);
	strcpy(m_logFont.lfFaceName, "宋体");
	OuputLine(pDC, "感谢Micheal Buro教授的系列论文", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢RogerLau的早期兴趣激发", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢“定石を覚えよう”的定式", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢livedevil的战术技法", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢wangfei的飞禽算法", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢huaren@ace.nju.edu.cn的猛禽算法", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢Fengart的数据支持", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢disco.com.hk的对局记录", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢sxhbq的开局棋谱", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢dragoniye的开局定势", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢Nisy的灵感起发", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢指导老师的严格督促", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢Nowcan的经典界面", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢wolflove的Dynamic Link Library", x, y, 7, 0xffffff, cy);
	y+= 25;
	strcpy(m_logFont.lfFaceName, "黑体");  
	OuputLine(pDC, "特别感谢", x, y, 10, 0xff, cy);
	strcpy(m_logFont.lfFaceName, "宋体");
	OuputLine(pDC, "感谢老妈一旁的唠叨和生活上的关照", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢老爸一直的精神支持", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "感谢感谢一切帮助过我的人", x, y, 7, 0xffffff, cy);
	y+= 20;
	OuputLine(pDC, "真的是十分感谢", x, y, 7, 0xffffff, cy);
	y+= 30;
	OuputLine(pDC, "2009年4月15日版", x, y, 5, 0xffffff, cy);
	
	height=m_TextTop-y;
	m_TextTop-=3;
	if(m_TextTop<height) m_TextTop = m_dRect.Height();
}
void CAboutBox::OuputLine(CDC*pDC, CString str, int x, int &y, int size, COLORREF cl, int maxy){
	CFont TempFont, *tfont;
	m_logFont.lfWidth = size;  
	m_logFont.lfHeight = size*2;
	
	TempFont.CreateFontIndirect(&m_logFont);

	tfont=pDC->SelectObject(&TempFont);

	if(y<maxy && y>-(m_logFont.lfHeight+2)){
		pDC->SetTextColor(0);
		pDC->TextOut(x+2, y+2, str);
		pDC->SetTextColor(cl);
		pDC->TextOut(x, y, str);
	}
	y+= m_logFont.lfHeight + 5;

	if(tfont) pDC->SelectObject(tfont);
	TempFont.DeleteObject();
}

void CAboutBox::OnLButtonDown(UINT nFlags, CPoint pt) 
{
	if(pt.x>250 && pt.y>270){
		HINSTANCE hRun = ShellExecute(GetParent()->GetSafeHwnd(), _T("mailto"), "ufis8@hotmail.com", NULL, NULL, SW_SHOW);
		if ((int) hRun <= 32){
			TRACE("Failed to invoke URL using ShellExecute\n");
			return;
		}
		return;
	}
	CDialog::OnLButtonDown(nFlags, pt);
}

void CAboutBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
	OnCancel();	
}
void CAboutBox::OnCancel() 
{
	m_MusicPlayer.StopPlay();
	CDialog::OnCancel();
}