// MusicPlayer.cpp: implementation of the CMusicPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "..\\stdafx.h"
//#include "FingerSmooth.h"
#include "MusicPlayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//bool CMusicPlayer::Runnalbe;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMusicPlayer::CMusicPlayer()
{
	di.Puased = false;
	di.hSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
}

CMusicPlayer::~CMusicPlayer()
{
	StopPlay();
}

bool CMusicPlayer::PlayDocument(CScoreDocument *pSDoc)
{
//	if(m_pSDoc) return false;
	di.doc = pSDoc;
	StopPlay();
	di.Runnalbe = true;
	if(di.Puased) {
		ReleaseSemaphore(di.hSemaphore, 1, NULL);
		di.Puased = false;
	}

	m_hThread = ::CreateThread (
		NULL,		// Ĭ�ϰ�ȫ����
		NULL,		// Ĭ�϶�ջ��С
		PlayProc,	// �߳���ڵ�ַ��ִ���̵߳ĺ�����
		&di,		// ���������Ĳ���
		0,		// ָ���߳���������
		&m_dwThreadId);	// �����̵߳�ID��

	return true;
}
DWORD WINAPI CMusicPlayer::PlayProc(LPVOID lpParam)
{
	dd &di =*((dd*)lpParam);
#ifndef NO_LOOP
	while(TRUE){
#endif	// NO_LOOP
	di.doc->GoHead();
	while(di.Runnalbe) {
		if(di.Puased){
			di.doc->m_pMidi->StopAllNote();
			WaitForSingleObject(di.hSemaphore, INFINITE);
			di.Puased = false;
		}
		if(di.doc->Play())
		{
			::Sleep(di.doc->GetPause());
		}else break;
	}
	::Sleep(1000);
#ifndef NO_LOOP
		if(!di.Runnalbe)break;
	}
#endif	// NO_LOOP
	di.Runnalbe = false;
	return 0;
}

void CMusicPlayer::StopPlay()
{
	if(di.Runnalbe){
		di.Runnalbe = false;
		WaitForSingleObject(m_hThread, 100);
	}
}

void CMusicPlayer::PuasePlay()
{
	if(di.Puased){
		ReleaseSemaphore(di.hSemaphore, 1, NULL);
	}else
		di.Puased = true;
}
