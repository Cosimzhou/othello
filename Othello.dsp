# Microsoft Developer Studio Project File - Name="Othello" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Othello - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Othello.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Othello.mak" CFG="Othello - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Othello - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Othello - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Othello - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386

!ELSEIF  "$(CFG)" == "Othello - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Othello - Win32 Release"
# Name "Othello - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Midi\MidiOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\Midi\MusicPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Midi\ScoreDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\Midi\ZPDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\Midi\ZPKeyMap.cpp
# End Source File
# Begin Source File

SOURCE=.\AboutBox.cpp
# End Source File
# Begin Source File

SOURCE=.\AnnBp.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtBaseSolve.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtEndSolve.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtEvaluation.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtMidSolve.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtStaSolve.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\ComputerPieceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ComputerThink.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EvaluatorMother.cpp
# End Source File
# Begin Source File

SOURCE=.\Game.cpp
# End Source File
# Begin Source File

SOURCE=.\GameScript.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphic.cpp
# End Source File
# Begin Source File

SOURCE=.\ImprovedEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\ImprovedEvaluation.cpp
# End Source File
# Begin Source File

SOURCE=.\LibraryViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NankEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\OpeningDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OpeningReader.cpp
# End Source File
# Begin Source File

SOURCE=.\Othello.cpp
# End Source File
# Begin Source File

SOURCE=.\Othello.rc
# End Source File
# Begin Source File

SOURCE=.\OthelloDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegionEvaluator.cpp
# End Source File
# Begin Source File

SOURCE=.\RowEvaluator.cpp
# End Source File
# Begin Source File

SOURCE=.\SetTimeLimitDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SevenEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ThunderEngine.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Midi\MidiOutput.h
# End Source File
# Begin Source File

SOURCE=.\Midi\MusicPlayer.h
# End Source File
# Begin Source File

SOURCE=.\Midi\ScoreDocument.h
# End Source File
# Begin Source File

SOURCE=.\Midi\ZPDocument.h
# End Source File
# Begin Source File

SOURCE=.\Midi\ZPKeyMap.h
# End Source File
# Begin Source File

SOURCE=.\AboutBox.h
# End Source File
# Begin Source File

SOURCE=.\AnnBp.h
# End Source File
# Begin Source File

SOURCE=.\ArtBaseSolve.h
# End Source File
# Begin Source File

SOURCE=.\ArtEndSolve.h
# End Source File
# Begin Source File

SOURCE=.\ArtEngine.h
# End Source File
# Begin Source File

SOURCE=.\ArtEvaluation.h
# End Source File
# Begin Source File

SOURCE=.\ArtMidSolve.h
# End Source File
# Begin Source File

SOURCE=.\ArtStaSolve.h
# End Source File
# Begin Source File

SOURCE=.\BasicEngine.h
# End Source File
# Begin Source File

SOURCE=.\ComputerPieceDlg.h
# End Source File
# Begin Source File

SOURCE=.\ComputerThink.h
# End Source File
# Begin Source File

SOURCE=.\DiagramDlg.h
# End Source File
# Begin Source File

SOURCE=.\EngineMother.h
# End Source File
# Begin Source File

SOURCE=.\EvaluatorMother.h
# End Source File
# Begin Source File

SOURCE=.\Game.h
# End Source File
# Begin Source File

SOURCE=.\GameScript.h
# End Source File
# Begin Source File

SOURCE=.\Graphic.h
# End Source File
# Begin Source File

SOURCE=.\ImprovedEngine.h
# End Source File
# Begin Source File

SOURCE=.\ImprovedEvaluation.h
# End Source File
# Begin Source File

SOURCE=.\LibraryViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\NankEngine.h
# End Source File
# Begin Source File

SOURCE=.\OpeningDlg.h
# End Source File
# Begin Source File

SOURCE=.\OpeningReader.h
# End Source File
# Begin Source File

SOURCE=.\Othello.h
# End Source File
# Begin Source File

SOURCE=.\OthelloDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegionEvaluator.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RowEvaluator.h
# End Source File
# Begin Source File

SOURCE=.\SetTimeLimitDlg.h
# End Source File
# Begin Source File

SOURCE=.\SevenEngine.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ThunderEngine.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\b0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BM.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Hd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=".\res\logo副本.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Othello.ico
# End Source File
# Begin Source File

SOURCE=.\res\Othello.rc2
# End Source File
# Begin Source File

SOURCE=.\res\RT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TreeNode.bmp
# End Source File
# Begin Source File

SOURCE=.\res\w0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\w1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\WAVE_SOUND.wav
# End Source File
# Begin Source File

SOURCE=".\res\开局库.txt"
# End Source File
# End Target
# End Project
# Section Othello : {6B7E638F-850A-101B-AFC0-4210102A8DA7}
# 	2:21:DefaultSinkHeaderFile:statusbar.h
# 	2:16:DefaultSinkClass:CStatusBar1
# End Section
# Section Othello : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section Othello : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section Othello : {2C787A50-E01C-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CPanels
# 	2:10:HeaderFile:panels.h
# 	2:8:ImplFile:panels.cpp
# End Section
# Section Othello : {6E1B5150-DB62-11D0-A0D8-0080C7E7B78D}
# 	2:5:Class:CPanel
# 	2:10:HeaderFile:panel.h
# 	2:8:ImplFile:panel.cpp
# End Section
# Section Othello : {E6E17E88-DF38-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CStatusBar1
# 	2:10:HeaderFile:statusbar.h
# 	2:8:ImplFile:statusbar.cpp
# End Section
