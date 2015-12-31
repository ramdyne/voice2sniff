# Microsoft Developer Studio Project File - Name="mini_ptlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mini_ptlib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mini_ptlib.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mini_ptlib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W4 /Gm /GX /Zi /Od /I "C:\tools\gtk-dev\src\glib" /I "C:\tools\gtk-dev\src\gtk+" /D "WIN32" /D "NDEBUG" /D "MINI_PTLIB" /FR /FD /GZ /c
# ADD BASE RSC /l 0x413 /d "NDEBUG"
# ADD RSC /l 0x413 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /NODEFAULTLIB:libc

!ELSEIF  "$(CFG)" == "mini_ptlib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W4 /Gm /GX /Zi /Od /I "C:\d\ethereal\gtk+-dev\src\glib" /I "C:\d\ethereal\gtk+-dev\src\gtk+" /D "WIN32" /D "_DEBUG" /D "MINI_PTLIB" /FR /FD /I /GZ /c
# ADD BASE RSC /l 0x413 /d "_DEBUG"
# ADD RSC /l 0x413 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /NODEFAULTLIB:libcd

!ENDIF 

# Begin Target

# Name "mini_ptlib - Win32 Release"
# Name "mini_ptlib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\args.cxx
# End Source File
# Begin Source File

SOURCE=.\src\asner.cxx
# End Source File
# Begin Source File

SOURCE=.\src\assert.cxx
# End Source File
# Begin Source File

SOURCE=.\src\collect.cxx
# End Source File
# Begin Source File

SOURCE=.\src\contain.cxx
# End Source File
# Begin Source File

SOURCE=.\src\object.cxx
# End Source File
# Begin Source File

SOURCE=.\src\win32.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "ptlib"

# PROP Default_Filter ""
# Begin Group "vc++"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\include\ptlib\vc++\contain.h"
# End Source File
# Begin Source File

SOURCE=".\include\ptlib\vc++\debstrm.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\ptlib\args.h
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\array.h
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\asner.h
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\contain.h
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\contain.inl
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\dict.h
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\lists.h
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\object.h
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\osutil.inl
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\pstring.h
# End Source File
# Begin Source File

SOURCE=.\include\ptlib\ptlib.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\mini_ptlib.h
# End Source File
# End Group
# Begin Group "Make file"

# PROP Default_Filter "*.mak"
# Begin Source File

SOURCE=.\mini_ptlib.mak
# End Source File
# End Group
# End Target
# End Project
