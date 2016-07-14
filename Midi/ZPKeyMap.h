// ZPKeyMap.h: interface for the CZPKeyMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZPKEYMAP_H__D78A55C0_227B_4112_BE58_E1A201AF2BC1__INCLUDED_)
#define AFX_ZPKEYMAP_H__D78A55C0_227B_4112_BE58_E1A201AF2BC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "KeyboardMap.h"

class CZPKeyMap // : public CKeyboardMap
{
public:
	CZPKeyMap();
	virtual ~CZPKeyMap();

	unsigned char Translate(char) const;
	static unsigned char keyMapping[128];
	static const char* szKeyString;
};

#endif // !defined(AFX_ZPKEYMAP_H__D78A55C0_227B_4112_BE58_E1A201AF2BC1__INCLUDED_)
