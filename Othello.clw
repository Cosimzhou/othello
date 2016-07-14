; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COthelloDlg
LastTemplate=CStatusBarCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Othello.h"

ClassCount=9
Class1=COthelloApp
Class2=COthelloDlg
Class3=CLibraryViewDlg

ResourceCount=14
Resource1=IDD_OTHELLO_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDR_MAIN_MENU (Chinese (中国))
Resource4=IDD_TIMELIMITED_DIALOG
Resource5=IDD_OTHELLO_DIALOG (Chinese (中国))
Resource6=IDD_ABOUTBOX (Chinese (中国))
Resource7=IDR_MAIN_MENU
Class4=CComputerPieceDlg
Resource8=IDD_OPENINGDLG_DIALOG
Resource9=IDD_COMPUTERPIECEDLG_DIALOG
Class5=COpeningDlg
Resource10=IDD_LIBRARYVIEWDLG_DIALOG
Class6=CAboutBox
Resource11=IDD_DIAGRAM_DIALOG
Class7=CDiagramDlg
Resource12=IDR_MENU_POPUP1
Class8=CSetTimeLimitDlg
Class9=CMyStatusBar
Resource13=IDD_ABOUTBOX_DIALOG
Resource14=IDR_ACCELERATOR_MAIN

[CLS:COthelloApp]
Type=0
HeaderFile=Othello.h
ImplementationFile=Othello.cpp
Filter=N
LastObject=COthelloApp

[CLS:COthelloDlg]
Type=0
HeaderFile=OthelloDlg.h
ImplementationFile=OthelloDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_MENU_TRAINING

[DLG:IDD_OTHELLO_DIALOG]
Type=1
Class=COthelloDlg
ControlCount=24
Control1=IDC_COMP_INFO,edit,1350569092
Control2=IDC_STATIC_COMMENT,static,1342308352
Control3=IDC_STATIC,static,1342308353
Control4=IDC_LBL_B_CH,static,1342308353
Control5=IDC_STATIC,static,1342308353
Control6=IDC_LBL_W_CH,static,1342308353
Control7=IDC_STATIC,static,1342308353
Control8=IDC_LBL_N_CH,static,1342308353
Control9=IDC_STATIC,static,1342308353
Control10=IDC_STATIC_VAL,static,1342308353
Control11=IDC_LIST_STEP,SysListView32,1350631433
Control12=IDC_STATIC_BNAME,static,1342308353
Control13=IDC_STATIC_WNAME,static,1342308353
Control14=IDC_STATIC,static,1342308353
Control15=IDC_STATIC_TIME,static,1342308353
Control16=IDC_STATIC_TRACE,static,1342308352
Control17=IDC_STATIC_LINE,static,1342308352
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC_BLACKTIME,static,1342177281
Control20=IDC_STATIC_WHITETIME,static,1342177281
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_LIST_CONSOLE,listbox,1352728833
Control24=IDC_COMBO_CMD,combobox,1344348162

[MNU:IDR_MAIN_MENU]
Type=1
Class=COthelloDlg
Command1=IDC_NEW_GAME
Command2=ID_MENU_OPEN
Command3=ID_MENU_SAVE
Command4=ID_MENU_OPENINGBOOK
Command5=ID_MENU_OPENLIBRARY
Command6=ID_MENU_COMPUTERPIECE
Command7=ID_MENU_STOPSEARCH
Command8=ID_MENU_PAUSEGAME
Command9=ID_MENUCOMPUTER_REFRESH
Command10=ID_MENU_REGRET
Command11=ID_MENU_REDO
Command12=IDCANCEL
Command13=ID_MENU_BOARD_NORMAL
Command14=ID_MENU_BOARD_ABNORMAL
Command15=ID_MENU_TURN_R
Command16=ID_MENU_TURN_L
Command17=ID_MENU_LOCSOUND
Command18=ID_MENU_ANIMATION
Command19=ID_MENU_HINTPOINT
Command20=ID_MENU_SHOWDATA
Command21=ID_MENU_CHESSBOOK
Command22=ID_MENU_TOPMOST
Command23=ID_MENU_SETLIMITED
Command24=ID_MENU_SHOWDIAGRAM
Command25=ID_MENU_OPENDIAGRAM
Command26=ID_MENU_SAVEDIAGRAM
Command27=ID_MENU_HELP_CONTENT
Command28=ID_MENU_ABOUTBOX
CommandCount=28

[DLG:IDD_OTHELLO_DIALOG (Chinese (中国))]
Type=1
Class=COthelloDlg
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NEW_GAME,button,1342242816
Control4=IDC_COMP_INFO,edit,1350634628
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308353
Control7=IDC_LBL_B_CH,static,1342308353
Control8=IDC_STATIC,static,1342308353
Control9=IDC_LBL_W_CH,static,1342308353
Control10=IDC_STATIC,static,1342308353
Control11=IDC_LBL_N_CH,static,1342308353
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308353
Control14=IDC_STATIC_LINE,button,1342178055
Control15=IDC_COMPUTER_SIDE,static,1342308352
Control16=IDC_LIST_STEP,listbox,1352728833

[MNU:IDR_MAIN_MENU (Chinese (中国))]
Type=1
Class=?
Command1=IDC_NEW_GAME
Command2=ID_MENUITEM32772
Command3=ID_MENUITEM32773
Command4=ID_COMPUTER_W_CH
Command5=ID_COMPUTER_B_CH
Command6=ID_COMPUTER_N_CH
Command7=ID_MENU_REGRET
Command8=ID_MENUITEM32778
Command9=IDCANCEL
Command10=ID_MENUITEM32780
Command11=ID_MENUITEM32781
CommandCount=11

[DLG:IDD_ABOUTBOX (Chinese (中国))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_COMPUTERPIECEDLG_DIALOG]
Type=1
Class=CComputerPieceDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO1,combobox,1344471043
Control6=IDC_COMBO2,combobox,1344339971
Control7=IDC_BUTTON_EXCHANGE,button,1342242816

[CLS:CComputerPieceDlg]
Type=0
HeaderFile=ComputerPieceDlg.h
ImplementationFile=ComputerPieceDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CComputerPieceDlg

[ACL:IDR_ACCELERATOR_MAIN]
Type=1
Class=?
Command1=ID_MENU_OPENLIBRARY
Command2=ID_MENU_OPEN
Command3=ID_MENU_OPENINGBOOK
Command4=ID_MENU_SAVE
Command5=ID_MENU_HELP_CONTENT
Command6=ID_MENU_STOPSEARCH
Command7=IDC_NEW_GAME
Command8=ID_MENU_COMPUTER_REFRESH
Command9=ID_MENU_COMPUTERPIECE
Command10=ID_MENU_SHOWDIAGRAM
Command11=ID_MENU_PAUSEGAME
Command12=ID_MENU_REGRET
Command13=ID_MENU_REDO
CommandCount=13

[DLG:IDD_OPENINGDLG_DIALOG]
Type=1
Class=?
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TREEVIEW,SysTreeView32,1350631431
Control4=IDC_STATIC_CONTENT,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO_C4,button,1342308361
Control7=IDC_RADIO_D3,button,1342177289
Control8=IDC_RADIO_E6,button,1342177289
Control9=IDC_RADIO_F5,button,1342177289

[CLS:COpeningDlg]
Type=0
HeaderFile=OpeningDlg.h
ImplementationFile=OpeningDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=COpeningDlg

[DLG:IDD_LIBRARYVIEWDLG_DIALOG]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728833
Control4=IDC_STATIC_CONTEXT,static,1342308352

[CLS:CLibraryViewDlg]
Type=0
HeaderFile=LibraryViewDlg.h
ImplementationFile=LibraryViewDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLibraryViewDlg

[CLS:CAboutBox]
Type=0
HeaderFile=AboutBox.h
ImplementationFile=AboutBox.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC
LastObject=CAboutBox

[DLG:IDD_ABOUTBOX_DIALOG]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC_PIC,static,1342177287

[CLS:CDiagramDlg]
Type=0
HeaderFile=DiagramDlg.h
ImplementationFile=DiagramDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDiagramDlg
VirtualFilter=dWC

[DLG:IDD_DIAGRAM_DIALOG]
Type=1
Class=CDiagramDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_DIAGRAM,static,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_RADIO_TYPE,button,1342308361
Control7=IDC_RADIO2,button,1342177289
Control8=IDC_RADIO3,button,1342177289
Control9=IDC_RADIO4,button,1342177289
Control10=IDC_RADIO5,button,1342177289

[DLG:IDD_TIMELIMITED_DIALOG]
Type=1
Class=CSetTimeLimitDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350639745
Control4=IDC_SPIN_LIMIT,msctls_updown32,1342177334
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CSetTimeLimitDlg]
Type=0
HeaderFile=SetTimeLimitDlg.h
ImplementationFile=SetTimeLimitDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSetTimeLimitDlg

[CLS:CMyStatusBar]
Type=0
HeaderFile=MyStatusBar.h
ImplementationFile=MyStatusBar.cpp
BaseClass=CStatusBarCtrl
Filter=W
LastObject=CMyStatusBar

[MNU:IDR_MENU_POPUP1]
Type=1
Class=?
Command1=ID_MENU_CONSOLE_CLEAR
Command2=ID_MENU_CONSOLE_SAVE
CommandCount=2

