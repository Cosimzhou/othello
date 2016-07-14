// OpeningReader.cpp: implementation of the COpeningReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "GameScript.h"
#include "OpeningReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/*
const int COpeningReader::worst2best[] ={ 
			20, 0x19, 0x41, 70, 11, 0x10, 0x13, 0x1a, 0x40, 0x47, 0x4a, 0x4f, 0x15, 0x18, 0x1d, 0x22, 
			0x38, 0x3d, 0x42, 0x45, 0x16, 0x17, 0x26, 0x2b, 0x2f, 0x34, 0x43, 0x44, 0x1f, 0x20, 0x27, 0x2a, 
			0x30, 0x33, 0x3a, 0x3b, 13, 14, 0x25, 0x2c, 0x2e, 0x35, 0x4c, 0x4d, 30, 0x21, 0x39, 60, 
			12, 15, 0x1c, 0x23, 0x37, 0x3e, 0x4b, 0x4e, 10, 0x11, 0x49, 80, 40, 0x29, 0x31, 50
		 };*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpeningReader::COpeningReader(CString bookname)
{
	m_book = NULL;
	m_bAvalible=false;
//#ifndef _DEBUG
	m_bAvalible=InitialRead(bookname);
//#endif
	TRACE("BookNode sizeof: %d\n",sizeof(BookNode));
}

COpeningReader::~COpeningReader()
{
	DestroyNode(m_book);
}
void COpeningReader::DestroyNode(BookNode *p)
{
#ifndef _DEBUG
	if(p){
		DestroyNode(p->child);
		DestroyNode(p->brother);
		delete p;
	}
#endif
}

bool COpeningReader::InitialRead(CString bookname){
	__int8 buf[41];
	int layer=0;
	BookNode* LocTrace[40];
	BookNode* pBookNode;

	CFile file;
	CFileException fe;
	if(!file.Open(bookname, CFile::modeRead | CFile::shareDenyWrite, &fe))
		return false;

	m_book = new BookNode;
	m_book->square	= 0x1f;
	m_book->value	= 0;
	m_book->brother	= NULL;
	m_book->child	= NULL;

	while(file.Read((LPSTR)buf, 41) == 41){
		pBookNode = m_book;
		/*构建新记录*/
		for(layer=0; layer<40; layer++){
			if(!pBookNode){
				pBookNode = new BookNode;
				LocTrace[layer-1]->child = pBookNode;
				pBookNode->square	= buf[layer];
				pBookNode->value	= -128; 
				pBookNode->child	= NULL;
				pBookNode->brother	= NULL;
			}else{
				while(buf[layer]!=pBookNode->square && pBookNode->brother)
					pBookNode = pBookNode->brother;
				if(buf[layer] != pBookNode->square){
					pBookNode->brother	= new BookNode;
					pBookNode			= pBookNode->brother;
					pBookNode->square	= buf[layer];
					pBookNode->value	= -128; 
					pBookNode->child	= NULL;
					pBookNode->brother	= NULL;
				}
			}
			LocTrace[layer] = pBookNode;
			pBookNode = pBookNode->child;
		}
		LocTrace[39]->value = -buf[40];
	}
	//为新记录赋回溯值
	InitBackdate(m_book, true);
	return true;
}
__int8 COpeningReader::InitBackdate(BookNode* p, bool child){
	__int8 tmpval;
	ASSERT(p);

	if(p->child){
		tmpval = InitBackdate(p->child, true);
		p->value = tmpval;
	}
	if(p->brother){
		tmpval = InitBackdate(p->brother, false);
		if(tmpval<p->value) tmpval=p->value;
	}else
		tmpval=p->value;

	if(child)
		return -tmpval;
	else
		return tmpval;
}

bool COpeningReader::Search(short* p, int stepnum){
	short my[40], f1;
	short *pmy=my;
	int i=stepnum;
	ASSERT(stepnum>=0);
	if(stepnum>=40) return false;
	if(stepnum==0){
		f1=rand()%4;
		if(f1==1)bestmove=0x27;
		else if(f1==2)bestmove=51;
		else if(f1==3)bestmove=59;
		else bestmove=0x1f;
		bestscore=0;
		return true;
	}
	bestscore=-128;
	bestmove=0;

	f1=*p;
	if(f1==0x1f){
		memcpy(my, p, stepnum*sizeof(short));
	}else{
		*pmy++=0x1f;
		while(i--)
			*pmy++=TurnBack(f1, *(++p));
	}

	pmy=my;
	i=0;
	BookNode* pBookNode=m_book;
	for(i=0; i<stepnum && pBookNode; i++){
		if(!pBookNode)
			return false;
		while(pBookNode->square!= *pmy && pBookNode->brother)
			pBookNode=pBookNode->brother;
		if(pBookNode->square== *pmy){
			pBookNode=pBookNode->child;
			pmy++;
			continue;
		}
		return false;
	}

	while(pBookNode){
		if(pBookNode->value>bestscore){// || bestscore==-128
			bestscore=pBookNode->value;
			bestmove=pBookNode->square;
		}else if(pBookNode->value==bestscore){
			if(rand() & 1)
				bestmove=pBookNode->square;
		}
		pBookNode=pBookNode->brother;
	}
	bestmove = TurnBack(f1, bestmove);
	return true;
}

int COpeningReader::Bestmove() const{
	return bestmove;
}

int COpeningReader::Bestscore() const{
	return bestscore;
}



short COpeningReader::TurnBack(short f1,short p) const
{
	if(f1==0x27)
		return Conv(GetY_ch(p),GetX_ch(p));

	if(f1==51)//0x33
		return Conv((9-GetY_ch(p)),(9-GetX_ch(p)));

	if(f1==59)//0x3b
		return Conv((9-GetX_ch(p)),(9-GetY_ch(p)));

	return p;
}

int COpeningReader::SearchShow(short *p, int stepnum, FlipSpot *output) const
{
	short my[40], f1;
	short *pmy=my;
	int i=stepnum;
	ASSERT(stepnum>=0 && output);
	if(stepnum>=40) return false;
	if(stepnum==0){
		output[0].square=0x1f;
		output[0].flips =0;
		output[1].square=0x27;
		output[1].flips =0;
		output[2].square=51;
		output[2].flips =0;
		output[3].square=59;
		output[3].flips =0;
		return 4;
	}

	f1=*p;
	if(f1==0x1f){
		memcpy(my, p, stepnum*sizeof(short));
	}else{
		*pmy++=0x1f;
		while(i--)
			*pmy++=TurnBack(f1, *(++p));
	}

	pmy=my;
	i=0;
	BookNode* pBookNode=m_book;
	for(i=0; i<stepnum && pBookNode; i++){
		if(!pBookNode)
			return 0;
		while(pBookNode->square!= *pmy && pBookNode->brother)
			pBookNode=pBookNode->brother;
		if(pBookNode->square== *pmy){
			pBookNode=pBookNode->child;
			pmy++;
			continue;
		}
		return 0;
	}

	i=0;
	while(pBookNode){
		output[i].square=TurnBack(f1, pBookNode->square);
		output[i].flips =pBookNode->value;
		i++;
		pBookNode=pBookNode->brother;
	}
	return i;
}
