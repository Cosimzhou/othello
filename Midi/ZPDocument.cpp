// ZPDocument.cpp: implementation of the CZPDocument class.
//
//////////////////////////////////////////////////////////////////////

#include "..\\stdafx.h"
//#include "FingerSmooth.h"
#include "ZPDocument.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const char*CZPDocument::DefaultZP="360&#&j o n m l m   m   l m l j     j j o n m l m   m   l   n o       l q p o n o   o   n p n o   p   q         (mkh)       (pmk)       (nli)       (mi)   l   (mkh)       (pmk)     n (nli)       (mi)   l   (mjh)               "
"mm(mh) l m n (olj)   l (lj)         ? mm(mh) l m j (jh) (lh)             ? mm(mh) l m n (olj)   l (lj)       j (kif) j k l (mif)     m (mig) l m n (nli)       ? (omj)ooo(omj) n m l ?(oli) oo(oli) n m l ?k l (mh) l m o (nj)   m (ljg)         ?k (ljg) k l m (mkh)     l (lh)   m (nli)                 "
"j o n m l (mh)   (mh)   (lk) m (lk) (je)     j j (oj) n (mj) l (mh)   (mh)   (li)   n (oj)       l (ql) p (ol) n (ok)   (ok)   (ml) p (nl) (oj)   (pli)   (qlj)       l (mki)       (pmk)       "
"(nli)     j o n m l (mh)   (mh)   (li) m (li) (jf)     j j (oj) n (mj) l (mh)   (mh)   (li)   n (oj)       l (ql) p (ol) n (ok)   (ok)   (nl) p (nl) (oj)   (pli)   (qlj)         (mkh)       (pmk)       (nli)       (mi)   l   (mkh)       (pmk)     n (nli)       (mi)   l   m                "
;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZPDocument::CZPDocument()
{
	DocType = Zp;
	m_pKeyMap = new CZPKeyMap;
	ReadString(DefaultZP);
}

CZPDocument::CZPDocument(const char* pfn)
{
	m_pKeyMap = new CZPKeyMap;
	SetFile(pfn);
}

CZPDocument::~CZPDocument()
{
	delete m_pKeyMap;
}

bool CZPDocument::Play()
{
	if(*m_FileCur ==' ')
	{
		m_FileCur++;
		return true;
	}
	m_pMidi->StopAllNote();
//	m_pView->ClearPressed();
	if(*m_FileCur !='(')
	{
		HitKeyNote(m_pKeyMap->Translate(*m_FileCur++));
	}else{
		m_FileCur++;
		while(*m_FileCur !=')')
			HitKeyNote(m_pKeyMap->Translate(*m_FileCur++));
		if(*m_FileCur ==')') m_FileCur++;
	}
	return m_FileCur< (m_FileContent + m_FileLen);
}

void CZPDocument::SetFile(const char *pfn)
{
	if(this->OpenFile(pfn))
	{
		int tc, start =0;
		m_FileLen = 0;	
		while(!feof(m_pFile)){
			tc = fgetc(m_pFile);
			if(start)
			if(m_pKeyMap->Translate((char)tc) || tc =='(' || tc==')')
				m_FileContent[m_FileLen++] = tc;
			else
				m_FileContent[m_FileLen++] = ' ';
			if(tc == '#') start = 1;
		}
		fclose(m_pFile);
		m_FileCur = m_FileContent;
	}
}

void CZPDocument::GoHead()
{
	m_FileCur =m_FileContent;
}

DWORD CZPDocument::GetPause() const
{	
	return 60;
}

void CZPDocument::ReadString(const char *cp)
{
	int tc, start =0;
	m_FileLen = 0;	
	while(*cp){
		tc = *cp++;
		if(start)
		if(m_pKeyMap->Translate((char)tc) || tc =='(' || tc==')')
			m_FileContent[m_FileLen++] = tc;
		else
			m_FileContent[m_FileLen++] = ' ';
		if(tc == '#') start = 1;
	}
	m_FileCur = m_FileContent;

}
