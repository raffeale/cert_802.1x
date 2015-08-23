# Microsoft Developer Studio Project File - Name="802_1X Connector" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=802_1X Connector - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "802_1X Connector.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "802_1X Connector.mak" CFG="802_1X Connector - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "802_1X Connector - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "802_1X Connector - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /u /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /D "NDEBUG" /win32
# SUBTRACT MTL /nologo
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wpcap.lib iphlpapi.lib /subsystem:windows /pdb:none /machine:I386
# SUBTRACT LINK32 /nologo

!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wpcap.lib iphlpapi.lib user32.lib /nologo /subsystem:windows /profile /debug /machine:I386
# SUBTRACT LINK32 /map /nodefaultlib

!ENDIF 

# Begin Target

# Name "802_1X Connector - Win32 Release"
# Name "802_1X Connector - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\802_1X Connector.cpp"
# End Source File
# Begin Source File

SOURCE=".\802_1X Connector.rc"
# End Source File
# Begin Source File

SOURCE=".\802_1X ConnectorDlg.cpp"
# End Source File
# Begin Source File

SOURCE=.\ChooseCard.cpp
# End Source File
# Begin Source File

SOURCE=.\ProPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\ProPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\ProPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\ProSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\802_1X Connector.h"
# End Source File
# Begin Source File

SOURCE=".\802_1X ConnectorDlg.h"
# End Source File
# Begin Source File

SOURCE=.\ChooseCard.h
# End Source File
# Begin Source File

SOURCE=md5.cpp
# End Source File
# Begin Source File

SOURCE=.\ProSheet.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE="C:\Program Files\Microsoft Visual Studio\VC98\Include\StrAlign.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\802_1X Connector.ico"
# End Source File
# Begin Source File

SOURCE=".\res\802_1X Connector.rc2"
# End Source File
# Begin Source File

SOURCE=".\802_1X Connector.rgs"
# End Source File
# Begin Source File

SOURCE=.\res\CERT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cert.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section 802_1X Connector : {00010009-000A-0001-0B00-01000C000100}
# 	1:20:IDR_MY802_1XCONNECTO:103
# End Section
