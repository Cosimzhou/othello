// OpeningReader.h: interface for the CArtOpeningReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENINGREADER_H__8395BC7A_B5FD_4EA4_8429_DC94844CC37A__INCLUDED_)
#define AFX_OPENINGREADER_H__8395BC7A_B5FD_4EA4_8429_DC94844CC37A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct BookNode{
	struct BookNode* brother;
	struct BookNode* child;
	__int8 square;
	__int8 value;
}BookNode;

class COpeningReader  
{
public:
	int SearchShow(short* p, int stepnum, FlipSpot* output) const;
	bool m_bAvalible;
	bool Search(short* p, int stepnum);
	int Bestmove() const;
	int Bestscore() const;
	
	COpeningReader(CString bookname);
	virtual ~COpeningReader();

private:
	int bestmove;
	int bestscore;
	BookNode* m_book;

protected:
	__inline short TurnBack(short f1,short p) const;
	void DestroyNode(BookNode*);
	bool InitialRead(CString bookname);
	__int8 InitBackdate(BookNode* p, bool child);
};

#endif // !defined(AFX_OPENINGREADER_H__8395BC7A_B5FD_4EA4_8429_DC94844CC37A__INCLUDED_)
