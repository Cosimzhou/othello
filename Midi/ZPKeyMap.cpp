// ZPKeyMap.cpp: implementation of the CZPKeyMap class.
//
//////////////////////////////////////////////////////////////////////

#include "..\\stdafx.h"
//#include "FingerSmooth.h"
#include "ZPKeyMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//													34  
const char* CZPKeyMap::szKeyString="A-B+CD[E]F1GH2I3JK4L5M6NO7P8QR9S0T;UV,W.XY/Z";
UCHAR CZPKeyMap::keyMapping[128] = {0, 255, 0, 0};
CZPKeyMap::CZPKeyMap()
{
	if(*reinterpret_cast<DWORD*>(keyMapping) == 0xff00){
		ZeroMemory(keyMapping, 128);
		for(const char *p = szKeyString; *p; ++p)
		{
			keyMapping[*p] = p - szKeyString + 1;
			if(*p>='A' && *p<='Z')
				keyMapping[*p + 32] = keyMapping[*p];
		}
	}
}

CZPKeyMap::~CZPKeyMap()
{

}
UCHAR CZPKeyMap::Translate(char p) const{
//	ASSERT(keyMapping[p]);
	return keyMapping[p];
}
