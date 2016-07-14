// Othello.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Othello.h"
#include "OthelloDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COthelloApp

BEGIN_MESSAGE_MAP(COthelloApp, CWinApp)
	//{{AFX_MSG_MAP(COthelloApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COthelloApp construction

COthelloApp::COthelloApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COthelloApp object

COthelloApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COthelloApp initialization

BOOL COthelloApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
#ifndef	_AS_GREEN_SOFTWARE
	HKEY hkey;
	char* szSubKey="Software\\Setalligence\\Othello";
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
#endif

	//MessageBox(NULL, , "", MB_OK);////GetCommandLine()
//	char* cmdBuf = GetCommandLine();
	char* lpCmd = new char[strlen(m_pszHelpFilePath)];
	strcpy(lpCmd, m_pszHelpFilePath);
	char* lpEnd = lpCmd + strlen(m_pszHelpFilePath);
	*(--lpEnd) = 'I';
	*(--lpEnd) = 'N';
	*(--lpEnd) = 'I';
	m_pszProfileName=_tcsdup(lpCmd);

	//MessageBox(NULL, m_pszHelpFilePath, "", MB_OK);

	DWORD Keep=0;
	BOOL LocSound;
	BOOL ShowHint;
	BOOL WBBW;
	BOOL TopMost;
	BOOL Showdata;
	BOOL Animation;
	BOOL UseBook;
	int TimeLimit;
	int PlayerType[2];

#ifdef	_AS_GREEN_SOFTWARE
	BOOL lRet;
	LocSound  = GetProfileInt("UIOption", "LocSound", 1);
	ShowHint  = GetProfileInt("UIOption", "ShowHint", 1);
	WBBW      = GetProfileInt("UIOption","FormalArrangement",1);
	Animation = GetProfileInt("UIOption", "Animation", 0);
	TopMost   = GetProfileInt("UIOption", "TopMost", 0);
	Showdata  = GetProfileInt("UIOption", "ShowData", 1);
	UseBook   = GetProfileInt("Algorithm", "UseBook", 0);
	PlayerType[0] = GetProfileInt("Algorithm", "PlayerBlack", 0);
	PlayerType[1] = GetProfileInt("Algorithm", "PlayerWhite", 0);
	TimeLimit = GetProfileInt("Algorithm", "TimeLimit", 0);
	Keep=1;
#else
	LONG lret= RegCreateKeyEx(HKEY_CURRENT_USER, szSubKey, 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &dwDisposition);
	
	if(lret==ERROR_SUCCESS){
		DWORD dwType, dwLength;
		BYTE bContent[10];
		LONG lRet;
		lRet =RegQueryValueEx(hkey, "LocSound", 0, &dwType, bContent, &dwLength);
		if(lRet==ERROR_SUCCESS){
			LocSound=*(reinterpret_cast<bool*>(bContent));
			Keep|=1;
		}
		lRet =RegQueryValueEx(hkey, "ShowHint", 0, &dwType, bContent, &dwLength);
		if(lRet==ERROR_SUCCESS){
			ShowHint=*(reinterpret_cast<bool*>(bContent));
			Keep|=2;
		}
		lRet =RegQueryValueEx(hkey, "WBBW", 0, &dwType, bContent, &dwLength);
		if(lRet==ERROR_SUCCESS){
			WBBW=*(reinterpret_cast<bool*>(bContent));
			Keep|=4;
		}
		lRet =RegQueryValueEx(hkey, "TopMost", 0, &dwType, bContent, &dwLength);
		if(lRet==ERROR_SUCCESS){
			TopMost=*(reinterpret_cast<bool*>(bContent));
			Keep|=8;
		}
		dwType=REG_BINARY;
		lRet =RegQueryValueEx(hkey, "Player", 0, &dwType, bContent, &dwLength);
		if(lRet==ERROR_SUCCESS){
			PlayerType[1]=(int)*(reinterpret_cast<short*>(bContent));
			PlayerType[0]=(int)*(reinterpret_cast<short*>(bContent+sizeof(short)));
			Keep|=16;
		}
		lRet =RegQueryValueEx(hkey, "UseBook", 0, &dwType, bContent, &dwLength);
		if(lRet==ERROR_SUCCESS){
			UseBook=*(reinterpret_cast<bool*>(bContent));
			Keep|=32;
		}	
		lRet =RegQueryValueEx(hkey, "ShowData", 0, &dwType, bContent, &dwLength);
		if(lRet==ERROR_SUCCESS){
			Showdata=*(reinterpret_cast<bool*>(bContent));
			Keep|=32;
		}
		lRet =RegQueryValueEx(hkey, "Animation", 0, &dwType, bContent, &dwLength);
		if(lRet==ERROR_SUCCESS){
			Animation=*(reinterpret_cast<bool*>(bContent));
			Keep|=32;
		}
		
		RegCloseKey(hkey);
	}
#endif
	COthelloDlg dlg;
	m_pMainWnd = &dlg;
	if(Keep){
		dlg.m_Keep = true;
		dlg.m_LocSound =!LocSound;
		dlg.m_ShowHint =!ShowHint;
		dlg.m_WBBW = (WBBW!=FALSE);
		dlg.m_TopMost=!TopMost;
		dlg.m_PlayerType[0]=PlayerType[0];
		dlg.m_PlayerType[1]=PlayerType[1];
		dlg.m_UseBook=!UseBook;
		dlg.m_ShowData=!Showdata;
		dlg.m_bAnimation=!Animation;
		 dlg.m_TimeLimit= TimeLimit;
	}else
		dlg.m_Keep = false;

	int nResponse = dlg.DoModal();
	
	Keep=dlg.m_Keep;
	if(!Keep){
		LocSound		= dlg.m_LocSound;
		ShowHint		= dlg.m_ShowHint;
		WBBW			= dlg.m_WBBW;
		TopMost			= dlg.m_TopMost;
		PlayerType[0]	= dlg.m_PlayerType[0];
		PlayerType[1]	= dlg.m_PlayerType[1];
		UseBook			= dlg.m_UseBook;
		Animation		= dlg.m_bAnimation;
		TimeLimit		= dlg.m_TimeLimit;
#ifdef	_AS_GREEN_SOFTWARE
		lRet =  WriteProfileInt("UIOption", "LocSound", LocSound);
		lRet &= WriteProfileInt("UIOption", "ShowHint", ShowHint);
		lRet &= WriteProfileInt("UIOption", "FormalArrangement", WBBW);
		lRet &= WriteProfileInt("UIOption", "Animation", Animation);
		lRet &= WriteProfileInt("UIOption", "TopMost", TopMost);
		lRet &= WriteProfileInt("UIOption", "ShowData", Showdata);
		lRet &= WriteProfileInt("Algorithm", "UseBook", UseBook);
		lRet &= WriteProfileInt("Algorithm", "PlayerBlack", PlayerType[0]);
		lRet &= WriteProfileInt("Algorithm", "PlayerWhite", PlayerType[1]);
		lRet &= WriteProfileInt("Algorithm", "TimeLimit", TimeLimit);

#else
		lret= RegCreateKeyEx(HKEY_CURRENT_USER, szSubKey, 0, NULL, 
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &dwDisposition);
		if(lret==ERROR_SUCCESS){
			Keep = (PlayerType[0]<<16)| PlayerType[1];
			RegSetValueEx(hkey, "LocSound", 0, REG_DWORD, (BYTE*)&LocSound, sizeof(BOOL));
			RegSetValueEx(hkey, "ShowHint", 0, REG_DWORD, (BYTE*)&ShowHint, sizeof(BOOL));
			RegSetValueEx(hkey, "WBBW",     0, REG_DWORD, (BYTE*)&WBBW, sizeof(BOOL));
			RegSetValueEx(hkey, "TopMost",  0, REG_DWORD, (BYTE*)&TopMost, sizeof(BOOL));
			RegSetValueEx(hkey, "Player",   0, REG_DWORD, (BYTE*)&Keep, sizeof(DWORD));
			RegSetValueEx(hkey, "UseBook",  0, REG_DWORD, (BYTE*)&UseBook, sizeof(DWORD));	
			RegSetValueEx(hkey, "ShowData",  0, REG_DWORD, (BYTE*)&Showdata, sizeof(DWORD));	
			RegSetValueEx(hkey, "Animation",  0, REG_DWORD, (BYTE*)&Animation, sizeof(DWORD));	
		}
#endif
	}
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
