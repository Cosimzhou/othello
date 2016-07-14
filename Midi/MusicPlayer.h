// MusicPlayer.h: interface for the CMusicPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICPLAYER_H__4E41191C_DF07_4EE0_AB07_9FD854746EEA__INCLUDED_)
#define AFX_MUSICPLAYER_H__4E41191C_DF07_4EE0_AB07_9FD854746EEA__INCLUDED_

#include "ScoreDocument.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMusicPlayer  
{
public:
	void PuasePlay();
	void StopPlay();
	bool PlayDocument(CScoreDocument*);

	CMusicPlayer();
	virtual ~CMusicPlayer();
	
	DWORD m_dwThreadId;
	HANDLE m_hThread;
	typedef struct {
		CScoreDocument* doc;
//		CDialog*		dlg;
		HANDLE	hSemaphore;
		bool Runnalbe;
		bool Puased;
	}dd;
	dd di;
	static DWORD WINAPI PlayProc(LPVOID lpParam);
//	static CScoreDocument *m_pSDoc;
};

#endif // !defined(AFX_MUSICPLAYER_H__4E41191C_DF07_4EE0_AB07_9FD854746EEA__INCLUDED_)
