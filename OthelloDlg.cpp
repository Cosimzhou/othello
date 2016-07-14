// OthelloDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AboutBox.h"
#include "Othello.h"
#include "OthelloDlg.h"
#include "OpeningDlg.h"
#include "ComputerPieceDlg.h"
#include "LibraryViewDlg.h"
#include "DiagramDlg.h"
#include "SetTimeLimitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



const char* COthelloDlg::m_PlayerName[]={
	"��"  ,"���","��ʳ","�ƶ�","����","�ȹ�",
	"��ȸ","����","�ɺ�","���","ɽ��","����",
	"����","����","��Ȯ","���","��ʨ","���",
	"����"
};

/////////////////////////////////////////////////////////////////////////////
// COthelloDlg dialog

COthelloDlg::COthelloDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COthelloDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COthelloDlg)
	m_CInfo = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void COthelloDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COthelloDlg)
	DDX_Control(pDX, IDC_LIST_STEP, m_lstStep);
	DDX_Control(pDX, IDC_LIST_CONSOLE, m_lstConsole);
	DDX_Text(pDX, IDC_COMP_INFO, m_CInfo);
	DDV_MaxChars(pDX, m_CInfo, 65535);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COthelloDlg, CDialog)
	//{{AFX_MSG_MAP(COthelloDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_GAMEMESSAGER, OnGameMessager) 
	ON_BN_CLICKED(IDC_NEW_GAME, OnMenuNewGame)
	ON_COMMAND(ID_MENU_REGRET, OnRegret)
	ON_COMMAND(ID_MENU_REDO, OnRedo)
	ON_COMMAND(ID_MENU_OPEN, OnOpen)
	ON_COMMAND(ID_MENU_SAVE, OnSave)
	ON_COMMAND(ID_MENU_COMPUTERPIECE, OnSetComputerPiece)
	ON_COMMAND(ID_MENU_BOARD_ABNORMAL, OnMenuBoardAbnormal)
	ON_COMMAND(ID_MENU_BOARD_NORMAL, OnMenuBoardNormal)
	ON_COMMAND(ID_MENU_TOPMOST, OnMenuTopmost)
	ON_COMMAND(ID_MENU_OPENINGBOOK, OnMenuOpeningbook)
	ON_COMMAND(ID_MENU_OPENLIBRARY, OnMenuOpenlibrary)
	ON_COMMAND(ID_MENU_COMPUTER_REFRESH, OnMenuComputerRefresh)
	ON_COMMAND(ID_MENU_ABOUTBOX, OnAboutbox)
	ON_COMMAND(ID_MENU_LOCSOUND, OnMenuLocsound)
	ON_COMMAND(ID_MENU_STOPSEARCH, OnMenuStopsearch)
	ON_COMMAND(ID_MENU_HINTPOINT, OnMenuHintpoint)
	ON_COMMAND(ID_MENU_HELP_CONTENT, OnMenuHelpContent)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENU_CHESSBOOK, OnMenuChessbook)
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_SHOWDATA, OnMenuShowdata)
	ON_COMMAND(ID_MENU_ANIMATION, OnMenuAnimation)
	ON_COMMAND(ID_MENU_SHOWDIAGRAM, OnMenuShowdiagram)
	ON_COMMAND(ID_MENU_OPENDIAGRAM, OnMenuOpendiagram)
	ON_COMMAND(ID_MENU_SAVEDIAGRAM, OnMenuSavediagram)
	ON_COMMAND(ID_MENU_SETLIMITED, OnMenuSetlimited)
	ON_COMMAND(ID_MENU_CONSOLE_CLEAR, OnMenuConsoleClear)
	ON_COMMAND(ID_MENU_CONSOLE_SAVE, OnMenuConsoleSave)
	ON_COMMAND(ID_MENU_PAUSEGAME, OnMenuPausegame)
	ON_COMMAND(ID_MENU_TURN_L, OnMenuTurnL)
	ON_COMMAND(ID_MENU_TURN_R, OnMenuTurnR)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_TRAINING, OnMenuTraining)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COthelloDlg message handlers

BOOL COthelloDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu="����Othello(&A)...";//.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_Brush.CreateSolidBrush(RGB(41,115,66));
#ifdef _SHOW_STATUS_BAR
	m_StatusBar.Create(WS_CHILD|WS_VISIBLE|SBS_SIZEGRIP, CRect(0, 0, 0, 0), this, 101);
	m_StatusBar.SetBkColor(RGB(41,115,66));		// ����ɫ
	int arWidth[] = { 28, 48, 68, 96, 116, 136, 156, 176, 196, 226, 246, 281, -1 };
	m_StatusBar.SetParts(13, arWidth);				// ����
	m_StatusBar.SetText("jjj", 1, 0);	// ��һ�������ı�
	m_StatusBar.SetText("ij ", 0, 0);				// �ڶ��������ı�
//	m_StatusBar.GetDlgItem(1)->GetDC()->SetTextColor(0xffffff);
#endif
	m_hAccel = ::LoadAccelerators(AfxGetResourceHandle(),    
                  MAKEINTRESOURCE(IDR_ACCELERATOR_MAIN));   //��ݼ���id  
    ASSERT(m_hAccel); 
	
	m_lstStep.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lstStep.InsertColumn(0, "No.", LVCFMT_LEFT, 20);
	m_lstStep.InsertColumn(1, "��ɫ", LVCFMT_LEFT, 35);
	m_lstStep.InsertColumn(2, "Ӧ��", LVCFMT_LEFT, 80);

	m_GBRc.top=31;
	m_GBRc.left=31;
	m_GBRc.right=m_GBRc.left+48*8;
	m_GBRc.bottom=m_GBRc.top+48*8;
	
	m_Game.SetOwner(m_hWnd);
	m_Game.SetComputerSide(m_PlayerType);
	m_Game.m_PlaySound = true;

	m_pOpeningReader = new COpeningReader(
#ifdef _DEBUG
	""
#else
	"book.lib"
#endif
	);
	if(!m_pOpeningReader->m_bAvalible){
		delete m_pOpeningReader;
		m_pOpeningReader = NULL;
	}
	CDC* pdc=GetDC();
	CPen* pen =new CPen();
	HBRUSH br=(HBRUSH)::GetStockObject(NULL_BRUSH);
	pen->CreatePen(PS_SOLID, 5, RGB(0,255,0));
	pdc->SelectObject(pen);
	pdc->SelectObject(br);
	pdc->SetTextColor(0xffffff);
	pdc->SetTextAlign(TA_CENTER);
	pdc->SetBkMode(TRANSPARENT);

	m_Graph.SetDC(pdc);
	m_Graph.SetRect(m_GBRc);
	m_Graph.SetGame(&m_Game);
	m_Graph.SetOpeningBook(m_pOpeningReader);

	if(m_Keep){
		m_Graph.m_WBBW = m_WBBW;
		if(m_WBBW){ //���̷ֲ�
			GetMenu()->GetSubMenu(1)->GetSubMenu(0)->
				CheckMenuRadioItem(ID_MENU_BOARD_NORMAL,ID_MENU_BOARD_ABNORMAL,ID_MENU_BOARD_NORMAL,MF_BYCOMMAND);
		}else{
			GetMenu()->GetSubMenu(1)->GetSubMenu(0)->
				CheckMenuRadioItem(ID_MENU_BOARD_NORMAL,ID_MENU_BOARD_ABNORMAL,ID_MENU_BOARD_ABNORMAL,MF_BYCOMMAND);
		}
		OnMenuHintpoint();	// m_ShowHint;
		OnMenuLocsound();	// m_LocSound;
		OnMenuTopmost();	// m_TopMost;
		OnMenuChessbook();	// m_UseBook;
		OnMenuShowdata();	// m_ShowData;
		OnMenuAnimation();	// m_bAnimation;
		m_Keep=true;
	}else{
		m_PlayerType[0]=0;
		m_PlayerType[1]=1;
	}
	m_CT.SetOwner(m_hWnd);
	m_CT.SetGame(&m_Game);
	m_CT.SetStyle(m_PlayerType);

	m_CT.SetOpeningReader(m_pOpeningReader);
	OnMenuNewGame();
	m_CInfo.Format("�ڴ�ռ�����:\r\n��CGame:%dbytes\r\n"
		"��CGraph:%dbytes\r\n��CComputerThink:%dbytes\r\n"
		"��CGameScript:%dbytes\r\n��COpeningReader:%dbytes",
		sizeof(CGame), sizeof(CGraphic),
		sizeof(CComputerThink), sizeof(CGameScript),
		sizeof(COpeningReader));
	UpdateData(FALSE);
	SendMessage(WM_GAMEMESSAGER,GM_SETPIECE,0);
	m_LibraryName="";

//	m_TimeLimit = 0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COthelloDlg::OnPaint() 
{
	if (IsIconic())	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}else{
		m_Graph.Paint();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.

void COthelloDlg::OnLButtonDown(UINT nFlags, CPoint pt) 
{
	int x, y;
	if(pt.x<m_GBRc.right && pt.y<m_GBRc.bottom && pt.x>m_GBRc.left && pt.y>m_GBRc.top){
		x=(pt.x-m_GBRc.left)/48+1;	y=(pt.y-m_GBRc.top)/48+1;
		EchoLocChess(x, y);
	}
	CDialog::OnLButtonDown(nFlags, pt);
}
LRESULT COthelloDlg::OnGameMessager(WPARAM wParam,  LPARAM lParam){
	CString str;
	char h, c;
	int i;
	UINT ukey;
	switch(wParam){
	case GM_LEGAL_OPERATION:
		m_Graph.m_Maybe=0;
		InvalidateRect(&m_GBRc, FALSE);
		UpdateWindow();
		break;
	case GM_COMPUTER_RUN: 
		i=m_Game.GetColor();
		str.Format("���ڵȴ�%s��[%s]����",i?"��":"��",m_PlayerName[m_PlayerType[i]]);
		SetDlgItemText(IDC_STATIC_COMMENT, str);
		m_CT.StartToThink();
		m_CT.SetTimeLimit(m_TimeLimit);
		break;
	case GM_GAME_OVER:
		EchoGM_GameOver(lParam);
		break;
	case GM_HAVE_TO_SKIP:
		if(lParam==B_CH){
			str="�׷�[";
			i=1;
		}else{ 
			str="�ڷ�[";
			i=0;
		}
		str+=m_PlayerName[m_PlayerType[i]];
		str+="]�޷�����, ����ͣһ��!";
		SetDlgItemText(IDC_STATIC_COMMENT, str);		
		MessageBox(str,"��ʾ",MB_ICONINFORMATION);
		break;
	case GM_STATUSBAR:
		c=lParam&0xff;
		h=(lParam>>8)&0xff;
		str.Format("%d",c);
		SetDlgItemText(IDC_LBL_B_CH,str);
		str.Format("%d",h);
		SetDlgItemText(IDC_LBL_W_CH,str);
		str.Format("%d",64-h-c);
		SetDlgItemText(IDC_LBL_N_CH,str);
		break;
	case GM_STEPLIST:
		h=(char)(lParam>>14);
		if(!h){
			h=(lParam>>8) & 0xff;
			c=lParam & 0x7f;
			i=GetX_ch(c)-1;
			if(!m_Graph.m_WBBW)i=7-i;
			str.Format("%d",h);
			h = m_lstStep.InsertItem(h, str, 0);

			str = (lParam&0x80?"��":"��");
			m_lstStep.SetItemText(h, 1, str);

			str.Format("%c%d",  i+'A', GetY_ch(c));
			m_lstStep.SetItemText(h, 2, str);
		}else{
			for(i=m_lstStep.GetItemCount();h&&i;h--)
				m_lstStep.DeleteItem(--i);
		}
		break;
	case GM_SETPIECE:
		SetDlgItemText(IDC_STATIC_BNAME,m_PlayerName[m_PlayerType[0]]);
		SetDlgItemText(IDC_STATIC_WNAME,m_PlayerName[m_PlayerType[1]]);
		break;
	case GM_UNDO_REDO:
		ukey= MF_BYCOMMAND;
		if(lParam & 1) ukey |= MF_ENABLED;
		else ukey |= MF_DISABLED | MF_GRAYED;
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REGRET, ukey);

		ukey= MF_BYCOMMAND;
		if(lParam & 1) ukey |= MF_ENABLED;
		else ukey |= MF_DISABLED | MF_GRAYED;
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REDO, ukey);
		break;
	case GM_SOLVED:
		m_CT.EndThinking();
		SearchResult((SearchReport*)lParam);
		i=m_Game.GetLocTraceTop()-1;
		str.Format("%s��[%s],�Ѿ�����",((SearchReport*)lParam)->color?"��":"��",m_PlayerName[m_PlayerType[((SearchReport*)lParam)->color]]);
		SetDlgItemText(IDC_STATIC_COMMENT, str);
		m_SReport[i] = *((SearchReport*)lParam);
		delete (SearchReport*)lParam;
		TRACE("Show the Step %d, b:w=%d:%d\n", i, m_SReport[i].bw[0], m_SReport[i].bw[1]);
		break;
	case GM_REPORTTRACE:
		i=(lParam>>8)-1;
		c=lParam & 0x7f;
		if(i==254){
			m_Graph.m_Maybe = c;
			InvalidateRect(&m_GBRc, FALSE);
			UpdateWindow();
			break;
		}else if(i>4||i<0) 
			break;
		m_StackTrace[i*3]=GetX_ch(c)+'A'-1;
		m_StackTrace[i*3+1]=GetY_ch(c)+'0';
		m_StackTrace[i*3+2]=' ';
		m_StackTrace[i*3+3]=0;
		SetDlgItemText(IDC_STATIC_TRACE, m_StackTrace);
		break;
	case GM_SHOWDIAGRAM:
		OnMenuShowdiagram();
		break;
	case GM_GETREPORT:
		m_Game.GetSearchReport(m_SReport);
		break;
	case GM_TIMEOUT:
		SetDlgItemText(IDC_STATIC_COMMENT, "�����õ���˼����ʱ�޵���");
		break;
	}
	return 0;
} 

void COthelloDlg::OnMenuNewGame() 
{
	GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REGRET, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	m_CostTime[0]=0;
	m_CostTime[1]=0;
	m_Game.StartGame();
	memset(m_SReport, 0, 60*sizeof(SearchReport));
	SetDlgItemText(IDC_STATIC_BLACKTIME, "00:00");
	SetDlgItemText(IDC_STATIC_WHITETIME, "00:00");
	SetDlgItemText(IDC_STATIC_COMMENT, "�����¿�ʼ��һ�̶Ծ�");
	SetTimer(0, 1000, NULL);

	InvalidateRect(&m_GBRc, FALSE);
	UpdateWindow();
}

void COthelloDlg::OnRegret() 
{
	if(m_Game.Undo()){
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REDO, MF_BYCOMMAND | MF_ENABLED);
		InvalidateRect(&m_GBRc, FALSE);
		UpdateWindow();
		SetDlgItemText(IDC_STATIC_COMMENT, "�㽫���ƻ�����һ��");
	}else{
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REGRET, MF_BYCOMMAND | MF_ENABLED);
		SetDlgItemText(IDC_STATIC_COMMENT, "�Ծ��Ѿ����˵��˵�һ��");	
	}
}

void COthelloDlg::OnRedo() 
{
	if(!m_Game.Redo()){
		SetDlgItemText(IDC_STATIC_COMMENT, "�Ծ��Ѿ�ǰ�Ƶ������һ��");	
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}else{
		InvalidateRect(&m_GBRc, FALSE);
		UpdateWindow();
		SetDlgItemText(IDC_STATIC_COMMENT, "�����Ծ�ǰ����һ��");
	}
}

void COthelloDlg::OnOpen() 
{
	CFileDialog dlg(true, "*.oqp", "", OFN_HIDEREADONLY, "�����ļ�(*.oqp)|*.oqp|�����ļ�(*.hbq)|*.hbq||");
	SetDlgItemText(IDC_STATIC_COMMENT, "���ڲ��ҹ�ȥ�浵");

	if(dlg.DoModal()==IDOK){
		if(m_Game.RebuildGame((LPCTSTR)dlg.GetPathName())){
			InvalidateRect(&m_GBRc, FALSE);
			UpdateWindow();
			SetDlgItemText(IDC_STATIC_COMMENT, "�������˹�ȥ�ĶԾ�");
		}
	}
}

void COthelloDlg::OnSave() 
{
	SetDlgItemText(IDC_STATIC_COMMENT, "��Ӧѡ�񱣴�·��");

	CFileDialog dlg(false, "*.oqp", "�¶Ծ�", OFN_OVERWRITEPROMPT, "�����ļ�(*.oqp)|*.oqp||");
	if(dlg.DoModal()==IDOK){
		m_Game.SaveGame((LPCTSTR)dlg.GetPathName());
		SetDlgItemText(IDC_STATIC_COMMENT, "�Ծ��Ѿ��������");
	}
}

void COthelloDlg::OnSetComputerPiece() 
{
	CComputerPieceDlg dlg;
	dlg.m_BlackPlayer=m_PlayerType[0];
	dlg.m_WhitePlayer=m_PlayerType[1];
	SetDlgItemText(IDC_STATIC_COMMENT, "���������úڰ�˫���Ŀ�����");

	if(dlg.DoModal()==IDOK){
		int tmp[2];
		tmp[0]=dlg.m_BlackPlayer;
		tmp[1]=dlg.m_WhitePlayer;
		if(m_CT.SetStyle(tmp)){
			memcpy(m_PlayerType, tmp, 2*sizeof(int));
			m_Game.SetComputerSide(m_PlayerType);
			SendMessage(WM_GAMEMESSAGER,GM_SETPIECE,0);
			m_Keep=false;
		}
	}
}

void COthelloDlg::OnMenuBoardAbnormal() 
{
	if(m_Game.GetGameState()==1){
		if(m_WBBW==false) return;
		if(MessageBox("�Ƿ�������Ϸ", "��ʾ", MB_ICONQUESTION|MB_YESNO)!=IDYES) return;
	}
	GetMenu()->GetSubMenu(1)->GetSubMenu(0)->
		CheckMenuRadioItem(ID_MENU_BOARD_NORMAL,ID_MENU_BOARD_ABNORMAL,ID_MENU_BOARD_ABNORMAL,MF_BYCOMMAND);
	m_WBBW=m_Graph.m_WBBW=false;
	m_Game.StartGame();
	InvalidateRect(&m_GBRc, FALSE);
	UpdateWindow();
	SetDlgItemText(IDC_STATIC_COMMENT,"���̲��ֱ���Ϊ����ģʽ");
	m_Keep=false;
}

void COthelloDlg::OnMenuBoardNormal() 
{
	if(m_Game.GetGameState()==1){
		if(m_WBBW==true) return;
		if(MessageBox("�Ƿ�������Ϸ", "��ʾ", MB_ICONQUESTION|MB_YESNO)!=IDYES) return;
	}
	GetMenu()->GetSubMenu(1)->GetSubMenu(0)->
		CheckMenuRadioItem(ID_MENU_BOARD_NORMAL,ID_MENU_BOARD_ABNORMAL,ID_MENU_BOARD_NORMAL,MF_BYCOMMAND);
	m_WBBW=m_Graph.m_WBBW=true;	
	m_Game.StartGame();
	InvalidateRect(&m_GBRc, FALSE);
	UpdateWindow();
	SetDlgItemText(IDC_STATIC_COMMENT, "���̲��ֱ���Ϊ��׼ģʽ");
	m_Keep=false;
}

BOOL COthelloDlg::PreTranslateMessage(MSG* pMsg) 
{
//	if(m_bTraining && pMsg->hwnd !=m_hWnd && pMsg->hwnd !=m_StatusBar.m_hWnd)
//		return TRUE;

	if(WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST){    
		HACCEL hAccel = m_hAccel;    
		if (hAccel && ::TranslateAccelerator(m_hWnd, hAccel, pMsg))    
			return TRUE;
	}
	
	if( pMsg->hwnd == m_lstConsole.m_hWnd && pMsg->message == WM_RBUTTONUP){
		OnListConsoleRButtonUp(CPoint(LOWORD(pMsg->lParam), HIWORD(pMsg->lParam)));
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void COthelloDlg::OnMenuTopmost() 
{
	if(m_TopMost){
		GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_MENU_TOPMOST, MF_BYCOMMAND|MF_UNCHECKED);
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		m_TopMost = FALSE;
		SetDlgItemText(IDC_STATIC_COMMENT, "���������ö�ȡ����");
	}else{
		GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_MENU_TOPMOST, MF_BYCOMMAND|MF_CHECKED);
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		m_TopMost = TRUE;	
		SetDlgItemText(IDC_STATIC_COMMENT, "���������ö�");
	}
	m_Keep=false;
}

void COthelloDlg::OnMenuOpeningbook() 
{
	COpeningDlg dlg;
	SetDlgItemText(IDC_STATIC_COMMENT, "�����˿��ֿ�");
	if(dlg.DoModal()==IDOK){
		if(strlen(dlg.m_StepList)){
			if(m_Game.GetGameState()==1){
				if(MessageBox("�Ƿ�ȷ����ѡ�еĿ������¿�ʼ?","��ʾ",MB_ICONQUESTION|MB_YESNO)==IDNO)
					return;
			}
			m_Game.OpeningGame(dlg.m_StepList);	// apply the opening
			SetDlgItemText(IDC_STATIC_COMMENT, "��ʹ���˶�ʽ����");
		}
	}
}

void COthelloDlg::OnMenuOpenlibrary() 
{
	SetDlgItemText(IDC_STATIC_COMMENT, "�����˶Ծֿ�");
	if(m_LibraryName==""){
		CFileDialog dlg(true, "*.wtb", "", OFN_HIDEREADONLY, "�Ծֿ��ļ�(*.wtb)|*.wtb||");
		if(dlg.DoModal()==IDOK){
			m_LibraryName= dlg.GetPathName();
		}else
			return ;
	}
	CLibraryViewDlg lvDlg;
	lvDlg.lpszPathName = m_LibraryName;
	if(lvDlg.DoModal()==IDOK){
		if(m_Game.GetGameState()==1)
			if(MessageBox("�Ƿ�ȷ����ʾѡ�еĶԾ�?","��ʾ",MB_ICONQUESTION|MB_YESNO)==IDNO)
					return;
		m_Game.OpeningGame(lvDlg.m_Item);	// apply the opening
		SetDlgItemText(IDC_STATIC_COMMENT, "�������ֶԾֿ��еĶԾ�,������,�Ҽ��鿴");
	}
}

void COthelloDlg::OnMenuComputerRefresh() 
{
	PostMessage(WM_GAMEMESSAGER, GM_COMPUTER_RUN, 0);
	SetDlgItemText(IDC_STATIC_COMMENT, "����������һ��");
}

void COthelloDlg::OnAboutbox() 
{
	CAboutBox dlgAbout;
	dlgAbout.DoModal();	
}

void COthelloDlg::OnMenuLocsound() 
{
	UINT ukey=(m_LocSound? MF_UNCHECKED: MF_CHECKED);
	GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_MENU_LOCSOUND, MF_BYCOMMAND|ukey);
	m_LocSound=!m_LocSound;
	m_Game.m_PlaySound = m_LocSound;

	if(m_LocSound)
		SetDlgItemText(IDC_STATIC_COMMENT, "����ʹ����������");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "��������������");
	m_Keep=false;
}

void COthelloDlg::OnMenuStopsearch() 
{
	m_CT.StopSearch();
 	SetDlgItemText(IDC_STATIC_COMMENT, "����ֹ�˵��Ե�˼��");
}

void COthelloDlg::OnMenuHintpoint() 
{
	UINT ukey=(m_ShowHint? MF_UNCHECKED: MF_CHECKED);
	GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_MENU_HINTPOINT, MF_BYCOMMAND|ukey);
	m_ShowHint=!m_ShowHint;
	m_Graph.m_ShowHint=m_ShowHint;
	InvalidateRect(&m_GBRc, FALSE);
	UpdateWindow();
	if(m_ShowHint)
		SetDlgItemText(IDC_STATIC_COMMENT, "���������ʾ�����ӵ�");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "�����˵�����ʾ�����ӵ�");
	m_Keep=false;
}

void COthelloDlg::SearchResult(SearchReport *sr)
{
	char buf[10];
	CString vstr;
	sprintf(buf,"%5f", sr->value);
	buf[5]=0;
	SetDlgItemText(IDC_STATIC_VAL,buf);
	sprintf(buf,"%5f", sr->time);
	buf[5]='s';	buf[6]=0;
	SetDlgItemText(IDC_STATIC_TIME,buf);
	
	ASSERT(sr->nodes>=0);	
	int i=GetX_ch(sr->best)-1;
	if(!m_Graph.m_WBBW)i=7-i;
	sprintf(buf,"%c%d", i+'A', GetY_ch(sr->best));
	CString tmpstr;
	if(sr->nodes!=0){
		if(sr->time)
			vstr.Format("%.3f",(sr->nodes/sr->time)/1000);
		else vstr="+INF";
		m_CInfo.Format("������%s��[%s]ִ��\r\n������ʱ:%.3f��\r\n�����ڵ�:%ld\r\n�����ٶ�:%sknps\r\n���Ž�:%s\r\n���Ź�ֵ:%.2f\0",
			(sr->color?"��":"��"), (m_PlayerName[m_PlayerType[sr->color]]), (sr->time), (sr->nodes), vstr, buf, (sr->value));
	
	}else{
		m_CInfo.Format("������%s��[%s]ִ��\r\nͨ����������\r\n�������Ž�:%s\r\n���Ź�ֵ:%.2f\0",
			(sr->color?"��":"��"), (m_PlayerName[m_PlayerType[sr->color]]), buf, (sr->value));	

	}

	tmpstr.Format("%2d.%c[%s] %2d:%2d %s %.3fs %d%s %sknps %s %.2f\0", 
			((sr->bw[0])+(sr->bw[1])-4), (sr->color?'W':'B'),
			(m_PlayerName[m_PlayerType[sr->color]]),
			(sr->bw[0]), (sr->bw[1]), (sr->nodes? "": "FDIN_BOOK"), (sr->time), 
			(sr->nodes>10000?sr->nodes/1000:sr->nodes), 
			(sr->nodes>10000?"k":""), vstr, buf, (sr->value));

	m_lstConsole.AddString(tmpstr);
	m_lstConsole.SetCurSel(m_lstConsole.GetCount()-1);

	UpdateData(FALSE);
}

void COthelloDlg::OnCancel() 
{
	EchoEndCommand();
}


void COthelloDlg::OnMenuHelpContent() 
{
	HINSTANCE hRun = ShellExecute(GetParent()->GetSafeHwnd(), _T("open"), "othello.chm", NULL, NULL, SW_SHOW);
	if ((int) hRun <= 32){
		MessageBox("�Ҳ��������ĵ�!","��ʾ", MB_ICONEXCLAMATION);
		TRACE("Failed to invoke URL using ShellExecute\n");
		return;
	}	
}

HBRUSH COthelloDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	ASSERT(nCtlColor!=IDC_SBARCTRL_MAIN);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);

	return m_Brush;
}


void COthelloDlg::OnMenuChessbook() 
{
	UINT ukey=(m_UseBook? MF_UNCHECKED: MF_CHECKED);
	GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_MENU_CHESSBOOK, MF_BYCOMMAND|ukey);
	m_UseBook=!m_UseBook;
	m_CT.SetUseBook(m_UseBook);
	if(m_UseBook)
		SetDlgItemText(IDC_STATIC_COMMENT, "�������ʹ�ÿ�������");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "�����˵���ʹ�ÿ�������");
	m_Keep=false;
}

void COthelloDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==0){
		char buf[10];
		int NowColor=m_Game.GetColor();
		int ctrlID=IDC_STATIC_BLACKTIME;
		m_CostTime[NowColor]++;
		sprintf(buf, "%.2d:%.2d", m_CostTime[NowColor]/60, m_CostTime[NowColor]%60);
		if(NowColor == 1)ctrlID=IDC_STATIC_WHITETIME;
		SetDlgItemText(ctrlID, buf);
	}
	CDialog::OnTimer(nIDEvent);
}

void COthelloDlg::OnMenuShowdata() 
{
	UINT ukey=(m_ShowData? MF_UNCHECKED: MF_CHECKED);
	GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_MENU_SHOWDATA, MF_BYCOMMAND|ukey);
	m_ShowData=!m_ShowData;
	m_Graph.m_ShowData = m_ShowData;
	if(m_ShowData)
		SetDlgItemText(IDC_STATIC_COMMENT, "���õ�����ʾ������������");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "�����˵�����ʾ������������");

	m_Keep=false;	
}

void COthelloDlg::OnMenuAnimation() 
{
	UINT ukey=(m_bAnimation? MF_UNCHECKED: MF_CHECKED);
	GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_MENU_ANIMATION, MF_BYCOMMAND|ukey);
	m_bAnimation=!m_bAnimation;
	m_Game.SetAnimation(m_bAnimation);
	if(m_bAnimation)
		SetDlgItemText(IDC_STATIC_COMMENT, "���õ�����ʾ���Ӷ���");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "�����˵�����ʾ���Ӷ���");

	m_Keep=false;
	
}


void COthelloDlg::EchoGM_GameOver(LPARAM lParam)
{
	char h, c;
	CString str;
	h=(lParam & 0xff00)>>8;
	c=lParam & 255;
	str.Format("��Ϸ����--%2d:%2d ",h,h-c);
	if(c){
		if(c>0)str+="��";
		if(c<0)str+="��";
		str+="��[";
		str+=m_PlayerName[m_PlayerType[(c>0?0:1)]];
		str+="]ʤ!";
	}else str+="ƽ��!";
	SetDlgItemText(IDC_STATIC_COMMENT, str);
	str.SetAt(8, '\r');str.SetAt(9, '\n');
	KillTimer(0);
	MessageBox(str,"���Ľ���",MB_ICONINFORMATION);
	PostMessage(WM_GAMEMESSAGER, GM_SHOWDIAGRAM, 0);
}

void COthelloDlg::OnMenuShowdiagram() 
{
	CDiagramDlg ddlg;
	ddlg.m_SRHead= m_SReport;
	ddlg.m_SRTop = m_Game.GetLocTraceTop();
	ddlg.DoModal();	
}

void COthelloDlg::OnMenuOpendiagram() 
{
	SetDlgItemText(IDC_STATIC_COMMENT, "�����˷���ͼ");
	CString strfile;
	CFileDialog dlg(true, "*.oad", "", OFN_HIDEREADONLY, "����ͼ�ļ�(*.oad)|*.oad||");
	if(dlg.DoModal()==IDOK){
		strfile= dlg.GetPathName();
	}else
		return ;
	CFile file;
	CFileException ex;
	if(!file.Open(strfile, CFile::modeRead, &ex)){
		MessageBox("�ļ���ռ��!", "����", MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	SearchReport asr[60];
	CDiagramDlg ddlg;
	ddlg.m_SRTop=file.Read(asr, sizeof(SearchReport)*60)/sizeof(SearchReport);
	ddlg.m_SRHead=asr;
	file.Close();
	ddlg.DoModal();
}

void COthelloDlg::OnMenuSavediagram() 
{
	SetDlgItemText(IDC_STATIC_COMMENT, "�������˷���ͼ");
	CString strfile;
	CFileDialog dlg(false, "*.oad", "", OFN_OVERWRITEPROMPT, "����ͼ�ļ�(*.oad)|*.oad||");
	if(dlg.DoModal()==IDOK){
		strfile= dlg.GetPathName();
	}else
		return ;
	CFile file;
	CFileException ex;
	if(!file.Open(strfile, CFile::modeCreate | CFile::modeWrite, &ex)){
		MessageBox("�ļ���ռ��!", "����", MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	file.Write(m_SReport, sizeof(SearchReport)*m_Game.GetLocTraceTop());
	file.Close();

}

void COthelloDlg::OnMenuSetlimited() 
{
	CSetTimeLimitDlg stlDlg;
	stlDlg.m_iTime = m_TimeLimit;
	if(stlDlg.DoModal()==IDOK){
		m_TimeLimit=stlDlg.m_iTime;
		m_Keep=false;
	}
}

void COthelloDlg::OnOK() 
{
	EchoCmdLine();
}

void COthelloDlg::EchoCmdLine()
{
	CString cmdLine;
	GetDlgItemText(IDC_COMBO_CMD, cmdLine);
	cmdLine.TrimLeft();
	cmdLine.TrimRight();

	CString cmd = cmdLine.Left(3); 

	if(!cmd.Compare("CMD")){
		MessageBox(
			"CLS\t\t������\r\n"
			"END\t\t�˳�����\r\n"
			"LOC xx\t\t��xx�����ӣ���LOC A8Ϊ��A8������\r\n"
			"NEW\t\t������Ϸ\r\n"
			"SET [B/W]=x\t���úڰ׷�ִ�壬��SET B=0 W=1Ϊ��ڷ�Ϊ�˰׷����\r\n"
			, "��������ʾ", MB_ICONINFORMATION | MB_OK);
		return;
	}
	if(!cmd.Compare("CLS")){
		OnMenuConsoleClear();
		return;
	}
	if(!cmd.Compare("END")){
		EchoEndCommand();
		return;
	}
	if(!cmd.Compare("NEW")){
		OnMenuNewGame();
		return;
	}
	if(!cmd.Compare("LOC")){
		int x, y;
		x = cmdLine.GetAt(4)-'A'+1;
		y = cmdLine.GetAt(5)-'0';
		EchoLocChess(x, y);
		return;
	}
	MessageBox("�����������������CMD�����Ѱ��", "��ʾ", MB_ICONINFORMATION);
	SetDlgItemText(IDC_COMBO_CMD, "");
}

void COthelloDlg::EchoEndCommand()
{
	if(m_Game.GetGameState()==1){
		if(MessageBox("��Ϸ��δ����,ȷ���˳���?", "��ʾ", MB_ICONQUESTION | MB_YESNO)==IDNO)
			return;
		m_Game.EndGame();
	}
	
	CDialog::OnCancel();
}

void COthelloDlg::OnListConsoleRButtonUp(CPoint pt)
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_POPUP1);

	m_lstConsole.ClientToScreen(&pt);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			pt.x, pt.y, this);
}

void COthelloDlg::OnMenuConsoleClear() 
{
	while(m_lstConsole.DeleteString(0));
}

void COthelloDlg::OnMenuConsoleSave() 
{
	SetDlgItemText(IDC_STATIC_COMMENT, "�������˿���̨���");
	CString strfile;
	CFileDialog dlg(false, "*.txt", "", OFN_OVERWRITEPROMPT, "����̨���(*.txt)|*.txt|����̨��¼(*.log)|*.log||");
	if(dlg.DoModal()==IDOK){
		strfile= dlg.GetPathName();
	}else
		return;
	CFile file;
	CFileException ex;
	if(!file.Open(strfile, CFile::modeCreate | CFile::modeWrite, &ex)){
		MessageBox("�ļ���ռ��!", "����", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	char str[1024];
	int len;
	for(int i= 0; i<m_lstConsole.GetCount(); i++){
		len = m_lstConsole.GetText(i, str);
		str[len++]='\r';str[len++]='\n';
		file.Write(str, len);
	}
	file.Close();
}

void COthelloDlg::EchoLocChess(int x, int y)
{
	x = m_Graph.TransformXY(x, y);
	if(m_Game.EchoClick(x)){
		y=m_Game.GetLocTraceTop()-1;
		m_SReport[y].best = 0;
		m_SReport[y].nodes = 0;
		m_SReport[y].time = 0;
		m_SReport[y].value = 0;
		m_SReport[y].color = 0;
		m_Game.GetChessCount(m_SReport[y].bw);
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REGRET, MF_BYCOMMAND | MF_ENABLED);
	}
}

void COthelloDlg::OnMenuPausegame() 
{
	if(m_Game.GetGameState()==1){
		m_CT.PauseGame();
		if(m_CT.GetPause())
			SetDlgItemText(IDC_STATIC_COMMENT, "����ͣ�˵������ӵ�Ȩ��");
		else
			SetDlgItemText(IDC_STATIC_COMMENT, "���ָ��˵������ӵ�Ȩ��");
	}
}

void COthelloDlg::OnMenuTurnL() 
{
	m_Graph.Rotate(false);
	InvalidateRect(&m_GBRc, FALSE);
	UpdateWindow();
}

void COthelloDlg::OnMenuTurnR() 
{
	m_Graph.Rotate(true);
	InvalidateRect(&m_GBRc, FALSE);
	UpdateWindow();
}

void COthelloDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutBox dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void COthelloDlg::OnMenuTraining() 
{
	MessageBox("�����ܽ�����ѧϰѵ������ʾ��ѵ��Ч�ʱȽϵ͡�\n�����ҪӦ�õ�ģ��ѵ������ʹ�ø�����coach.exe���ߡ�","��ʾ");
	m_Game.EndGame();
	::Sleep(100);
//	OnMenuNewGame();	
}
