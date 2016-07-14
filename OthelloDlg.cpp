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
	"人"  ,"随便","大食","制动","静估","稳估",
	"飞雀","飞燕","飞鹤","斑鸠","山雕","猎隼",
	"银鼠","玉兔","金犬","火狐","雄狮","神龟",
	"雷神"
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
		strAboutMenu="关于Othello(&A)...";//.LoadString(IDS_ABOUTBOX);
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
	m_StatusBar.SetBkColor(RGB(41,115,66));		// 背景色
	int arWidth[] = { 28, 48, 68, 96, 116, 136, 156, 176, 196, 226, 246, 281, -1 };
	m_StatusBar.SetParts(13, arWidth);				// 分栏
	m_StatusBar.SetText("jjj", 1, 0);	// 第一个栏的文本
	m_StatusBar.SetText("ij ", 0, 0);				// 第二个栏的文本
//	m_StatusBar.GetDlgItem(1)->GetDC()->SetTextColor(0xffffff);
#endif
	m_hAccel = ::LoadAccelerators(AfxGetResourceHandle(),    
                  MAKEINTRESOURCE(IDR_ACCELERATOR_MAIN));   //快捷键表id  
    ASSERT(m_hAccel); 
	
	m_lstStep.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lstStep.InsertColumn(0, "No.", LVCFMT_LEFT, 20);
	m_lstStep.InsertColumn(1, "颜色", LVCFMT_LEFT, 35);
	m_lstStep.InsertColumn(2, "应招", LVCFMT_LEFT, 80);

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
		if(m_WBBW){ //棋盘分布
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
	m_CInfo.Format("内存占用情况:\r\n类CGame:%dbytes\r\n"
		"类CGraph:%dbytes\r\n类CComputerThink:%dbytes\r\n"
		"类CGameScript:%dbytes\r\n类COpeningReader:%dbytes",
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
		str.Format("正在等待%s方[%s]落子",i?"白":"黑",m_PlayerName[m_PlayerType[i]]);
		SetDlgItemText(IDC_STATIC_COMMENT, str);
		m_CT.StartToThink();
		m_CT.SetTimeLimit(m_TimeLimit);
		break;
	case GM_GAME_OVER:
		EchoGM_GameOver(lParam);
		break;
	case GM_HAVE_TO_SKIP:
		if(lParam==B_CH){
			str="白方[";
			i=1;
		}else{ 
			str="黑方[";
			i=0;
		}
		str+=m_PlayerName[m_PlayerType[i]];
		str+="]无法落子, 必须停一手!";
		SetDlgItemText(IDC_STATIC_COMMENT, str);		
		MessageBox(str,"提示",MB_ICONINFORMATION);
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

			str = (lParam&0x80?"黑":"白");
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
		str.Format("%s方[%s],已经落子",((SearchReport*)lParam)->color?"白":"黑",m_PlayerName[m_PlayerType[((SearchReport*)lParam)->color]]);
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
		SetDlgItemText(IDC_STATIC_COMMENT, "您设置电脑思考的时限到了");
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
	SetDlgItemText(IDC_STATIC_COMMENT, "您重新开始了一盘对局");
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
		SetDlgItemText(IDC_STATIC_COMMENT, "你将局势回退了一步");
	}else{
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REGRET, MF_BYCOMMAND | MF_ENABLED);
		SetDlgItemText(IDC_STATIC_COMMENT, "对局已经回退到了第一步");	
	}
}

void COthelloDlg::OnRedo() 
{
	if(!m_Game.Redo()){
		SetDlgItemText(IDC_STATIC_COMMENT, "对局已经前移到了最后一步");	
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_MENU_REDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}else{
		InvalidateRect(&m_GBRc, FALSE);
		UpdateWindow();
		SetDlgItemText(IDC_STATIC_COMMENT, "您将对局前移了一步");
	}
}

void COthelloDlg::OnOpen() 
{
	CFileDialog dlg(true, "*.oqp", "", OFN_HIDEREADONLY, "棋谱文件(*.oqp)|*.oqp|棋谱文件(*.hbq)|*.hbq||");
	SetDlgItemText(IDC_STATIC_COMMENT, "您在查找过去存档");

	if(dlg.DoModal()==IDOK){
		if(m_Game.RebuildGame((LPCTSTR)dlg.GetPathName())){
			InvalidateRect(&m_GBRc, FALSE);
			UpdateWindow();
			SetDlgItemText(IDC_STATIC_COMMENT, "您重现了过去的对局");
		}
	}
}

void COthelloDlg::OnSave() 
{
	SetDlgItemText(IDC_STATIC_COMMENT, "您应选择保存路径");

	CFileDialog dlg(false, "*.oqp", "新对局", OFN_OVERWRITEPROMPT, "棋谱文件(*.oqp)|*.oqp||");
	if(dlg.DoModal()==IDOK){
		m_Game.SaveGame((LPCTSTR)dlg.GetPathName());
		SetDlgItemText(IDC_STATIC_COMMENT, "对局已经保存完毕");
	}
}

void COthelloDlg::OnSetComputerPiece() 
{
	CComputerPieceDlg dlg;
	dlg.m_BlackPlayer=m_PlayerType[0];
	dlg.m_WhitePlayer=m_PlayerType[1];
	SetDlgItemText(IDC_STATIC_COMMENT, "您可以设置黑白双方的控制者");

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
		if(MessageBox("是否重新游戏", "提示", MB_ICONQUESTION|MB_YESNO)!=IDYES) return;
	}
	GetMenu()->GetSubMenu(1)->GetSubMenu(0)->
		CheckMenuRadioItem(ID_MENU_BOARD_NORMAL,ID_MENU_BOARD_ABNORMAL,ID_MENU_BOARD_ABNORMAL,MF_BYCOMMAND);
	m_WBBW=m_Graph.m_WBBW=false;
	m_Game.StartGame();
	InvalidateRect(&m_GBRc, FALSE);
	UpdateWindow();
	SetDlgItemText(IDC_STATIC_COMMENT,"棋盘布局被设为镜像模式");
	m_Keep=false;
}

void COthelloDlg::OnMenuBoardNormal() 
{
	if(m_Game.GetGameState()==1){
		if(m_WBBW==true) return;
		if(MessageBox("是否重新游戏", "提示", MB_ICONQUESTION|MB_YESNO)!=IDYES) return;
	}
	GetMenu()->GetSubMenu(1)->GetSubMenu(0)->
		CheckMenuRadioItem(ID_MENU_BOARD_NORMAL,ID_MENU_BOARD_ABNORMAL,ID_MENU_BOARD_NORMAL,MF_BYCOMMAND);
	m_WBBW=m_Graph.m_WBBW=true;	
	m_Game.StartGame();
	InvalidateRect(&m_GBRc, FALSE);
	UpdateWindow();
	SetDlgItemText(IDC_STATIC_COMMENT, "棋盘布局被设为标准模式");
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
		SetDlgItemText(IDC_STATIC_COMMENT, "您将窗体置顶取消了");
	}else{
		GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_MENU_TOPMOST, MF_BYCOMMAND|MF_CHECKED);
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		m_TopMost = TRUE;	
		SetDlgItemText(IDC_STATIC_COMMENT, "您将窗体置顶");
	}
	m_Keep=false;
}

void COthelloDlg::OnMenuOpeningbook() 
{
	COpeningDlg dlg;
	SetDlgItemText(IDC_STATIC_COMMENT, "您打开了开局库");
	if(dlg.DoModal()==IDOK){
		if(strlen(dlg.m_StepList)){
			if(m_Game.GetGameState()==1){
				if(MessageBox("是否确定以选中的开局重新开始?","提示",MB_ICONQUESTION|MB_YESNO)==IDNO)
					return;
			}
			m_Game.OpeningGame(dlg.m_StepList);	// apply the opening
			SetDlgItemText(IDC_STATIC_COMMENT, "您使用了定式开局");
		}
	}
}

void COthelloDlg::OnMenuOpenlibrary() 
{
	SetDlgItemText(IDC_STATIC_COMMENT, "您打开了对局库");
	if(m_LibraryName==""){
		CFileDialog dlg(true, "*.wtb", "", OFN_HIDEREADONLY, "对局库文件(*.wtb)|*.wtb||");
		if(dlg.DoModal()==IDOK){
			m_LibraryName= dlg.GetPathName();
		}else
			return ;
	}
	CLibraryViewDlg lvDlg;
	lvDlg.lpszPathName = m_LibraryName;
	if(lvDlg.DoModal()==IDOK){
		if(m_Game.GetGameState()==1)
			if(MessageBox("是否确定显示选中的对局?","提示",MB_ICONQUESTION|MB_YESNO)==IDNO)
					return;
		m_Game.OpeningGame(lvDlg.m_Item);	// apply the opening
		SetDlgItemText(IDC_STATIC_COMMENT, "电脑重现对局库中的对局,可以左,右键查看");
	}
}

void COthelloDlg::OnMenuComputerRefresh() 
{
	PostMessage(WM_GAMEMESSAGER, GM_COMPUTER_RUN, 0);
	SetDlgItemText(IDC_STATIC_COMMENT, "电脑重新落一子");
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
		SetDlgItemText(IDC_STATIC_COMMENT, "允许使用落子声音");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "禁用了落子声音");
	m_Keep=false;
}

void COthelloDlg::OnMenuStopsearch() 
{
	m_CT.StopSearch();
 	SetDlgItemText(IDC_STATIC_COMMENT, "您中止了电脑的思考");
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
		SetDlgItemText(IDC_STATIC_COMMENT, "允许电脑提示可落子点");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "禁用了电脑提示可落子点");
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
		m_CInfo.Format("电脑以%s方[%s]执棋\r\n搜索耗时:%.3f秒\r\n搜索节点:%ld\r\n搜索速度:%sknps\r\n最优解:%s\r\n最优估值:%.2f\0",
			(sr->color?"白":"黑"), (m_PlayerName[m_PlayerType[sr->color]]), (sr->time), (sr->nodes), vstr, buf, (sr->value));
	
	}else{
		m_CInfo.Format("电脑以%s方[%s]执棋\r\n通过开局棋谱\r\n搜索最优解:%s\r\n最优估值:%.2f\0",
			(sr->color?"白":"黑"), (m_PlayerName[m_PlayerType[sr->color]]), buf, (sr->value));	

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
		MessageBox("找不到帮助文档!","提示", MB_ICONEXCLAMATION);
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
		SetDlgItemText(IDC_STATIC_COMMENT, "允许电脑使用开局棋谱");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "禁用了电脑使用开局棋谱");
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
		SetDlgItemText(IDC_STATIC_COMMENT, "您让电脑显示开局棋谱数据");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "禁用了电脑显示开局棋谱数据");

	m_Keep=false;	
}

void COthelloDlg::OnMenuAnimation() 
{
	UINT ukey=(m_bAnimation? MF_UNCHECKED: MF_CHECKED);
	GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_MENU_ANIMATION, MF_BYCOMMAND|ukey);
	m_bAnimation=!m_bAnimation;
	m_Game.SetAnimation(m_bAnimation);
	if(m_bAnimation)
		SetDlgItemText(IDC_STATIC_COMMENT, "您让电脑显示落子动画");
	else
		SetDlgItemText(IDC_STATIC_COMMENT, "禁用了电脑显示落子动画");

	m_Keep=false;
	
}


void COthelloDlg::EchoGM_GameOver(LPARAM lParam)
{
	char h, c;
	CString str;
	h=(lParam & 0xff00)>>8;
	c=lParam & 255;
	str.Format("游戏结束--%2d:%2d ",h,h-c);
	if(c){
		if(c>0)str+="黑";
		if(c<0)str+="白";
		str+="方[";
		str+=m_PlayerName[m_PlayerType[(c>0?0:1)]];
		str+="]胜!";
	}else str+="平局!";
	SetDlgItemText(IDC_STATIC_COMMENT, str);
	str.SetAt(8, '\r');str.SetAt(9, '\n');
	KillTimer(0);
	MessageBox(str,"对弈结束",MB_ICONINFORMATION);
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
	SetDlgItemText(IDC_STATIC_COMMENT, "您打开了分析图");
	CString strfile;
	CFileDialog dlg(true, "*.oad", "", OFN_HIDEREADONLY, "分析图文件(*.oad)|*.oad||");
	if(dlg.DoModal()==IDOK){
		strfile= dlg.GetPathName();
	}else
		return ;
	CFile file;
	CFileException ex;
	if(!file.Open(strfile, CFile::modeRead, &ex)){
		MessageBox("文件被占用!", "错误", MB_ICONEXCLAMATION | MB_OK);
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
	SetDlgItemText(IDC_STATIC_COMMENT, "您保存了分析图");
	CString strfile;
	CFileDialog dlg(false, "*.oad", "", OFN_OVERWRITEPROMPT, "分析图文件(*.oad)|*.oad||");
	if(dlg.DoModal()==IDOK){
		strfile= dlg.GetPathName();
	}else
		return ;
	CFile file;
	CFileException ex;
	if(!file.Open(strfile, CFile::modeCreate | CFile::modeWrite, &ex)){
		MessageBox("文件被占用!", "错误", MB_ICONEXCLAMATION | MB_OK);
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
			"CLS\t\t清空输出\r\n"
			"END\t\t退出程序\r\n"
			"LOC xx\t\t在xx处落子，如LOC A8为在A8处落子\r\n"
			"NEW\t\t重新游戏\r\n"
			"SET [B/W]=x\t设置黑白方执棋，如SET B=0 W=1为设黑方为人白方随便\r\n"
			, "命令行提示", MB_ICONINFORMATION | MB_OK);
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
	MessageBox("命令输入错误，详情用CMD命令查寻。", "提示", MB_ICONINFORMATION);
	SetDlgItemText(IDC_COMBO_CMD, "");
}

void COthelloDlg::EchoEndCommand()
{
	if(m_Game.GetGameState()==1){
		if(MessageBox("游戏尚未结束,确定退出吗?", "提示", MB_ICONQUESTION | MB_YESNO)==IDNO)
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
	SetDlgItemText(IDC_STATIC_COMMENT, "您保存了控制台输出");
	CString strfile;
	CFileDialog dlg(false, "*.txt", "", OFN_OVERWRITEPROMPT, "控制台输出(*.txt)|*.txt|控制台纪录(*.log)|*.log||");
	if(dlg.DoModal()==IDOK){
		strfile= dlg.GetPathName();
	}else
		return;
	CFile file;
	CFileException ex;
	if(!file.Open(strfile, CFile::modeCreate | CFile::modeWrite, &ex)){
		MessageBox("文件被占用!", "错误", MB_ICONEXCLAMATION | MB_OK);
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
			SetDlgItemText(IDC_STATIC_COMMENT, "您暂停了电脑落子的权利");
		else
			SetDlgItemText(IDC_STATIC_COMMENT, "您恢复了电脑落子的权利");
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
	MessageBox("本功能仅仅是学习训练的演示，训练效率比较低。\n如果需要应用的模板训练，请使用附带的coach.exe工具。","提示");
	m_Game.EndGame();
	::Sleep(100);
//	OnMenuNewGame();	
}
