// ImprovedEngine.cpp: implementation of the CImprovedEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "ImprovedEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PERCENTITLE   1.5  // i.e. 93%, refer to normally-distribution table 
#define D             8    //search height
#define DP            4    //shallow search height

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImprovedEngine::CImprovedEngine()
{

}

CImprovedEngine::~CImprovedEngine()
{

}
/*
Ϊ������ĳ������pos�������������Ϊd��������������֮ǰ�����ȶ�pos����һ�����Ϊd'��ǳ������(shallow search)(d'<d)��
�������v'����������pos���������v�����й��ƣ���ȷ������ֵv�Ƿ��ڵ�ǰ����������(��,��) ֮�䣬��������Ļ�,�Ͳ���Ҫ
��pos�������Ϊd��������ֱ�ӷ���shallow search���ұ߽缴�ɡ��������pos�������Ϊd�������Ի�ȡ����ֵv��

��v'������v��һ����Ȼ�뷨�ǲ�������ģ�ͣ�v=av'+b+������ a,b��IR, �š�N(0,��^2) �������� ����0,��^2 ����̬�ֲ���
(1)�����������Ĺ�ֵ�����ȶ��Ļ���������Ϊa=1, b=0 ���Ҧ�^2 ��С�� v^=av'+b ���Կ�����v����Ч��ƫ���ơ�
����������ĵ�ʽ��
		v�ݦ� <==> v^+�šݦ� <==> v^-�¡�-�� <==> (v^-��)/�ҡ�-��/��                  
����-��/�ҷ���0, 1 ����̬�ֲ�����ֲ�����Ϊ����
���ԣ�ָ������p������£�v�ݦµȼ��� (v^-��)/��>��^-1(p)��
��v^=av'+b ��
		(v^-��)/��>��^-1(p) <==> (av'+b-��)/��>��^-1(p) <==> v'>(��^-1(p)��+��-b)/a
�ã� v�ݦ���ָ������p ���������Ƿ�����ȼ��� v'>(��^-1(p)��+��-b)/a �Ƿ������
���Ƶķ������Ƶã�
 v�ܦ���ָ������p ���������Ƿ�����ȼ���v'��(��^-1(p)��+��-b)/a �Ƿ������
����a,b,p,�Ҷ��ǳ�������,������֪����

* /

int Alpha_Beta(int height, int alpha, int beta)
{
	int i, max, val;
 	POSDELTA delta;
	if (height==0 || IsGameOver())//Leaf(&pos, height)
		return Eval(&pos);

	//location for selective extension
	//  ...
	//	...

	if (height == D){
		//check for if v >= beta
		int bound = int((+PERCENTITLE * sigma + beta -b)/a+0.5);
		if (Alpha_Beta(DP, bound-1, bound) >= bound)
			return beta;

		//check for if v <= alpha
		bound = int((-PERCENTITLE * sigma + alpha -b)/a+0.5);
		if (Alpha_Beta(DP, bound-1, bound) <= bound)
			return alpha;
	}
//  ...
	max = alpha;
	for (i = 0; i < pos.moveNum; i++){
		Move(&pos, pos.moves[i], &delta);
		val = -AlphaBeta(height-1, -beta, -max);
		UndoMove(&pos, &delta);
		if (val > max){
			if (val >= beta)
				return val;
			max = val;
		}
	}
	return max;
}
/**/