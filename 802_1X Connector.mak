# Microsoft Developer Studio Generated NMAKE File, Based on 802_1X Connector.dsp
!IF "$(CFG)" == ""
CFG=802_1X Connector - Win32 Debug
!MESSAGE No configuration specified. Defaulting to 802_1X Connector - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "802_1X Connector - Win32 Release" && "$(CFG)" != "802_1X Connector - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\802_1X Connector.exe"


CLEAN :
	-@erase "$(INTDIR)\802_1X Connector.obj"
	-@erase "$(INTDIR)\802_1X Connector.pch"
	-@erase "$(INTDIR)\802_1X Connector.res"
	-@erase "$(INTDIR)\802_1X ConnectorDlg.obj"
	-@erase "$(INTDIR)\ChooseCard.obj"
	-@erase "$(INTDIR)\md5.obj"
	-@erase "$(INTDIR)\ProPage1.obj"
	-@erase "$(INTDIR)\ProPage2.obj"
	-@erase "$(INTDIR)\ProPage3.obj"
	-@erase "$(INTDIR)\ProSheet.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\802_1X Connector.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /Ob0 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\802_1X Connector.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/D "NDEBUG" /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\802_1X Connector.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/o"$(OUTDIR)\802_1X Connector.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wpcap.lib iphlpapi.lib /subsystem:windows /pdb:none /machine:I386 /out:"$(OUTDIR)\802_1X Connector.exe" 
LINK32_OBJS= \
	"$(INTDIR)\802_1X Connector.obj" \
	"$(INTDIR)\802_1X ConnectorDlg.obj" \
	"$(INTDIR)\ChooseCard.obj" \
	"$(INTDIR)\ProPage1.obj" \
	"$(INTDIR)\ProPage2.obj" \
	"$(INTDIR)\ProPage3.obj" \
	"$(INTDIR)\ProSheet.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\md5.obj" \
	"$(INTDIR)\802_1X Connector.res"

"$(OUTDIR)\802_1X Connector.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\802_1X Connector.exe" "$(OUTDIR)\802_1X Connector.bsc"


CLEAN :
	-@erase "$(INTDIR)\802_1X Connector.obj"
	-@erase "$(INTDIR)\802_1X Connector.pch"
	-@erase "$(INTDIR)\802_1X Connector.res"
	-@erase "$(INTDIR)\802_1X Connector.sbr"
	-@erase "$(INTDIR)\802_1X ConnectorDlg.obj"
	-@erase "$(INTDIR)\802_1X ConnectorDlg.sbr"
	-@erase "$(INTDIR)\ChooseCard.obj"
	-@erase "$(INTDIR)\ChooseCard.sbr"
	-@erase "$(INTDIR)\md5.obj"
	-@erase "$(INTDIR)\md5.sbr"
	-@erase "$(INTDIR)\ProPage1.obj"
	-@erase "$(INTDIR)\ProPage1.sbr"
	-@erase "$(INTDIR)\ProPage2.obj"
	-@erase "$(INTDIR)\ProPage2.sbr"
	-@erase "$(INTDIR)\ProPage3.obj"
	-@erase "$(INTDIR)\ProPage3.sbr"
	-@erase "$(INTDIR)\ProSheet.obj"
	-@erase "$(INTDIR)\ProSheet.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\802_1X Connector.bsc"
	-@erase "$(OUTDIR)\802_1X Connector.exe"
	-@erase "$(OUTDIR)\802_1X Connector.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /Gi /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\802_1X Connector.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\802_1X Connector.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\802_1X Connector.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\802_1X Connector.sbr" \
	"$(INTDIR)\802_1X ConnectorDlg.sbr" \
	"$(INTDIR)\ChooseCard.sbr" \
	"$(INTDIR)\ProPage1.sbr" \
	"$(INTDIR)\ProPage2.sbr" \
	"$(INTDIR)\ProPage3.sbr" \
	"$(INTDIR)\ProSheet.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\md5.sbr"

"$(OUTDIR)\802_1X Connector.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=wpcap.lib iphlpapi.lib user32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\802_1X Connector.pdb" /debug /machine:I386 /out:"$(OUTDIR)\802_1X Connector.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\802_1X Connector.obj" \
	"$(INTDIR)\802_1X ConnectorDlg.obj" \
	"$(INTDIR)\ChooseCard.obj" \
	"$(INTDIR)\ProPage1.obj" \
	"$(INTDIR)\ProPage2.obj" \
	"$(INTDIR)\ProPage3.obj" \
	"$(INTDIR)\ProSheet.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\md5.obj" \
	"$(INTDIR)\802_1X Connector.res"

"$(OUTDIR)\802_1X Connector.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("802_1X Connector.dep")
!INCLUDE "802_1X Connector.dep"
!ELSE 
!MESSAGE Warning: cannot find "802_1X Connector.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "802_1X Connector - Win32 Release" || "$(CFG)" == "802_1X Connector - Win32 Debug"
SOURCE=".\802_1X Connector.cpp"

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"


"$(INTDIR)\802_1X Connector.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"


"$(INTDIR)\802_1X Connector.obj"	"$(INTDIR)\802_1X Connector.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ENDIF 

SOURCE=".\802_1X Connector.rc"

"$(INTDIR)\802_1X Connector.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=".\802_1X ConnectorDlg.cpp"

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"


"$(INTDIR)\802_1X ConnectorDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"


"$(INTDIR)\802_1X ConnectorDlg.obj"	"$(INTDIR)\802_1X ConnectorDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ENDIF 

SOURCE=.\ChooseCard.cpp

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"


"$(INTDIR)\ChooseCard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"


"$(INTDIR)\ChooseCard.obj"	"$(INTDIR)\ChooseCard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ENDIF 

SOURCE=.\ProPage1.cpp

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"


"$(INTDIR)\ProPage1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"


"$(INTDIR)\ProPage1.obj"	"$(INTDIR)\ProPage1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ENDIF 

SOURCE=.\ProPage2.cpp

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"


"$(INTDIR)\ProPage2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"


"$(INTDIR)\ProPage2.obj"	"$(INTDIR)\ProPage2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ENDIF 

SOURCE=.\ProPage3.cpp

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"


"$(INTDIR)\ProPage3.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"


"$(INTDIR)\ProPage3.obj"	"$(INTDIR)\ProPage3.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ENDIF 

SOURCE=.\ProSheet.cpp

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"


"$(INTDIR)\ProSheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"


"$(INTDIR)\ProSheet.obj"	"$(INTDIR)\ProSheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /Ob0 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\802_1X Connector.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\802_1X Connector.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /Gi /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\802_1X Connector.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\802_1X Connector.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=md5.cpp

!IF  "$(CFG)" == "802_1X Connector - Win32 Release"


"$(INTDIR)\md5.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ELSEIF  "$(CFG)" == "802_1X Connector - Win32 Debug"


"$(INTDIR)\md5.obj"	"$(INTDIR)\md5.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\802_1X Connector.pch"


!ENDIF 


!ENDIF 

