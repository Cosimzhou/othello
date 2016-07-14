// ComputerThink.cpp: implementation of the CComputerThink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "ComputerThink.h"

#include "ArtEngine.h"
#include "BasicEngine.h"
#include "SevenEngine.h"
#include "NankEngine.h"
#include "ThunderEngine.h"

#include "RowEvaluator.h"
#include "RegionEvaluator.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const char CComputerThink::m_EngMap[ENGINE_NUM]={
			0,	1,	1,	1,	1,
			1,	2,	2,	2,	4,
			4,	4,	3,	3,	3,
			3,	3,	3,	5
};
const int CComputerThink::m_EngAI[6]={	0,	1,	6,	12,	9,	18
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRITICAL_SECTION CComputerThink::m_CS;
HANDLE CComputerThink::m_hXLock = NULL;
bool CComputerThink::m_CSInited = false;
int CComputerThink::m_RLockCount = 0;

CComputerThink::CComputerThink()
{
	m_Player[0]=0;
	m_Player[1]=0;
	m_Eng[0]=m_Eng[1]=NULL;
	m_InUse=-1;
	m_iTimeLimit=0;
	m_hAIThread=NULL;
	m_DonotEcho = false;

	if(!m_CSInited){
		::InitializeCriticalSection(&m_CS);
		m_CSInited = true;
	}
	if(!m_hXLock){
		m_hXLock = ::CreateSemaphore(NULL, 1, 1, "OTHELLO_COMPUTER_THINKER_ENGINE");
	}
}

CComputerThink::~CComputerThink()
{
	if(m_CSInited==true){
		::DeleteCriticalSection(&m_CS);
	}
}



void CComputerThink::MakeDecision()
{
	ChessType	Mapt[CH_LEN];
	memcpy(Mapt, m_pG->m_map, CH_LEN*sizeof(ChessType));

	if(m_pG->m_BlackLoc){
		m_PlayColor=B_CH;
		m_InUse=0;
	}else{
		m_PlayColor=W_CH;
		m_InUse=1;
	}
	
	if(m_Player[m_InUse]){		// if the side is in the charge of computer
		int bm=0;
		ASSERT(Mapt[0]);
		if(m_pOR){			// look up the book
			short *trace;
			int len;
			trace = m_pG->GetLocTrace(len);
			if(m_pG->GetLocTraceTop() <= 4 || m_UseBook){
				if(m_pOR->Search(trace, len)){
					bm=m_pOR->Bestmove();
					if(!CGameScript::IsLocable(bm, m_PlayColor, Mapt)) bm=0;
				}
			}
		}
		SearchReport *sr=new SearchReport();
		ASSERT(Mapt[0]);
		if(bm==0){
			m_Eng[m_InUse]->Search(Mapt,m_PlayColor);
			bm=m_Eng[m_InUse]->BestMove();
			sr->nodes = m_Eng[m_InUse]->Nodes();
			sr->value = m_Eng[m_InUse]->BestScore();
			sr->time  = m_Eng[m_InUse]->Time()/1000.0;
		} else {
			sr->nodes = 0;
			sr->value = m_pOR->Bestscore();
			sr->time  = 0;
		}
		sr->best  = bm;
		sr->color = m_InUse;
		CGameScript::DoFlips(Mapt, bm, m_PlayColor, Oppl_ch(m_PlayColor));
		Mapt[bm]=m_PlayColor;
		CGameScript::CountChess(Mapt, sr->bw);
		m_InUse=-1;

		while(m_DonotEcho)
			Sleep(1000);
		m_pG->EchoClick(bm, m_PlayColor);		
		if(sr){
			PostMessage(m_Owner, WM_GAMEMESSAGER, GM_SOLVED, (LPARAM)sr);
		}
	}
}

bool CComputerThink::SetStyle(int* s)
{
	if(s[0]<0||s[0]>=ENGINE_NUM||s[1]<0||s[1]>=ENGINE_NUM) return false;
	if(m_EngMap[s[0]]==5||m_EngMap[s[1]]==5){
		WIN32_FIND_DATA wfd;
		HANDLE hRet = FindFirstFile("AI1.dll", &wfd);
		if(hRet){
			CloseHandle(hRet);
		}else
			return false;
	}	
	::WaitForSingleObject(m_hXLock, INFINITE);



	for(int i=0; i<2; i++){
		if(m_Player[i]==s[i]) continue;
		if(m_EngMap[m_Player[i]]==m_EngMap[s[i]]){
			m_Eng[i]->SetAI(s[i]-m_EngAI[m_EngMap[s[i]]]);
			m_Player[i]=s[i];
		}else{

			m_Player[i]=s[i];
			while(i==m_InUse);
			if(m_Eng[i]) delete m_Eng[i];
			switch(m_EngMap[s[i]]){
			case 0:
				m_Eng[i]=NULL;
				continue;
				break;
			case 1:
				m_Eng[i]= new CBasicEngine;
				break;
			case 2:
				m_Eng[i]= new CSevenEngine;
				m_Eng[i]->SetEvaluator(new CRowEvaluator);
				break;
			case 3:
				m_Eng[i]= new CArtEngine;
				break;
			case 4:
				m_Eng[i]= new CNankEngine;
				m_Eng[i]->SetEvaluator(new CRegionEvaluator);
				break;
			case 5:
				m_Eng[i]= new CThunderEngine;
				break;
			}
			m_Eng[i]->SetAI(s[i]-m_EngAI[m_EngMap[s[i]]]);
			m_Eng[i]->SetOwner(m_Owner);
		}
	}
	::ReleaseSemaphore(m_hXLock, 1, NULL);
	return true;
}


void CComputerThink::StopSearch()
{
	if( m_InUse==0 || m_InUse==1){
		if(m_Player[m_InUse]){
			m_Eng[m_InUse]->StopSearch();
		}
	}
}

void CComputerThink::SetUseBook(bool u)
{
	m_UseBook = u;
}
void CComputerThink::SetOwner(HWND hwnd)
{
	ASSERT(hwnd);
	m_Owner=hwnd;
}
void CComputerThink::SetOpeningReader(COpeningReader* p){
//	ASSERT(p);
	m_pOR=p;
}
void CComputerThink::SetGame(CGame *pg)
{
	ASSERT(pg);
	m_pG=pg;
}

void CComputerThink::StartToThink()
{
	DWORD dwThreadId;
	DWORD dw=::WaitForSingleObject(m_hAIThread, INFINITE);
	//if()
	ASSERT(dw!=WAIT_FAILED || !m_hAIThread);
	m_hAIThread = CreateThread(NULL, 0, AIThreadFunc, this, 0, &dwThreadId);
//	SetThreadPriority(m_hAIThread, THREAD_PRIORITY_BELOW_NORMAL);
}

DWORD WINAPI CComputerThink::AIThreadFunc(LPVOID lpParam){
	::EnterCriticalSection(&m_CS);
	m_RLockCount++;
	if(m_RLockCount==1){
		::WaitForSingleObject(m_hXLock, 0);
	}
	::LeaveCriticalSection(&m_CS);

	((CComputerThink*)lpParam)->MakeDecision();

	::EnterCriticalSection(&m_CS);
	m_RLockCount--;
	if(m_RLockCount==0){
		::ReleaseSemaphore(m_hXLock, 1, NULL);
	}
	::LeaveCriticalSection(&m_CS);
	return 0;
}

void CComputerThink::SetTimeLimit(int iTime){
	DWORD dwThreadId;
//	DWORD dw=::WaitForSingleObject(m_hTimeThread, INFINITE);

//	ASSERT(dw!=WAIT_FAILED || !m_hTimeThread);
	m_iTimeLimit = iTime;
	if(!iTime) return;
	m_hTimeThread = CreateThread(NULL, 0, TimeLimitThreadFunc, (LPVOID)this, 0, &dwThreadId);
//	SetThreadPriority(m_hAIThread, THREAD_PRIORITY_BELOW_NORMAL);

}
DWORD WINAPI CComputerThink::TimeLimitThreadFunc(LPVOID lpParam){
	::EnterCriticalSection(&m_CS);
	m_RLockCount++;
	if(m_RLockCount==1){
		::WaitForSingleObject(m_hXLock, 0);
	}
	::LeaveCriticalSection(&m_CS);

	int iTime=((CComputerThink*)lpParam)->m_iTimeLimit;
	if(!iTime) return 0;
	while(iTime--)
		Sleep(1000);

	((CComputerThink*)lpParam)->StopSearch();
	PostMessage(((CComputerThink*)lpParam)->m_Owner, WM_GAMEMESSAGER, GM_TIMEOUT, 0);

	::EnterCriticalSection(&m_CS);
	m_RLockCount--;
	if(m_RLockCount==0){
		::ReleaseSemaphore(m_hXLock, 1, NULL);
	}
	::LeaveCriticalSection(&m_CS);

	return 1;
}

void CComputerThink::EndThinking()
{
	char errbuf[128];
	try{
		::CloseHandle(m_hAIThread);
		m_hAIThread = NULL;
		if(m_iTimeLimit) ::CloseHandle(m_hTimeThread);
		m_hTimeThread = NULL;
	}catch(CException cex){
		cex.GetErrorMessage(errbuf, 100);
		TRACE("%s\n",errbuf);
		m_hAIThread = NULL;
		m_hTimeThread = NULL;
	}
	
}

void CComputerThink::PauseGame()
{
	m_DonotEcho = !m_DonotEcho;
}

bool CComputerThink::GetPause()
{
	return m_DonotEcho;
}
