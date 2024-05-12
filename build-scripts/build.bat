@echo off
cls

IF NOT EXIST .\build mkdir .\build
pushd .\build

:: Compiler Flags
set compiler-flags=-c -nologo -Zi -Oi -FC -W4 -WX -MP -EHsc -std:c++latest

:: Custom Defines
set defines=^
-DKRYS_ENABLE_ASSERTS=1 ^
-DKRYS_ENABLE_LOGGING=1 ^
-DKRYS_ENABLE_DEBUG_BREAK=1 ^
-DKRYS_ENABLE_PERFORMANCE_CHECKS=1

:: Include Directories
set include-dirs=^
/I "..\src" ^
/I "..\src\Core" ^
/I "..\src\Platform" ^
/I "..\src\ThirdParty\Glad\include\glad" ^
/I "..\src\ThirdParty\Glad\include" ^
/I "..\src\ThirdParty\glm" ^
/I "..\src\ThirdParty\stb"

:: Source Files
set source-files=^
..\src\ThirdParty\Glad\src\gl.c ^
..\src\ThirdParty\Glad\src\wgl.c ^
..\src\Platform\OpenGL\GLTexture2D.cpp ^
..\src\Platform\OpenGL\GLRenderer2D.cpp ^
..\src\Platform\OpenGL\GLShader.cpp ^
..\src\Platform\OpenGL\GLVertexArray.cpp ^
..\src\Platform\OpenGL\GLBuffer.cpp ^
..\src\Platform\OpenGL\GLGraphicsContext.cpp ^
..\src\Platform\Windows\WindowsChrono.cpp ^
..\src\Platform\Windows\WindowsPerformance.cpp ^
..\src\Platform\Windows\WindowsLogger.cpp ^
..\src\Platform\Windows\WindowsInput.cpp ^
..\src\Platform\Windows\WindowsWindow.cpp ^
..\src\Core\Misc\Time.cpp ^
..\src\Core\Application.cpp

:: Disabled warnings:
set disabled-warnings=-wd4100 -wd4201

:: Compile each source file to an object file
cl %compiler-flags% %disable-warnings% %source-files% %defines% %include-dirs%

:: Link object files into a static library
lib -nologo -OUT:Krystal.lib *.obj

:: Check for compilation errors
set compile-error=%ERRORLEVEL%
if %compile-error% equ 0 (
    echo Compilation succeeded.
) else (
    echo Compilation failed.
)

popd

exit /b %compile-error%

:: Disabled warnings:
:: 4100 -> unreferenced formal parameter (we'll never need this).
:: 4201 -> nameless union/struct (we should re-enable this after replacing glm).