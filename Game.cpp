// Game.cpp: implementation of the CGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "Game.h"
#include<mmsystem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const ChessType CGame::Init_Board[CH_LEN]={
BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,
BLOCK,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,
BLOCK,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,
BLOCK,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,

BLOCK,	N_CH,	N_CH,	N_CH,	W_CH,	B_CH,	N_CH,	N_CH,	N_CH,
BLOCK,	N_CH,	N_CH,	N_CH,	B_CH,	W_CH,	N_CH,	N_CH,	N_CH,

BLOCK,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,
BLOCK,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,
BLOCK,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,	N_CH,
BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,	BLOCK,
BLOCK
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGame::CGame():m_bEnd(false)
{
	m_B2W=0;
}

CGame::~CGame()
{
}

void CGame::StartGame(){
	ClearBoard(m_map);
	m_GS.StartClean();
	m_bEnd = false;
	m_B2W=0;
	m_BlackLoc = TRUE;
	m_HintCounter = m_GS.FindLocablePt(B_CH, m_map, m_HintPt);
	m_GameState = 1;
	m_FlipSecTop=m_FlipSec;
	m_FlipHistoryTop=m_FlipHistory;
	m_LocTop = m_LocMaxTop = m_LocHistory;
	PostMessage(m_Owner, WM_GAMEMESSAGER, GM_STATUSBAR, 0x202);

	if(m_ComputerAct[(m_BlackLoc?0:1)])	//电脑执棋
		PostMessage(m_Owner, WM_GAMEMESSAGER, GM_COMPUTER_RUN, 0);
}

bool CGame::EchoClick(int pos, char c)
{
	if(m_bEnd)
		return false;
	char Player=W_CH;
	LPARAM lp=0;
	if(m_BlackLoc)Player=B_CH;
	if(m_GameState!=1 || !c && m_ComputerAct[(m_BlackLoc?0:1)]) return false;
    if(m_GS.IsLocable(pos, Player, m_map)){
        *(m_FlipSecTop++) = m_GS.DoLoc(pos, Player, m_map, m_FlipHistoryTop)+1;
		*(m_LocTop++) = pos;
		m_LocMaxTop = m_LocTop;
		m_CurLoc = pos;
		ListStep(m_CurLoc, m_FlipSecTop-m_FlipSec, Player);
		m_HintCounter = 0;

		if(m_PlaySound){
			PlaySound(MAKEINTRESOURCE(IDR_WAVE1), //".\\res\\WAVE_SOUND.wav",//
				AfxGetInstanceHandle(), ///0,//
				SND_RESOURCE | SND_MEMORY | SND_APPLICATION | SND_NODEFAULT | SND_ASYNC );// SND_FILENAME
			::Sleep(20);
		}
		if(m_bDynamicShow){
			for(m_B2W=1; m_B2W<=4; m_B2W++){
				SendMessage(m_Owner, WM_GAMEMESSAGER, GM_LEGAL_OPERATION, 0); //显示新棋局
				Sleep(120);
			}
			m_B2W=0;
		}

		m_HintCounter = m_GS.FindLocablePt(Oppl_ch(Player),m_map,m_HintPt);
		Statistics();

		if(m_HintCounter)	//交换执棋
			m_BlackLoc=!m_BlackLoc;
		
		PostMessage(m_Owner, WM_GAMEMESSAGER, GM_LEGAL_OPERATION, 0); //显示新棋局

		if(!m_HintCounter){	//对方无法落子,交换执棋
			if(m_GS.IsGameOver(m_map)){	//游戏结束
				GameOver();
				return true;
			} else {	//对方无法行动, 继续执棋
				m_HintCounter = m_GS.FindLocablePt(Player,m_map,m_HintPt);
				SendMessage(m_Owner, WM_GAMEMESSAGER, GM_LEGAL_OPERATION, 0); //显示新棋局
				SendMessage(m_Owner, WM_GAMEMESSAGER, GM_HAVE_TO_SKIP, Player);
			}
		}

		if(m_ComputerAct[(m_BlackLoc?0:1)])	//电脑执棋
			PostMessage(m_Owner, WM_GAMEMESSAGER, GM_COMPUTER_RUN, 0);
		return true;
	}
	return false;
}

void CGame::SetOwner(HWND hwnd)
{
	m_Owner = hwnd;
}


void CGame::SetComputerSide(int* cs)
{
	m_ComputerAct[0] = (cs[0]!=0);
	m_ComputerAct[1] = (cs[1]!=0);
}

bool CGame::Undo()
{
	int i;
	ChessType Player;
	if(m_FlipSec>=m_FlipSecTop || m_GameState == 0)return false;
	i=*(--m_FlipSecTop);
	Player=m_map[*(--m_LocTop)];
	while(i--)
		m_map[*(--m_FlipHistoryTop)]=Oppl_ch(Player);
	m_map[*m_LocTop]=N_CH;

	m_HintCounter = m_GS.FindLocablePt(Player, m_map, m_HintPt);
	m_BlackLoc = (Player==B_CH);
	m_CurLoc = *(m_LocTop-1);
	PostMessage(m_Owner, WM_GAMEMESSAGER, GM_STEPLIST, 1<<14);// */
	Statistics();
	return true;
}

void CGame::ClearBoard(ChessType *map){
	memcpy(map, Init_Board, CH_LEN*sizeof(ChessType));
	SendMessage(m_Owner, WM_GAMEMESSAGER, GM_STEPLIST, 60<<14);
}

bool CGame::Redo()
{
	if(m_LocTop >= m_LocMaxTop || m_GameState == 0) return false;
	int cs, pos = *(m_LocTop++);
	ChessType col = (m_BlackLoc ? BLACK : WHITE);
	LPARAM lp;
	if(!m_map[pos] && m_GS.CountAnyFlip(pos, col, m_map)){
		*(m_FlipSecTop++)=m_GS.DoLoc(pos, col, m_map, m_FlipHistoryTop)+1;
		/*start to record located point*/
		cs= m_LocTop - m_LocHistory;
		lp=0;
		lp=pos;
		lp|=(col==B_CH?0x80:0);
		lp|=cs<<8;
		PostMessage(m_Owner, WM_GAMEMESSAGER, GM_STEPLIST, lp);

		m_HintCounter = m_GS.FindLocablePt(Oppl_ch(col), m_map, m_HintPt);
		if(m_HintCounter) m_BlackLoc = (col != B_CH);
		else m_HintCounter = m_GS.FindLocablePt(col, m_map, m_HintPt);

		m_CurLoc = pos;
		Statistics();

		/*recording located point finished*/
		return true;
	}
	return false;
}

bool CGame::SaveGame(const char* fp) const
{
	if(!m_GameState) return false;
	CFile fl(fp, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	CArchive ar(&fl,CArchive::store);
	UINT Key=MARK_KEYWORD;
	ar<<Key<<m_GameState<<m_ComputerAct[0]<<m_ComputerAct[1]<<int(m_LocTop-m_LocHistory);
	short *p=(short*)m_LocHistory;
	while(p<m_LocTop) ar<<*p++;
	ar.Close();
	fl.Close();
	return true;
}

bool CGame::RebuildGame(const char *fp)
{
	CFile fl(fp, CFile::modeRead);
	CArchive ar(&fl,CArchive::load);
	UINT Key;
	int top;
	int gamestate, cat1, cat2;
	ar>>Key;
	if(Key==MARK_KEYWORD){
		ar>>gamestate>>cat1>>cat2>>top;

		short stack[61];
		short *stacktop;
		stacktop=stack;

		while(top--) ar>>*stacktop++;
		*stacktop=0;
		if(BuildGame(stack)){
			m_GameState= gamestate;
			m_ComputerAct[0]=cat1!=0;
			m_ComputerAct[1]=cat2!=0;

			return true;
		}
	}
	ar.Close();
	fl.Close();
	return false;
}

int CGame::GetGameState() const
{
	return m_GameState;
}

void CGame::OpeningGame(char *step)
{
	short stack[61];
	short *stacktop;
	int x, y;
	char ctmp;
	ChessType color=B_CH;
	stacktop=stack;	

	while(*step){
		ctmp=*(step++);
		ASSERT((ctmp>='A'&&ctmp<='H')||(ctmp>='a'&&ctmp<='h'));
		if(ctmp>='A'&&ctmp<='H')
			x=ctmp-'A'+1;
		else
			x=ctmp-'a'+1;
		y=*(step++)-'0';
		ASSERT(y>=1&&y<=Y_UB);
		*stacktop++ = Conv(x, y);
	}
	*stacktop=0;
	if(BuildGame(stack)){
		if(!m_GS.IsGameOver(m_map)){
			m_GameState=1;
			if(m_ComputerAct[(m_BlackLoc?0:1)])	//电脑执棋
				PostMessage(m_Owner, WM_GAMEMESSAGER, GM_COMPUTER_RUN, 0);
		}
	}
}

bool CGame::InnerLoc(ChessType* map, int pos, ChessType *col, int cs, short *&flipSecTp, short *&flipHistoryTp, LPARAM* &lp, WPARAM* &wp)
{
    if(!map[pos] && m_GS.CountAnyFlip(pos, *col, map)){
        *(flipSecTp++)=m_GS.DoLoc(pos, *col, map, flipHistoryTp)+1;
		/*start to record located point*/
		*lp=0;
		*lp=pos;
		*lp|=(*col==B_CH?0x80:0);
		*(lp++)|=cs<<8;
		//*(wp++)=GM_STEPLIST;
		/*recording located point finished*/
		if(m_GS.FindLocablePt(Oppl_ch(*col), map))
			*col = Oppl_ch(*col);
		return true;
	}
	return false;
}

bool CGame::BuildGame(short *pos)
{
	ChessType color= B_CH; 
	ChessType tmpMap[CH_LEN];
	short *flipHistoryTop, flipHistory[1000];
	short *flipSecTop,FlipSec[60];
	short *locTop, locHistory[60];
	WPARAM *wpt, wps[60];
	LPARAM *lpt, lps[60];
	SearchReport *psr;
	int cst= 0;

	/* initialize stack top*/
	psr = m_SReport;
	flipHistoryTop = flipHistory;
	flipSecTop = FlipSec;
	locTop = locHistory;
	wpt = wps; 
	lpt = lps;
	/* stack top initialization finished*/
	memcpy(tmpMap, Init_Board, CH_LEN*sizeof(ChessType));

	while(*pos){
		cst++;
		psr->color =color;
		psr->best  =*pos;
		psr->nodes =0;
		psr->time  =0;
		psr->value =0;
		bool ret=InnerLoc(tmpMap, *pos, &color, cst, flipSecTop, flipHistoryTop, lpt, wpt);
		m_GS.CountChess(tmpMap, psr->bw);
		psr++;
		*(locTop++) = *pos++;
		ASSERT(ret);
		if(!ret) return false;
	}

	/* initialize the game*/
	memcpy(m_map, tmpMap, CH_LEN*sizeof(ChessType));
	memcpy(m_FlipHistory, flipHistory, (flipHistoryTop-flipHistory)*sizeof(short));
	m_FlipHistoryTop = m_FlipHistory+(flipHistoryTop-flipHistory);
	memcpy(m_FlipSec, FlipSec, (flipSecTop-FlipSec)*sizeof(short));
	m_FlipSecTop = m_FlipSec+(flipSecTop-FlipSec);
	memcpy(m_LocHistory, locHistory, (locTop-locHistory)*sizeof(short));
	m_LocTop = m_LocMaxTop = m_LocHistory+(locTop-locHistory);
	m_CurLoc = *(pos-1);
	m_HintCounter = m_GS.FindLocablePt(color, m_map, m_HintPt);
	m_BlackLoc = (color==B_CH);
	/* start to post message */
	wpt=wps;
	lpt=lps;
	SendMessage(m_Owner, WM_GAMEMESSAGER, GM_STEPLIST, 60<<14);
	while(cst--){
		PostMessage(m_Owner, WM_GAMEMESSAGER, GM_STEPLIST, *(lpt++));		
	}
	PostMessage(m_Owner, WM_GAMEMESSAGER, GM_LEGAL_OPERATION, 0);
	Statistics();
	PostMessage(m_Owner, WM_GAMEMESSAGER, GM_UNDO_REDO, 1);
	PostMessage(m_Owner, WM_GAMEMESSAGER, GM_GETREPORT, 0);
	return true;
}

int CGame::GetColor() const
{
	return 1-m_BlackLoc;
}


void CGame::SetAnimation(bool a)
{
	m_bDynamicShow = a;
}

short* CGame::GetLocTrace(int &len) const
{
	len = m_LocTop-m_LocHistory;
	return (short*)m_LocHistory;
}

int CGame::GetLocTraceTop() const
{
	return m_LocTop-m_LocHistory;
}

void CGame::GetChessCount(short *ret) const
{
	ASSERT(ret);
	if(m_GameState)
		m_GS.CountChess((ChessType*)m_map, ret);
}

void CGame::GetSearchReport(SearchReport *psr) const
{
	ASSERT(psr);
	memcpy(psr, m_SReport,60*sizeof(SearchReport));
}
void CGame::Statistics() const{
	LPARAM lp=0;
	lp|=m_GS.CountChess((ChessType*)m_map,B_CH);
	lp|=m_GS.CountChess((ChessType*)m_map,W_CH)<<8;
	PostMessage(m_Owner, WM_GAMEMESSAGER, GM_STATUSBAR, lp);
}
void CGame::ListStep(int pos, int i, char Player) const{
	LPARAM lp=0;
	lp=pos;
	lp|=(Player==B_CH?0x80:0);
	lp|=i<<8;
	PostMessage(m_Owner, WM_GAMEMESSAGER, GM_STEPLIST, lp);
}
void CGame::GameOver(){
	LPARAM lp=0;
	lp|=m_GS.WinPlayer(m_map)&0xff;
	lp|=(m_GS.CountChess(m_map,B_CH)<<8)&0xff00;
	PostMessage(m_Owner, WM_GAMEMESSAGER, GM_GAME_OVER, lp);
	m_GameState=2;
}

void CGame::EndGame()
{
	m_bEnd = true;	
}
