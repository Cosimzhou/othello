// ScoreDocument.cpp: implementation of the CScoreDocument class.
//
//////////////////////////////////////////////////////////////////////

#include "..\\stdafx.h"
//#include "FingerSmooth.h"
#include "ScoreDocument.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScoreDocument::CScoreDocument()
{
	m_pFile = NULL;
	m_TuneOffset = 60;
	m_TuneStart = 24;
	DocType = Base;
}

CScoreDocument::~CScoreDocument()
{

}

BOOL CScoreDocument::OpenFile(const char *pfn)
{
	if(m_pFile = fopen(pfn, "rb+"))
		return TRUE;

	return FALSE;
}

void CScoreDocument::CloseFile()
{
	if(m_pFile)
		fclose(m_pFile);
}

bool CScoreDocument::Play()
{
	return true;	
}

void CScoreDocument::HitKeyNote(UCHAR note, UCHAR channel, UCHAR volume)
{
	if(!note) return;
	note--;
	m_pMidi->NoteOn(channel, note + m_TuneOffset, volume);
//	m_pView->AddPressed(note + m_TuneOffset - m_TuneStart);
}

/*void CScoreDocument::SetView(CPianoView * ppv)
{
	m_pView = ppv;
}*/

void CScoreDocument::GoHead()
{
	
}
void CScoreDocument::SetFile(const char*sfn)
{

}

void CScoreDocument::ReleaseKeyNote(UCHAR note, UCHAR channel)
{
	if(!note) return;
	note--;
	m_pMidi->NoteOff(channel, note + m_TuneOffset);
//	m_pView->RemovePressed(note + m_TuneOffset - m_TuneStart);
}

DWORD CScoreDocument::GetPause() const
{
	return 100;
}

UINT CScoreDocument::DocumentType()
{	
	return DocType;
}
