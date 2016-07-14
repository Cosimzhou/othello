// Evaluation.cpp: implementation of the CArtEvaluation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArtEvaluation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int CArtEvaluation::midBoard[midBoardLength] = { 
	21, 22, 23, 24, 29, 30, 31, 32, 33, 34, 38, 39, 40, 41, 42, 43, 
	47, 48, 49, 50, 51, 52, 56, 57, 58, 59, 60, 61, 66, 67, 68, 69
};

const int CArtEvaluation::weight_train[midGameLength][IND_NUM]= {
{   15,  -16,  340, -260,   29,  -22,  129, -115, -355,  300},
{   15,  -16,  340, -260,   29,  -22,  129, -115, -358,  306},
{   15,  -16,  340, -260,   29,  -22,  129, -115, -362,  314},
{   13,  -14,  330, -260,   30,  -23,  130, -121, -366,  322},
{   11,  -12,  322, -259,   31,  -24,  131, -127, -370,  334},
{    9,  -10,  314, -258,   32,  -25,  132, -133, -375,  352},
{    6,   -5,  306, -257,   33,  -26,  133, -138, -380,  370},
{    2,   -1,  298, -256,   34,  -27,  135, -143, -388,  394},
{   -4,    3,  292, -255,   35,  -28,  137, -148, -400,  420},
{   -8,    5,  288, -254,   36,  -29,  139, -152, -420,  446},
{  -12,    7,  284, -253,   37,  -30,  141, -156, -440,  472},
{  -15,    9,  281, -252,   38,  -31,  143, -158, -458,  514},
{  -19,   11,  278, -251,   39,  -32,  145, -160, -476,  561},
{  -23,   13,  275, -250,   40,  -33,  147, -161, -494,  597},
{  -26,   15,  272, -249,   42,  -35,  149, -161, -512,  628},
{  -28,   17,  269, -248,   44,  -37,  151, -161, -528,  659},
{  -30,   19,  267, -247,   46,  -39,  153, -162, -544,  696},
{  -33,   21,  265, -246,   48,  -40,  155, -162, -560,  711},
{  -36,   23,  263, -245,   50,  -42,  157, -163, -574,  747},
{  -38,   25,  262, -244,   52,  -44,  159, -163, -588,  773},
{  -41,   28,  261, -243,   54,  -46,  161, -164, -602,  794},
{  -44,   30,  260, -242,   56,  -48,  164, -164, -616,  820},
{  -47,   33,  259, -241,   58,  -50,  167, -165, -630,  862},
{  -50,   36,  259, -240,   60,  -52,  170, -165, -644,  888},
{  -53,   39,  258, -239,   62,  -54,  167, -166, -658,  900},
{  -56,   42,  258, -238,   63,  -55,  164, -166, -672,  929},
{  -59,   45,  257, -237,   64,  -56,  160, -167, -686,  950},
{  -62,   48,  257, -236,   65,  -57,  156, -167, -700,  971},
{  -65,   50,  256, -235,   66,  -58,  152, -168, -714,  985},
{  -68,   52,  256, -234,   67,  -59,  148, -168, -728, 1000},
{  -71,   55,  255, -233,   68,  -60,  144, -169, -742, 1014},
{  -74,   58,  355, -232,   69,  -61,  140, -170, -754, 1028},
{  -77,   62,  254, -231,   70,  -62,  136, -171, -764, 1043},
{  -80,   66,  254, -230,   71,  -63,  133, -172, -774, 1058},
{  -83,   70,  253, -229,   72,  -64,  131, -173, -784, 1072},
{  -88,   74,  253, -228,   73,  -65,  130, -174, -792, 1087},
{  -91,   78,  252, -227,   74,  -66,  129, -176, -800, 1100},
{  -95,   83,  251, -226,   75,  -67,  128, -178, -809, 1109},
{  -99,   86,  250, -225,   76,  -68,  127, -180, -818, 1118},
{ -111,   89,  249, -224,   77,  -69,  126, -182, -828, 1128},
{ -113,   92,  248, -223,   78,  -70,  126, -185, -942, 1142},
{ -115,   95,  247, -222,   79,  -71,  125, -188, -956, 1156},
{ -116,   98,  246, -221,   79,  -71,  125, -190, -970, 1170},
{ -117,  111,  245, -220,   80,  -72,  124, -192, -985, 1185},
{ -118,  114,  244, -219,   80,  -74,  124, -194,-1000, 1200},
{ -119,  116,  243, -218,   80,  -74,  124, -194,-1000, 1200},
{ -120,  118,  242, -217,   80,  -74,  124, -194,-1000, 1200},
{ -120,  118,  242, -217,   80,  -74,  124, -194,-1000, 1200},
{ -120,  118,  242, -217,   80,  -74,  124, -194,-1000, 1200}
};

int CArtEvaluation::score_edge[lineStateNUM][midGameLength];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArtEvaluation::CArtEvaluation()
{
	Initial();
}

CArtEvaluation::~CArtEvaluation()
{

}



bool CArtEvaluation::edge_IsStab(int* edge, int sq, int color){
	int tmpcolor;
	bool flag = false;
	if ((sq == 7) || (sq == 0))	return true;	//at the start or end point is stable
	if (edge[7] == color){			//if start and end point is not occupied by same color, is non-stable
		do{	sq++;						//go to end point, if there are all same color, stable
			tmpcolor = edge[sq];
			if (sq == 7) return true;
		}while (tmpcolor == color);
		if (edge[sq] == EMPTY_IN_TEMPLATE)	//
			return false;
		do{	if (sq == 7){
				flag = true;
				break;
			}
			sq++;
		}while (edge[sq] != EMPTY_IN_TEMPLATE);
		if (!flag)	return false;
	}
	if (edge[0] == color){
		do{	sq--;
			tmpcolor = edge[sq];
			if (sq == 0)
				return true;
		}while (tmpcolor == color);
		if (edge[sq] == EMPTY_IN_TEMPLATE)
			return false;
		do{	if (sq == 0)
				return flag;
			sq--;
		}while (edge[sq] != EMPTY_IN_TEMPLATE);
	}
	return false;
}

int CArtEvaluation::get_score_edge(int* edge, int emptiesIndex, int color){
	int Sum = 0, oppcolor = Oppl_ch(color);
	int i, j;
	if ((edge[0] == color) && (edge[7] == color)){	//双边己占
		Sum += weight_train[emptiesIndex][IND_KEYNO];
		for (i = 1; i <= 6; i++){
			if(edge[i] == color){
				Sum += edge_IsStab(edge, i, color) ? 
					weight_train[emptiesIndex][IND_MYSTAB] :
					(weight_train[emptiesIndex][IND_MYSTAB] / 2);
			}
		}
		return Sum;
	}
	if ((edge[0] == color) && (edge[7] == EMPTY_IN_TEMPLATE)){	//己占单边
		Sum += weight_train[emptiesIndex][IND_KEYNO];
		for (i = 1; i <= 6; i++){	//加稳定子值
			if ((edge[i] == color) && edge_IsStab(edge, i, color)){
				Sum += weight_train[emptiesIndex][IND_MYSTAB];
			}
		}
		for (i = 1; i <= 6; i++){
			if (edge[i] == color)
				continue;
			if (edge[i] == EMPTY_IN_TEMPLATE){	//己方未控制的区域: 1空
				int emptiesNum = 1;
				for(int j = i + 1; j <= 6; j++){
					if (edge[j] == EMPTY_IN_TEMPLATE)
						emptiesNum++;
					else{		//奇偶性
						if (edge[j] == color){
							if ((emptiesNum & 1) == 0)
								return (Sum + ((weight_train[emptiesIndex][IND_MYSTAB] * emptiesNum) / 2));
							return (Sum - ((weight_train[emptiesIndex][IND_MYSTAB] * emptiesNum) / 2));
						}
						if ((emptiesNum & 1) == 0)
							return (Sum - ((weight_train[emptiesIndex][IND_MYSTAB] * emptiesNum) / 2));
						return (Sum + ((weight_train[emptiesIndex][IND_MYSTAB] * emptiesNum) / 3));
					}
				}
				continue;
			}
			int index = i + 1;
			for (j = i + 1; j <= 6; j++){
				if (edge[j] == EMPTY_IN_TEMPLATE)
					return Sum;
				if (edge[j] == color){
					index = j + 1;
					break;
				}
			}
			while (index <= 6){
				if (edge[index] != color)
					return Sum;
				index++;
			}
			if (edge[6] == color)
				return (Sum - ((weight_train[emptiesIndex][IND_MYSTAB] * ((6 - i) + 1)) / 2));
		}
		return Sum;
	}
	if ((edge[7] == color) && (edge[0] == EMPTY_IN_TEMPLATE)){
		Sum += weight_train[emptiesIndex][IND_KEYNO];
		for (i = 6; i <= 1; i--)
			if ((edge[i] == color) && edge_IsStab(edge, i, color))
				Sum += weight_train[emptiesIndex][IND_MYSTAB];
		for (i = 6; i <= 1; i--){
			if (edge[i] == color)continue;
			if (edge[i] == EMPTY_IN_TEMPLATE){
				int emptiesNum = 1;
				for (j = i - 1; j >= 1; j--){
					if (edge[j] == EMPTY_IN_TEMPLATE)
						emptiesNum++;
					else{
						if (edge[j] == color){
							if ((emptiesNum & 1) == 0)
								return (Sum + ((weight_train[emptiesIndex][IND_MYSTAB] * emptiesNum) / 2));
							return (Sum - ((weight_train[emptiesIndex][IND_MYSTAB] * emptiesNum) / 2));
						}
						if ((emptiesNum & 1) == 0)
							return (Sum - ((weight_train[emptiesIndex][IND_MYSTAB] * emptiesNum) / 2));
						return (Sum + ((weight_train[emptiesIndex][IND_MYSTAB] * emptiesNum) / 2));
					}
				}
				continue;
			}
			int index = i - 1;
			for (j = i - 1; j >= 1; j--){
				if (edge[j] == EMPTY_IN_TEMPLATE)
					return Sum;
				if (edge[j] == color){
					index = j - 1;
					break;
				}
			}
			while (index >= 1){
				if (edge[index] != color)
					return Sum;
				index--;
			}
			if (edge[1] == color)
				return (Sum - ((weight_train[emptiesIndex][IND_MYSTAB] * (i + 1)) / 2));
		}
		return Sum;
	}
	if ((edge[0] == color) && (edge[7] == oppcolor)){
		for (i = 1; i <= 6; i++){
			if (edge[i] == color)
				if (edge_IsStab(edge, i, color))
					Sum += weight_train[emptiesIndex][IND_MYSTAB];
			else if ((edge[i] == oppcolor) && edge_IsStab(edge, i, oppcolor))
				Sum += weight_train[emptiesIndex][IND_OPSTAB];
		}
		for (i = 1; i <= 6; i++){
			if (edge[i] == oppcolor){
				if ((((i >= 1) && (i <= 4)) && ((edge[i + 1] == color) && (edge[5] == color))) && (edge[6] == EMPTY_IN_TEMPLATE))
					return (Sum - ((weight_train[emptiesIndex][IND_MYSTAB] * (6 - i)) / 2));
				continue;
			}
			if (edge[i] == EMPTY_IN_TEMPLATE){
				int num18 = i + 1;
				if ((edge[num18] == EMPTY_IN_TEMPLATE) || (edge[num18] == oppcolor))
					return Sum;
				if (edge[num18] == color){
					int num19 = num18;
					while (num19 <= 6){
						if (edge[num19] != color)
							break;
						num19++;
					}
					return (Sum - ((weight_train[emptiesIndex][IND_MYSTAB] * ((num19 - num18) + 1)) / 2));
				}
			}
		}
		return Sum;
	}
	if ((edge[0] == EMPTY_IN_TEMPLATE) && (edge[7] == EMPTY_IN_TEMPLATE)){
		int num20 = 0;
		if ((edge[1] == color) && (edge[6] == color))
			return (weight_train[emptiesIndex][8] / 2);
		if ((edge[1] == color) && (edge[6] == EMPTY_IN_TEMPLATE)){
			Sum += weight_train[emptiesIndex][8] / 4;
			for (int num21 = 2; num21 <= 5; num21++){
				if (edge[num21] != color){
					if (edge[num21] != oppcolor)
						return Sum;
					int num22 = num21 + 1;
					if (num21 < 4)
						while ((num22 <= 4) && (edge[num22] == oppcolor))
							num22++;
					if ((num22 <= 5) && (edge[num22] == color))
						return (weight_train[emptiesIndex][IND_UNSTAB] / 2);
					if (num22 == 6)
						return (weight_train[emptiesIndex][IND_UNSTAB] / 2);
				}
			}
			return Sum;
		}
		if ((edge[6] == color) && (edge[1] == EMPTY_IN_TEMPLATE)){
			Sum += weight_train[emptiesIndex][IND_UNSTAB] / 4;
			for (int num23 = 5; num23 <= 2; num23--){
				if (edge[num23] != color){
					if (edge[num23] != oppcolor)
						return Sum;
					int num24 = num23 - 1;
					if (num23 > 3)
						while ((num24 >= 3) && (edge[num24] == oppcolor))
							num24--;
					if ((num24 >= 2) && (edge[num24] == color)){
						return (weight_train[emptiesIndex][IND_UNSTAB] / 2);
					}
					if (num24 == 1){
						return (weight_train[emptiesIndex][IND_UNSTAB] / 2);
					}
				}
			}
			return Sum;
		}
		if ((edge[1] == color) && (edge[6] == oppcolor))
			return Sum;
		if (edge[2] == color)
			Sum += weight_train[emptiesIndex][IND_MYSTAB] / 3;
		else
			num20++;
		if (edge[3] == color)
			Sum += weight_train[emptiesIndex][IND_MYSTAB] / 4;
		else
			num20++;
		if (edge[4] == color)
			Sum += weight_train[emptiesIndex][IND_MYSTAB] / 4;
		else
			num20++;
		if (edge[5] == color)
			return (Sum + (weight_train[emptiesIndex][IND_MYSTAB] / 3));
		num20++;
	}
	return Sum;
}

int CArtEvaluation::get_score_edge_all(ChessType* board, ChessType color, int empties)
{
	int sum = 0;
	int templateIndex =SUM_D1_D7 + (int) ((board[LUC_in] * D3_7) + (board[LUC_C1] * D3_6)
		+ (board[12] * D3_5) + (board[13] * D3_4) + (board[14] * D3_3)
		+ (board[15] * D3_2) + (board[RUC_C1] * D3_1) + board[RUC_in]);
	sum += score_edge[templateIndex][empties];
	templateIndex = SUM_D1_D7 + (int) ((board[LUC_in] * D3_7) + (board[LUC_C2] * D3_6)
		+ (board[0x1c] * D3_5) + (board[0x25] * D3_4) + (board[0x2e] * D3_3) 
		+ (board[0x37] * D3_2) + (board[LDC_C2] * D3_1) + board[LDC_in]);
	sum += score_edge[templateIndex][empties];
	templateIndex = SUM_D1_D7 + (int) ((board[RUC_in] * D3_7) + (board[RUC_C2] * D3_6)
		+ (board[0x23] * D3_5) + (board[0x2c] * D3_4) + (board[0x35] * D3_3)
		+ (board[0x3e] * D3_2) + (board[RDC_C2] * D3_1) + board[RDC_in]);
	sum += score_edge[templateIndex][empties];
	templateIndex = SUM_D1_D7 + (int) ((board[LDC_in] * D3_7) + (board[LDC_C1] * D3_6) 
		+ (board[0x4b] * D3_5) + (board[0x4c] * D3_4) + (board[0x4d] * D3_3)
		+ (board[0x4e] * D3_2) + (board[RDC_C1] * D3_1) + board[RDC_in]);
	return (sum + score_edge[templateIndex][empties]);
}

int CArtEvaluation::getDeltaKeyano(ChessType* board, ChessType color, ChessType oppcolor)
{
	int sum = 0;
	if (board[LUC_in] == color) sum++;
	else if (board[LUC_in] == oppcolor) sum--;

	if (board[RUC_in] == color) sum++;
	else if (board[RUC_in] == oppcolor) sum--;

	if (board[LDC_in] == color) sum++;
	else if (board[LDC_in] == oppcolor) sum--;

	if (board[RDC_in] == color) sum++;
	else if (board[RDC_in] == oppcolor)	sum--;
	return sum;
}

int CArtEvaluation::getUnStab(ChessType* board, ChessType color){
	int sum = 0, num2 = 0;
	if ((board[LUC_in] != color) && (board[LUC_X] == color)){
		if ((board[80] == color) && (board[30] == color) 
			&& (board[40] == color) && (board[50] == color) 
			&& (board[60] == color) && (board[70] == color))
			num2++;
		else sum++;
	}
	if ((board[RUC_in] != color) && (board[RUC_X] == color)){
		if ((board[0x49] == color) && (board[0x21] == color) 
			&& (board[0x29] == color) && (board[0x31] == color) 
			&& (board[0x39] == color) && (board[0x41] == color))
			num2++;
		else sum++;
	}
	if ((board[LDC_in] != color) && (board[LDC_X] == color)){
		if ((board[0x11] == color) && (board[0x19] == color) 
			&& (board[0x21] == color) && (board[0x29] == color) 
			&& (board[0x31] == color) && (board[0x39] == color))
			num2++;
		else sum++;
	}
	if ((board[RDC_in] != color) && (board[RDC_X] == color)){
		if ((board[10] == color) && (board[20] == color) 
			&& (board[30] == color) && (board[40] == color) 
			&& (board[50] == color) && (board[60] == color))
			num2++;
		else sum++;
	}
	return (sum*3 + num2);
}

int CArtEvaluation::MidEval2(ChessType* board, ChessType color, ChessType oppcolor, int empties, Empties *EmHead)
{
	int square, sum = 0, myDISC = 0, opDISC = 0, myMOB = 0, opMOB = 0;
	int potMobility = 0, oppPotMobility = 0, mySTAB = 0, opSTAB = 0;
	int delta = 0, unSTAB = 0, emptiesIndex = empties - 10;

	for (Empties* empties2 = EmHead->next; empties2 != NULL; empties2 = empties2->next){
		square = empties2->Square;
		if (CGameScript::CountAnyFlip(square, color, board)) myMOB++;
		else if (CGameScript::AnyPotMobility(board, square, oppcolor)) potMobility++;
		if (CGameScript::CountAnyFlip(square, oppcolor, board)) opMOB++;
		else if (CGameScript::AnyPotMobility(board, square, color)) oppPotMobility++;
	}
	for (int i = 0; i < midBoardLength; i++){
		square = midBoard[i];
		if (board[square] == color){
			myDISC++;
			if (CGameScript::IsStab(board, square, color))
				mySTAB++;
		}else if (board[square] == oppcolor){
			opDISC++;
			if (CGameScript::IsStab(board, square, oppcolor))
				opSTAB++;
		}
	}
	delta = getDeltaKeyano(board, color, oppcolor);
	unSTAB = getUnStab(board, color) - getUnStab(board, oppcolor);
	sum = (((((((((myDISC * weight_train[emptiesIndex][IND_MYDISC]) + (opDISC * weight_train[emptiesIndex][IND_OPDISC])) + (myMOB * weight_train[emptiesIndex][IND_MYMOB])) + (opMOB * weight_train[emptiesIndex][IND_OPMOB])) + (potMobility * weight_train[emptiesIndex][IND_MYPOTMOB])) + (oppPotMobility * weight_train[emptiesIndex][IND_OPPOTMOB])) + (mySTAB * weight_train[emptiesIndex][IND_MYSTAB])) + (opSTAB * weight_train[emptiesIndex][IND_OPSTAB])) + (unSTAB * weight_train[emptiesIndex][IND_UNSTAB])) + (delta * weight_train[emptiesIndex][IND_KEYNO]);
	return (sum + (get_score_edge_all(board, color, emptiesIndex) / 3));
}

int CArtEvaluation::StaEval2(ChessType* board, ChessType color, ChessType oppcolor, int empties, Empties* EmHead)
{
	int square, sum = 0, myDISC = 0, opDISC = 0, myMOB = 0, opMOB = 0;
	int potMobility = 0, oppPotMobility = 0, mySTAB = 0, opSTAB = 0;
	int delta = 0, unSTAB = 0, emptiesIndex = empties - 10;

	for (Empties* empties2 = EmHead->next; empties2 != NULL; empties2 = empties2->next){
		square = empties2->Square;
		if (CGameScript::CountAnyFlip(square, color, board)) myMOB++;
		else if (CGameScript::AnyPotMobility(board, square, oppcolor)) potMobility++;

		if (CGameScript::CountAnyFlip(square, oppcolor, board)) opMOB++;
		else if (CGameScript::AnyPotMobility(board, square, color)) oppPotMobility++;
	}
	for (int i = 0; i < midBoardLength; i++){
		square = midBoard[i];
		if (board[square] == color){
			myDISC++;
			if (CGameScript::IsStab(board, square, color)) mySTAB++;
		}else if (board[square] == oppcolor){
			opDISC++;
			if (CGameScript::IsStab(board, square, oppcolor)) opSTAB++;
		}
	}
	delta = getDeltaKeyano(board, color, oppcolor);
	unSTAB = getUnStab(board, color) - getUnStab(board, oppcolor);
	sum = (((((((((myDISC * weight_train[emptiesIndex][IND_MYDISC]) + (opDISC * weight_train[emptiesIndex][IND_OPDISC])) + (myMOB * weight_train[emptiesIndex][IND_MYMOB])) + (opMOB * weight_train[emptiesIndex][IND_OPMOB])) + (potMobility * weight_train[emptiesIndex][IND_MYPOTMOB])) + (oppPotMobility * weight_train[emptiesIndex][IND_OPPOTMOB])) + (mySTAB * weight_train[emptiesIndex][IND_MYSTAB])) + (opSTAB * weight_train[emptiesIndex][IND_OPSTAB])) + (unSTAB * weight_train[emptiesIndex][IND_UNSTAB])) + (delta * weight_train[emptiesIndex][IND_KEYNO]);
	sum += get_score_edge_all(board, color, emptiesIndex) / 4;

	if (board[PT_D4] == color) sum += 24;
	else if (board[PT_D4] == oppcolor) sum -= 24;
	if (board[PT_E4] == color) sum += 24;
	else if (board[PT_E4] == oppcolor) sum -= 24;
	if (board[PT_D5] == color) sum += 24;
	else if (board[PT_D5] == oppcolor) sum -= 24;
	if (board[PT_E5] == color) return (sum + 24);
	if (board[PT_E5] == oppcolor) sum -= 24;
	return sum;
}

void CArtEvaluation::Initial(){
	int edge[8];
	InitRecursion(edge, 0);
}

void CArtEvaluation::InitRecursion(int *edge, int depth)
{
	if(depth==8){
		int sum = edge[0];
		for(int i=0; i<7; sum += edge[++i])
			sum *= 3;
		for (i = 0; i < midGameLength; i++){
			score_edge[sum][i] = get_score_edge(edge, i, 2) - get_score_edge(edge, i, 0);
		}
		return;
	}
	for(edge[depth]=0; edge[depth]<3; edge[depth]++){
		InitRecursion(edge, depth+1);
	}
}