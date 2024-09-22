@echo off

set krystal_start_time=%time%
echo Compiling 'Krystal'.
echo Started at %krystal_start_time%.

IF NOT EXIST .\build mkdir .\build
pushd .\build

IF NOT EXIST .\obj mkdir .\obj

set krystal_defines=^
-DKRYS_ENABLE_ASSERTS=1 ^
-DKRYS_ENABLE_LOGGING=1 ^
-DKRYS_ENABLE_DEBUG_BREAK=1 ^
-DKRYS_ENABLE_PERFORMANCE_CHECKS=1 ^
-D_ITERATOR_DEBUG_LEVEL=2

set krystal_include_directories=^
/I "K:\src" ^
/I "K:\src\Core" ^
/I "K:\src\Platform" ^
/I "K:\src\ThirdParty\assimp\include" ^
/I "K:\src\ThirdParty\Glad\include" ^
/I "K:\src\ThirdParty\glm" ^
/I "K:\src\ThirdParty\stb"

set krystal_source_files=^
K:\src\ThirdParty\Glad\src\gl.c ^
K:\src\ThirdParty\Glad\src\wgl.c ^
K:\src\Platform\OpenGL\GLModel.cpp ^
K:\src\Platform\OpenGL\Textures\GLTexture2D.cpp ^
K:\src\Platform\OpenGL\Textures\GLTextureCubemap.cpp ^
K:\src\Platform\OpenGL\GLShader.cpp ^
K:\src\Platform\OpenGL\GLVertexArray.cpp ^
K:\src\Platform\OpenGL\GLBuffer.cpp ^
K:\src\Platform\OpenGL\GLGraphicsContext.cpp ^
K:\src\Platform\Windows\WindowsChrono.cpp ^
K:\src\Platform\Windows\WindowsPerformance.cpp ^
K:\src\Platform\Windows\WindowsLogger.cpp ^
K:\src\Platform\Windows\WindowsInput.cpp ^
K:\src\Platform\Windows\WindowsWindow.cpp ^
K:\src\Core\IO\IO.cpp ^
K:\src\Core\Graphics\Renderer\Renderer.cpp ^
K:\src\Core\Misc\Time.cpp ^
K:\src\Core\Application.cpp

set krystal_disabled_warnings=-wd4100 -wd4201

set krystal_compiler_flags=-c -Foobj\ -nologo -Zi -Oi -FC -W4 -WX -MP -EHsc -std:c++latest -MTd

set krystal_linker_flags=-nologo -OUT:Krystal.lib

:: Compile files to object files
cl ^
%krystal_compiler_flags% ^
%krystal_disabled_warnings% ^
%krystal_source_files% ^
%krystal_defines% ^
%krystal_include_directories%

:: Link object files into a static library
lib %krystal_linker_flags% ./obj/*.obj

popd

set krystal_compilation_error=%ERRORLEVEL%
if %krystal_compilation_error% equ 0 (
  echo Compilation of 'Krystal' succeeded.
) else (
  echo Compilation of 'Krystal' failed.
)

set krystal_end_time=%time%
set /A "krystal_start_in_seconds=((%krystal_start_time:~0,2%*3600)+(%krystal_start_time:~3,2%*60)+%krystal_start_time:~6,2%)"
set /A "krystal_end_in_seconds=((%krystal_end_time:~0,2%*3600)+(%krystal_end_time:~3,2%*60)+%krystal_end_time:~6,2%)"
set /A "krystal_compilation_duration_in_seconds=%krystal_end_in_seconds%-%krystal_start_in_seconds%"
echo Finished at %krystal_end_time% (%krystal_compilation_duration_in_seconds%s).

exit /b %krystal_compilation_error%
