@echo off
IF NOT EXIST .\build mkdir .\build
pushd .\build

:: TODO: check out Chandler Carruth - optimisation guy on LLVM

:: Compiler Flags:
:: |  FLAG  | DESCRIPTION
:: | D      | compiler level #defines
:: | Oi     | use intrinsics whenever possible
:: | Zi     | debug info
:: | W4     | compile-time warnings
:: | WX     | treat warnings as errors
:: | wd     | disable warnings for a specific warning code
:: | FC     | compile-time errors show full path to source code
:: | nologo | turn off compiler name banner
REM old cmd -> cl -nologo -Zi -Oi -FC -W4 -WX -DKRYSTAL_WIN32=1 ..\code\win32_handmade.cpp user32.lib Gdi32.lib

set compiler_flags=-nologo -Zi -Oi -FC -W4 -WX
set defines=-DKRYSTAL_WINDOWS=1
set disable_warnings=-wd4100
set include_dirs=/I "..\src\Core" /I "..\src\Platform\Windows"
set entry_point=..\src\Platform\Windows\WindowsEntry.cpp
set additional_translation_units=..\src\Platform\Windows\WindowsWindow.cpp
set linked_libs=user32.lib Gdi32.lib

cl^
 %compiler_flags%^
 %defines%^
 %disable_warnings%^
 %include_dirs%^
 %entry_point%^
 %additional_translation_units%^
 %linked_libs%

if %ERRORLEVEL% equ 0 (echo Compilation succeeded.)

popd