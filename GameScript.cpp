// GameScript.cpp: implementation of the CGameScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameScript.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



const unsigned __int8 CGameScript::QuickDirMask[CH_LEN] = {
0,  0,  0,  0,  0,  0,  0,  0,  0,
0, 81, 81, 87, 87, 87, 87, 22, 22,
0, 81, 81, 87, 87, 87, 87, 22, 22,
0,121,121,255,255,255,255,182,182,
0,121,121,255,  0,  0,255,182,182,
0,121,121,255,  0,  0,255,182,182,
0,121,121,255,255,255,255,182,182,
0, 41, 41,171,171,171,171,162,162,
0, 41, 41,171,171,171,171,162,162,
0,  0,  0,  0,  0,  0,  0,  0,  0,
0
};

const unsigned __int8 CGameScript::CanSchInDrct[8]={ 1,2,4,8,16,32,64,128};
const int CGameScript::DrctInc[8]={ GO_RIGHT, GO_LEFT, GO_DOWNLEFT, GO_UPRIGHT, GO_DOWN, GO_UP, GO_DOWNRIGHT, GO_UPLEFT };
volatile BYTE* CGameScript::m_FlipTop=m_FlipStack;
volatile BYTE CGameScript::m_FlipStack[1000];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGameScript::CGameScript()
{

}

CGameScript::~CGameScript()
{

}

int CGameScript::FindLocablePt(ChessType PlayerColor, ChessType* Mapt, int* CanPutA)
{
	int i=X_UB, numloc=0;
	while(i != CH_LEN-X_UB){
		if(!*(Mapt+i)){
			if(CountAnyFlip(i, PlayerColor, Mapt)){
				CanPutA[numloc] = i;
				numloc++;
			}
		}
		i++;
	}
    return numloc;
}

int CGameScript::FindLocablePt(ChessType PlayerColor, ChessType *Mapt)
{
	int i=X_UB;
	while(i != CH_LEN-X_UB){
		if(!*(Mapt+i)){
			if(CountAnyFlip(i, PlayerColor, Mapt))
				return i;
		}
		i++;
	}
    return 0;
}

bool CGameScript::IsGameOver(ChessType* Mapt)
{
	if(!FindLocablePt(B_CH, Mapt)&&!FindLocablePt(W_CH, Mapt))
		return true;
	return false;
}

ChessType CGameScript::WinPlayer(ChessType* Mapt)
{
	int bn=0;
	ChessType *sq=&Mapt[LUC_in];
	ChessType *ed=&Mapt[RDC_in]+1;
	
	if(!IsGameOver(Mapt)) return 0;

	while(sq!=ed){
		if(*sq==B_CH)bn++;
		else if(*sq==W_CH)bn--;
		sq++;
	}
	return bn;
}

int CGameScript::CountChess(ChessType* Mapt, ChessType Player)
{
	int pn=0;
	ChessType *sq=&Mapt[LUC_in];
	ChessType *ed=&Mapt[RDC_in]+1;
	while(sq!=ed){
		if(*sq==Player)pn++;
		sq++;
	}
	return pn;	
}
void CGameScript::CountChess(ChessType* Mapt, short* ret)
{
	ChessType *sq=&Mapt[LUC_in];
	ChessType *ed=&Mapt[RDC_in]+1;
	*ret=*(ret+1)=0;
	while(sq!=ed){
		if(*sq==B_CH)(*ret)++;
		if(*sq==W_CH)(*(ret+1))++;
		sq++;
	}
}
int CGameScript::DirectLoc(ChessType *sq, ChessType* Mapt, int inc, ChessType color, ChessType oppcol, short*&FlipStack)
{
	ChessType *pt=sq + inc;
	if(*pt == oppcol){
		int count=1;
		pt+=inc;
		while(*pt == oppcol && count<6){
			count++;
			pt+=inc;
		}
		if(*pt == color) {
			pt-=inc;
			do{	*pt=color;
				*(FlipStack++)=pt-Mapt;
				pt-=inc;
			} while(pt != sq);
			return count;
		}
	}
	return 0;
}
int CGameScript::DoLoc(int pos, ChessType PlayerColor, ChessType* Mapt, short*&FlipStack) 
{
    int key=QuickDirMask[pos];
	int count=0;
	ChessType oppcol=Oppl_ch(PlayerColor);
    ChessType *sq;
    sq= Mapt+pos;
	for(int i=0; i<8; i++){
		if(key & CanSchInDrct[i])
			count+=DirectLoc(sq, Mapt, DrctInc[i], PlayerColor, oppcol, FlipStack);
	}

	if(count){
		*sq= PlayerColor;
		*(FlipStack++)=pos;
	}
    return count;
}
int CGameScript::DirectLoc(ChessType *sq, int inc, ChessType color, ChessType oppcol)
{
    ChessType *pt=sq + inc;
    if(*pt == oppcol){
        int count=1;
        pt+=inc;
		while(*pt == oppcol && count<6){
			count++;
            pt+=inc;
		}
        if(*pt == color) return count;
    }
    return 0;
}
int CGameScript::CountAnyFlip(int pos, ChessType PlayerColor, ChessType* Mapt)
{
    int key=QuickDirMask[pos];
	int count=0;
	ChessType oppcol=Oppl_ch(PlayerColor);
    ChessType *sq;
    sq= Mapt+pos;
	for(int i=0; i<8; i++){
		if(key & CanSchInDrct[i])
			count+=DirectLoc(sq, DrctInc[i], PlayerColor, oppcol);
	}
    return count;
}
int CGameScript::GenerateLoc(ChessType PlayerColor, ChessType*Mapt, FlipSpot *vp)
{
	int i=LUC_in, val, numloc=0;
	while(i!=RDC_in+1){
		if(*(Mapt+i)==EMPTY){
			if(val=CountAnyFlip(i, PlayerColor, Mapt)){
				if(vp){ vp[numloc].square = i;vp[numloc].flips =val;}
				numloc++;
			}
		}
		i++;
	}

    return numloc;
}

int CGameScript::DoFlips(ChessType* board, int sqnum, ChessType color, ChessType oppcolor)
{
	int key = QuickDirMask[sqnum];
	ChessType* sq = board + sqnum;
	BYTE* count = (BYTE*)m_FlipTop;
	for(int i=0; i<8; i++){
		if(key & CanSchInDrct[i])
			DrctnlFlips(board, sq, DrctInc[i], color, oppcolor);
	}
/*	if (num & 0x80)	DrctnlFlips(board, sq, DrctInc[7], color, oppcolor);
	if (num & 0x40)	 DrctnlFlips(board, sq, DrctInc[6], color, oppcolor);
	if (num & 0x20)	DrctnlFlips(board, sq, DrctInc[5], color, oppcolor);
	if (num & 0x10)	 DrctnlFlips(board, sq, DrctInc[4], color, oppcolor);
	if (num & 8)	 DrctnlFlips(board, sq, DrctInc[3], color, oppcolor);
	if (num & 4)	 DrctnlFlips(board, sq, DrctInc[2], color, oppcolor);
	if (num & 2)	 DrctnlFlips(board, sq, DrctInc[1], color, oppcolor);
	if (num & 1)	 DrctnlFlips(board, sq, DrctInc[0], color, oppcolor);
/*	if(m_FlipTop - count){
		TRACE("Pushing %x\n",count);
		TRACE("Pushed %x\n",m_FlipTop);
	}*/
	return (int)(m_FlipTop - count);
}

int CGameScript::DrctnlFlips(ChessType* board, ChessType* sq, int inc, ChessType color, ChessType oppcol)
{
	ChessType *pt=sq + inc;
	if(*pt == oppcol){
		pt+=inc;
		while(*pt == oppcol){
			pt+=inc;
		}
		if(*pt == color) {
			pt-=inc;
			do{	*pt=color;
				*(m_FlipTop++)=pt-board;
				pt-=inc;
			} while(pt != sq);
		}
	}
	return 0;
}

void CGameScript::UndoFlips(ChessType *board, int flipCount, ChessType oppcolor)
{
	while(flipCount--){
		ASSERT(m_FlipTop>=m_FlipStack);
		*(board + *(--m_FlipTop)) = oppcolor;
	}
}

bool CGameScript::AnyPotMobility(ChessType* board, int sqnum, ChessType oppcolor)
{
    if ((((board[sqnum + GO_LEFT] != oppcolor) && (board[sqnum + GO_RIGHT] != oppcolor)) && 
		((board[sqnum + GO_UPRIGHT] != oppcolor) && (board[sqnum + GO_DOWNLEFT] != oppcolor))) && 
		(((board[sqnum + GO_UPLEFT] != oppcolor) && (board[sqnum + GO_DOWNRIGHT] != oppcolor)) && 
		((board[sqnum + GO_UP] != oppcolor) && 	(board[sqnum + GO_DOWN] != oppcolor))))
    {
        return false;
    }
    return true;
}

bool CGameScript::IsStab(ChessType* board, int sqnum, ChessType color)
{
    int stability;
    int stability2;
    int num = QuickDirMask[sqnum];
    if (((num & 0x80) != 0) && ((num & 0x40) != 0)){
        stability = DrctnlStab(board, sqnum, DrctInc[7], color);
        if (stability != YES){
            stability2 = DrctnlStab(board, sqnum, DrctInc[6], color);
            if ((stability2 != YES) && ((stability == NO) || (stability2 == NO)))
                return false;
		}
	}

	if (((num & 0x20) != 0) && ((num & 0x10) != 0)){
        stability = DrctnlStab(board, sqnum, DrctInc[5], color);
        if (stability != YES){
            stability2 = DrctnlStab(board, sqnum, DrctInc[4], color);
            if ((stability2 != YES) && ((stability == NO) || (stability2 == NO)))
                return false;
        }
    }
    if (((num & 8) != 0) && ((num & 4) != 0)){
        stability = DrctnlStab(board, sqnum, DrctInc[3], color);
        if (stability != YES){
            stability2 = DrctnlStab(board, sqnum, DrctInc[2], color);
            if ((stability2 != YES) && ((stability == NO) || (stability2 == NO)))
                return false;
        }
    }
    if (((num & 2) != 0) && ((num & 1) != 0)){
        stability = DrctnlStab(board, sqnum, DrctInc[1], color);
        if (stability != YES){
            stability2 = DrctnlStab(board, sqnum, DrctInc[0], color);
            if ((stability2 != YES) && ((stability == NO) || (stability2 == NO)))
                return false;
        }
    }
    return true;
}

int CGameScript::DrctnlStab(ChessType* board, int boardIndex, int inc, ChessType color)
{
	ChessType type;
	int index = boardIndex;
	do {
		index += inc;
		type = board[index];
		if (type == BLOCK) return YES;
	} while (type == color);
	if (board[index] != EMPTY){
		do{
			if (board[index] == BLOCK)
				return MAYBE;
			index += inc;
		} while (board[index] != EMPTY);
	}
	return NO;
}

void CGameScript::StartClean()
{
	m_FlipTop=m_FlipStack;
}

bool CGameScript::IsLocable(int pos, ChessType PlayerColor, ChessType* Mapt)
{
    int key=QuickDirMask[pos];
	ChessType oppcol=Oppl_ch(PlayerColor);
    ChessType *sq = Mapt+pos;
	if(*sq) return false;
	for(int i=0; i<8; i++){
		if(key & CanSchInDrct[i])
			if(DirectLoc(sq, DrctInc[i], PlayerColor, oppcol)) 
				return true;
	}
/*	if(key & 0x80)	if(DirectLoc(sq, DrctInc[7], PlayerColor, oppcol)) return true;
    if(key & 0x40)	if(DirectLoc(sq, DrctInc[6], PlayerColor, oppcol)) return true;
    if(key & 0x20)	if(DirectLoc(sq, DrctInc[5], PlayerColor, oppcol)) return true;
    if(key & 0x10)	if(DirectLoc(sq, DrctInc[4], PlayerColor, oppcol)) return true;
    if(key & 8)		if(DirectLoc(sq, DrctInc[3], PlayerColor, oppcol)) return true;
    if(key & 4)		if(DirectLoc(sq, DrctInc[2], PlayerColor, oppcol)) return true;
    if(key & 2)		if(DirectLoc(sq, DrctInc[1], PlayerColor, oppcol)) return true;
    if(key & 1)		if(DirectLoc(sq, DrctInc[0], PlayerColor, oppcol)) return true;
  */  
	return false;
}

int CGameScript::CountLocablePt(ChessType PlayerColor, ChessType* Mapt)
{
	int i=X_UB, numloc=0;
	while(i != CH_LEN-X_UB){
		if(!*(Mapt+i)){
			if(IsLocable(i, PlayerColor, Mapt)){
				numloc++;
			}
		}
		i++;
	}
    return numloc;
}

