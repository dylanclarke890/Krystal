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

:: Custom Defines:
:: |           -D            |             Description
:: | KRYS_ENABLE_DEBUG_BREAK | Turn on breakpoints (needed for asserts)
:: | KRYS_ENABLE_ASSERTS     | Runtime asserts that trigger a break point on fail
:: | KRYS_ENABLE_LOGGING     | Turn on logging
set defines=^
-DKRYS_ENABLE_ASSERTS=1 ^
-DKRYS_ENABLE_LOGGING=1 ^
-DKRYS_ENABLE_DEBUG_BREAK=1

set entry-point=..\src\Platform\Windows\WindowsEntry.cpp

set include-dirs=^
/I "..\src\Core" ^
/I "..\src\Platform\Windows" ^
/I "..\src\Graphics" ^
/I "..\src\Graphics\OpenGL" ^
/I "..\src\ThirdParty\Glad\include\glad" ^
/I "..\src\ThirdParty\Glad\include" ^
/I "..\src\ThirdParty\glm"

set additional-translation-units=^
..\src\ThirdParty\Glad\src\glad.c ^
..\src\Graphics\OpenGL\OpenGLGraphicsContext.cpp ^
..\src\Platform\Windows\WindowsChrono.cpp ^
..\src\Platform\Windows\WindowsPerformance.cpp ^
..\src\Platform\Windows\WindowsLogger.cpp ^
..\src\Platform\Windows\WindowsInput.cpp ^
..\src\Platform\Windows\WindowsWindow.cpp ^
..\src\Core\Application.cpp

set linked-libs=^
user32.lib ^
Gdi32.lib ^
OpenGL32.lib ^
Winmm.lib

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