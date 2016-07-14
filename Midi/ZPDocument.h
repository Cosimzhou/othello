// ZPDocument.h: interface for the CZPDocument class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZPDOCUMENT_H__AEF143C9_0668_46C2_89AE_49480CA655D4__INCLUDED_)
#define AFX_ZPDOCUMENT_H__AEF143C9_0668_46C2_89AE_49480CA655D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ZPKeyMap.h"
#include "ScoreDocument.h"

class CZPDocument  : public CScoreDocument
{
public:
	void ReadString(const char*);
	DWORD GetPause() const;
	void SetFile(const char*);
	bool Play();
	void GoHead();
	CZPDocument();
	CZPDocument(const char*);
	virtual ~CZPDocument();

protected:
	CZPKeyMap* m_pKeyMap;
	char m_FileContent[4096];
	char* m_FileCur;
	UINT m_FileLen;

	static const char *DefaultZP;
};

#endif // !defined(AFX_ZPDOCUMENT_H__AEF143C9_0668_46C2_89AE_49480CA655D4__INCLUDED_)
