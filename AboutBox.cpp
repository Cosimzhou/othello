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
	m_logFont.lfCharSet = GB2312_CHARSET;  //�ַ���
	m_logFont.lfOutPrecision = 3;  
	m_logFont.lfClipPrecision = 2;  
	m_logFont.lfQuality = PROOF_QUALITY;  
	m_logFont.lfPitchAndFamily = 49;
	m_logFont.lfEscapement = 0;  
	m_logFont.lfOrientation = 0;  
	m_logFont.lfPitchAndFamily = DEFAULT_PITCH|FF_ROMAN;  
	m_logFont.lfUnderline = FALSE;  //�»���
	m_logFont.lfStrikeOut=FALSE;     //ɾ����  
	m_logFont.lfItalic= FALSE;      //б��  
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
	strcpy(m_logFont.lfFaceName, "����");
	OuputLine(&MemDC, "˫���˳�", 22, y, 7, 0x90F7F9, 300);
	y=270;
	OuputLine(&MemDC, "��ϵ����: E-mail:", 100, y, 7, 0xffffff, 300);
	m_logFont.lfUnderline=TRUE;
	y=270;
	OuputLine(&MemDC, "ufis8@hotmail.com", 250, y, 7, 0xff00, 300);
	m_logFont.lfUnderline=FALSE;
	///////////////////////////////////////////////////////
	//// ����Ϊ������ɫ //////////////
	///////////////////////////////////////////////////////
	//// ����Ϊ������ͼ //////////////
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
	//// ����Ϊ������ͼ //////////////
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

	strcpy(m_logFont.lfFaceName, "����");  
	OuputLine(pDC, "�ڰ�������ϵͳV1.0", x, y, 10, 0xff, cy);

	strcpy(m_logFont.lfFaceName, "����");
	OuputLine(pDC, "�ϲ����մ�ѧ�����ѧԺ�������", x, y, 7, 0x90F7F9, cy);
	OuputLine(pDC, "2009���ҵ���", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "052012 36  ��־��", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "ָ����ʦ: ������", x, y, 7, 0xffffff, cy);
	y+= 25;
	strcpy(m_logFont.lfFaceName, "����");  
	OuputLine(pDC, "��  л", x, y, 10, 0xff, cy);
	strcpy(m_logFont.lfFaceName, "����");
	OuputLine(pDC, "��лMicheal Buro���ڵ�ϵ������", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лRogerLau��������Ȥ����", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��л����ʯ��ҙ���褦���Ķ�ʽ", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лlivedevil��ս������", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лwangfei�ķ����㷨", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лhuaren@ace.nju.edu.cn�������㷨", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лFengart������֧��", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лdisco.com.hk�ĶԾּ�¼", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лsxhbq�Ŀ�������", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лdragoniye�Ŀ��ֶ���", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лNisy�������", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лָ����ʦ���ϸ񶽴�", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лNowcan�ľ������", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��лwolflove��Dynamic Link Library", x, y, 7, 0xffffff, cy);
	y+= 25;
	strcpy(m_logFont.lfFaceName, "����");  
	OuputLine(pDC, "�ر��л", x, y, 10, 0xff, cy);
	strcpy(m_logFont.lfFaceName, "����");
	OuputLine(pDC, "��л����һ�Ե���߶�������ϵĹ���", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��л�ϰ�һֱ�ľ���֧��", x, y, 7, 0xffffff, cy);
	OuputLine(pDC, "��л��лһ�а������ҵ���", x, y, 7, 0xffffff, cy);
	y+= 20;
	OuputLine(pDC, "�����ʮ�ָ�л", x, y, 7, 0xffffff, cy);
	y+= 30;
	OuputLine(pDC, "2009��4��15�հ�", x, y, 5, 0xffffff, cy);
	
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