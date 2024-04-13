@echo off
cls

IF NOT EXIST .\build mkdir .\build
pushd .\build

:: Compiler Flags:
:: |  FLAG  | DESCRIPTION
:: | D      | compiler level #defines
:: | O2     | enable optimisations
:: | Oi     | use intrinsics whenever possible
:: | Zi     | debug info
:: | W4     | compile-time warnings
:: | WX     | treat warnings as errors
:: | wd     | disable warnings for a specific warning code
:: | FC     | compile-time errors show full path to source code
:: | nologo | turn off compiler name banner

set compiler_flags=-nologo -Zi -Oi -FC -W4 -WX
set defines=-DKRYSTAL_WINDOWS=1
set disable_warnings=-wd4100
set include_dirs=/I "..\src\Core" /I "..\src\Platform\Windows"
set entry_point=..\src\Platform\Windows\WindowsEntry.cpp
set additional_translation_units=^
..\src\Platform\Windows\WindowsWindow.cpp ^
..\src\Core\Application.cpp
set linked_libs=user32.lib Gdi32.lib

set startTime=%time%
echo Compilation started at %startTime%.

cl^
 %compiler_flags%^
 %defines%^
 %disable_warnings%^
 %include_dirs%^
 %entry_point%^
 %additional_translation_units%^
 %linked_libs%

if %ERRORLEVEL% equ 0 (echo Compilation succeeded.)

set endTime=%time%
set /A "startSecs=((%startTime:~0,2%*3600)+(%startTime:~3,2%*60)+%startTime:~6,2%)"
set /A "endSecs=((%endTime:~0,2%*3600)+(%endTime:~3,2%*60)+%endTime:~6,2%)"
set /A "durationSecs=%endSecs%-%startSecs%"
echo Compilation finished at %endTime% (%durationSecs%s)

popd

exit /b %ERRORLEVEL%