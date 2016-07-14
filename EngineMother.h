// EngineMother.h: interface for the CEngineMother class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENGINEMOTHER_H__BEFA80EE_F717_42C9_94DD_1B07121ADD9E__INCLUDED_)
#define AFX_ENGINEMOTHER_H__BEFA80EE_F717_42C9_94DD_1B07121ADD9E__INCLUDED_

#include "Othello.h"
//#include "GameScript.h"
#include "EvaluatorMother.h"
#include <windows.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//using namespace GameScript;

class CEngineMother  
{
public:
	CEngineMother(){
		m_BestMove=-1;
		m_BestScore=-64;
		m_Nodes=0;
		m_Time=0.0;
		m_bSearchContinue=true;
		m_pEM = NULL;

	};
	virtual ~CEngineMother(){
		if(m_pEM)
			delete m_pEM;
	};
public:
	void SetOwner(HWND hwnd){
		m_Owner=hwnd;
	}
	void ReportTrace(int pos, int depth) const{
		if(depth<4 || depth== 255)
			PostMessage(m_Owner, WM_GAMEMESSAGER, GM_REPORTTRACE, (depth<<8)|pos);
	}
	void SetEvaluator(CEvaluatorMother* pEM){
		ASSERT(pEM);
		m_pEM = pEM;
	}
	virtual void Search(ChessType* curboard, ChessType col)=0;
	virtual double BestScore() const{	return m_BestScore;}
	virtual void StopSearch(){ m_bSearchContinue=false;}
	virtual int BestMove() const{	return m_BestMove;}
	virtual int Nodes() const{	return m_Nodes;}
	virtual double Time() const{	return m_Time;}
	virtual void SetAI(int ai)=0;
protected:
	void SetBest(int n){
		ASSERT(n==0 || n>=10 && n<=80);
		m_BestMove=n;
		ReportTrace(n, 255);
	};
	bool m_bSearchContinue;
	int m_BestMove;
	double m_BestScore;
	long m_Nodes;
	double m_Time;
	CEvaluatorMother* m_pEM;

	double NowTime(){return GetTickCount();};
private:
	HWND m_Owner;
};

#endif // !defined(AFX_ENGINEMOTHER_H__BEFA80EE_F717_42C9_94DD_1B07121ADD9E__INCLUDED_)
