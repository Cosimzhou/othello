// ScoreDocument.h: interface for the CScoreDocument class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCOREDOCUMENT_H__CA119FCD_D70E_48E2_A305_A0D985AFCF27__INCLUDED_)
#define AFX_SCOREDOCUMENT_H__CA119FCD_D70E_48E2_A305_A0D985AFCF27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ZPKeyMap.h"
#include "MidiOutput.h"	// Added by ClassView
//#include "PianoView.h"

class CScoreDocument  
{
public:
	UINT DocumentType();
	void ReleaseKeyNote(UCHAR, UCHAR=0);
//	void SetView(CPianoView*);
	void HitKeyNote(UCHAR,UCHAR=0,UCHAR=90);
//	CPianoView* m_pView;
	virtual void GoHead();
	virtual bool Play();
	virtual void SetFile(const char*);
	virtual DWORD GetPause()const;
	CMidiOutput* m_pMidi;
	CScoreDocument();
	virtual ~CScoreDocument();

protected:
	enum {Base=0, Zp, Buffer} DocType;
	UCHAR m_TuneStart;
	UCHAR m_TuneOffset;
	void CloseFile();
	BOOL OpenFile(const char*);
	CZPKeyMap* m_pKeyMap;
//private:
	FILE* m_pFile;
};

#endif // !defined(AFX_SCOREDOCUMENT_H__CA119FCD_D70E_48E2_A305_A0D985AFCF27__INCLUDED_)
