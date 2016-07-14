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
为了评价某个局面pos，需对其进行深度为d的搜索，在搜索之前可以先对pos进行一次深度为d'的浅层搜索(shallow search)(d'<d)，
搜索结果v'可以用来对pos的真正结果v来进行估计，以确定其真值v是否不在当前的搜索窗口(α,β) 之间，如果这样的话,就不需要
对pos进行深度为d的搜索，直接返回shallow search的右边界即可。否则，需对pos进行深度为d的搜索以获取其真值v。

用v'来估计v的一个自然想法是采用线性模型：v=av'+b+ε其中 a,b∈IR, ε～N(0,σ^2) 误差变量ε 服从0,σ^2 的正态分布。
(1)如果搜索引擎的估值函数稳定的话，可以认为a=1, b=0 并且σ^2 很小。 v^=av'+b 可以看作是v的有效无偏估计。
所以有下面的等式：
		v≥β <==> v^+ε≥β <==> v^-β≥-ε <==> (v^-β)/σ≥-ε/σ                  
其中-ε/σ服从0, 1 的正态分布，其分布函数为Φ。
所以，指定概率p的情况下，v≥β等价于 (v^-β)/σ>Φ^-1(p)。
又v^=av'+b ：
		(v^-β)/σ>Φ^-1(p) <==> (av'+b-β)/σ>Φ^-1(p) <==> v'>(Φ^-1(p)σ+β-b)/a
得： v≥β在指定概率p 的条件下是否成立等价于 v'>(Φ^-1(p)σ+β-b)/a 是否成立。
类似的方法可推得：
 v≤β在指定概率p 的条件下是否成立等价于v'≤(Φ^-1(p)σ+α-b)/a 是否成立。
其中a,b,p,σ都是常量，α,β是已知量。

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