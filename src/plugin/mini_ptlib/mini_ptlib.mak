# Microsoft Developer Studio Generated NMAKE File, Based on mini_ptlib.dsp
!IF "$(CFG)" == ""
CFG=mini_ptlib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to mini_ptlib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "mini_ptlib - Win32 Release" && "$(CFG)" != "mini_ptlib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mini_ptlib.mak" CFG="mini_ptlib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mini_ptlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mini_ptlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "mini_ptlib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\mini_ptlib.lib"


CLEAN :
	-@erase "$(INTDIR)\args.obj"
	-@erase "$(INTDIR)\asner.obj"
	-@erase "$(INTDIR)\assert.obj"
	-@erase "$(INTDIR)\collect.obj"
	-@erase "$(INTDIR)\contain.obj"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(OUTDIR)\mini_ptlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\mini_ptlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mini_ptlib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\mini_ptlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\args.obj" \
	"$(INTDIR)\asner.obj" \
	"$(INTDIR)\assert.obj" \
	"$(INTDIR)\collect.obj" \
	"$(INTDIR)\contain.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\win32.obj"

"$(OUTDIR)\mini_ptlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mini_ptlib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mini_ptlib.lib" "$(OUTDIR)\mini_ptlib.bsc"


CLEAN :
	-@erase "$(INTDIR)\args.obj"
	-@erase "$(INTDIR)\args.sbr"
	-@erase "$(INTDIR)\asner.obj"
	-@erase "$(INTDIR)\asner.sbr"
	-@erase "$(INTDIR)\assert.obj"
	-@erase "$(INTDIR)\assert.sbr"
	-@erase "$(INTDIR)\collect.obj"
	-@erase "$(INTDIR)\collect.sbr"
	-@erase "$(INTDIR)\contain.obj"
	-@erase "$(INTDIR)\contain.sbr"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\object.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(INTDIR)\win32.sbr"
	-@erase "$(OUTDIR)\mini_ptlib.bsc"
	-@erase "$(OUTDIR)\mini_ptlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "MINI_PTLIB" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mini_ptlib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\args.sbr" \
	"$(INTDIR)\asner.sbr" \
	"$(INTDIR)\assert.sbr" \
	"$(INTDIR)\collect.sbr" \
	"$(INTDIR)\contain.sbr" \
	"$(INTDIR)\object.sbr" \
	"$(INTDIR)\win32.sbr"

"$(OUTDIR)\mini_ptlib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\mini_ptlib.lib" /NODEFAULTLIB:libcd 
LIB32_OBJS= \
	"$(INTDIR)\args.obj" \
	"$(INTDIR)\asner.obj" \
	"$(INTDIR)\assert.obj" \
	"$(INTDIR)\collect.obj" \
	"$(INTDIR)\contain.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\win32.obj"

"$(OUTDIR)\mini_ptlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("mini_ptlib.dep")
!INCLUDE "mini_ptlib.dep"
!ELSE 
!MESSAGE Warning: cannot find "mini_ptlib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "mini_ptlib - Win32 Release" || "$(CFG)" == "mini_ptlib - Win32 Debug"
SOURCE=.\src\args.cxx

!IF  "$(CFG)" == "mini_ptlib - Win32 Release"


"$(INTDIR)\args.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "mini_ptlib - Win32 Debug"


"$(INTDIR)\args.obj"	"$(INTDIR)\args.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\asner.cxx

!IF  "$(CFG)" == "mini_ptlib - Win32 Release"


"$(INTDIR)\asner.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "mini_ptlib - Win32 Debug"


"$(INTDIR)\asner.obj"	"$(INTDIR)\asner.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\assert.cxx

!IF  "$(CFG)" == "mini_ptlib - Win32 Release"


"$(INTDIR)\assert.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "mini_ptlib - Win32 Debug"


"$(INTDIR)\assert.obj"	"$(INTDIR)\assert.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\collect.cxx

!IF  "$(CFG)" == "mini_ptlib - Win32 Release"


"$(INTDIR)\collect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "mini_ptlib - Win32 Debug"


"$(INTDIR)\collect.obj"	"$(INTDIR)\collect.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\contain.cxx

!IF  "$(CFG)" == "mini_ptlib - Win32 Release"


"$(INTDIR)\contain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "mini_ptlib - Win32 Debug"


"$(INTDIR)\contain.obj"	"$(INTDIR)\contain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\object.cxx

!IF  "$(CFG)" == "mini_ptlib - Win32 Release"


"$(INTDIR)\object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "mini_ptlib - Win32 Debug"


"$(INTDIR)\object.obj"	"$(INTDIR)\object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE=.\src\win32.cxx

!IF  "$(CFG)" == "mini_ptlib - Win32 Release"


"$(INTDIR)\win32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "mini_ptlib - Win32 Debug"


"$(INTDIR)\win32.obj"	"$(INTDIR)\win32.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

