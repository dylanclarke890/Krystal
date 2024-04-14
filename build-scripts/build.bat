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
:: | MP     | enable multi-processing compilation
:: | /std:  | compiler version e.g. c++20
set compiler-flags=-nologo -Zi -Oi -FC -W4 -WX -MP -EHsc -std:c++20

set entry-point=..\src\Platform\Windows\WindowsEntry.cpp

set include-dirs=^
/I "..\src\Core" ^
/I "..\src\Platform\Windows"

set additional-translation-units=^
..\src\Platform\Windows\WindowsPerformance.cpp ^
..\src\Platform\Windows\WindowsLogger.cpp ^
..\src\Platform\Windows\WindowsInput.cpp ^
..\src\Platform\Windows\WindowsWindow.cpp ^
..\src\Core\Application.cpp

set defines=^
-DKRYSTAL_WINDOWS=1

set linked-libs=^
user32.lib ^
Gdi32.lib

set disable-warnings=-wd4100
:: End compiler settings

set start_time=%time%
echo Compilation started at %start_time%.

cl^
 %compiler-flags%^
 %defines%^
 %disable-warnings%^
 %include-dirs%^
 %entry-point%^
 %additional-translation-units%^
 %linked-libs%

set compile-error=%ERRORLEVEL%
if %compile-error% equ 0 (echo Compilation succeeded.)

set end_time=%time%
set /A "start_in_seconds=((%start_time:~0,2%*3600)+(%start_time:~3,2%*60)+%start_time:~6,2%)"
set /A "end_in_seconds=((%end_time:~0,2%*3600)+(%end_time:~3,2%*60)+%end_time:~6,2%)"
set /A "duration_in_seconds=%end_in_seconds%-%start_in_seconds%"
echo Compilation finished at %end_time% (%duration_in_seconds%s)

popd

exit /b %compile-error%