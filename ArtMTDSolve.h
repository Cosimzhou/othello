// MTDSolve.h: interface for the CArtMTDSolve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTDSOLVE_H__C41093CE_5304_4821_B015_9FE686FEA1AE__INCLUDED_)
#define AFX_MTDSOLVE_H__C41093CE_5304_4821_B015_9FE686FEA1AE__INCLUDED_

//#include "ArtBaseSolve.h"
#include "ArtMIDSolve.h"
#include "ArtEndSolve.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArtMTDSolve  : public CArtBaseSolve
{
public:
	void SetSolver(CArtEndSolve*, CArtMidSolve*);
	CArtEndSolve* m_pEndSolve;
	CArtMidSolve* m_pMidSolve;
	CArtMTDSolve();
	virtual ~CArtMTDSolve();
	double Solve(ChessType* board, int alpha, int beta, ChessType color, int empties, int discdiff, int prevmove);

	
//		private int bestMove;
//		private static string engineName = Settings.Default.EGEngine;
//		private bool existEGEngine;
//		private int nodes = 0;

/*		public MTDSolve(){
			try{
				this.existEGEngine = File.Exists(engineName);
			}catch{
				this.existEGEngine = false;
			}
		}
		[DllImport("EGEngine", EntryPoint="AI_GetBestMove", SetLastError=true)]
		public static extern int MyDllAI_GetBestMove();
		[DllImport("EGEngine", EntryPoint="AI_GetEval", SetLastError=true)]
		public static extern int MyDllAI_GetEval();
		[DllImport("EGEngine", EntryPoint="AI_GetNodes", SetLastError=true)]
		public static extern int MyDllAI_GetNodes();
		[DllImport("EGEngine", EntryPoint="SetDepth", SetLastError=true)]
		public static extern void MyDllAI_SetDepth(int mid, int wld, int end);
		[DllImport("EGEngine", EntryPoint="AI_Slove", SetLastError=true)]
		public static extern void MyDllAI_Slove(int[] curboard, int color, int mode, int n_bits);
		public void SetDepth(int midDepth, int wldDepth, int endDepth)
		{
			if (this.existEGEngine){
				MyDllAI_SetDepth(midDepth, wldDepth, endDepth);
			}
		}*/

/*
		public int BestMove{
			get{return this.bestMove;}
		}

		public bool ExistEGEngine{
			get{return this.existEGEngine;}
		}

		public int Nodes{
			get{return this.nodes;}
		}

		public enum Mode{
			DEFAULT = -1,
			EXECT = 0,
			WLD = 1
		}
	}*/

};

#endif // !defined(AFX_MTDSOLVE_H__C41093CE_5304_4821_B015_9FE686FEA1AE__INCLUDED_)
