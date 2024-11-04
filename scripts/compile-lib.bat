@echo off
setlocal enabledelayedexpansion

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
/I "K:\include" ^
/I "K:\source\ThirdParty\Glad\include"

set krystal_third_party_source_files=^
K:\source\ThirdParty\Glad\src\gl.c ^
K:\source\ThirdParty\Glad\src\wgl.c

set krystal_platform_source_files=^
K:\source\Platform\Win32\Win32Application.cpp ^
K:\source\Platform\Win32\Win32Logger.cpp ^
K:\source\Platform\Win32\Win32OpenGLWindow.cpp ^
K:\source\Platform\Win32\Win32Window.cpp ^
K:\source\Platform\Win32\Win32WindowManager.cpp

set krystal_core_source_files=^
K:\source\Core\Application.cpp ^
K:\source\Core\ApplicationContext.cpp ^
K:\source\Core\StringId.cpp ^
K:\source\Core\Window.cpp ^
K:\source\Core\WindowManager.cpp ^
K:\source\Core\Events\EventDispatcher.cpp ^
K:\source\Core\Events\EventManager.cpp ^
K:\source\Core\Events\KeyboardEvent.cpp ^
K:\source\Core\Events\MouseButtonEvent.cpp ^
K:\source\Core\Events\MouseEvent.cpp ^
K:\source\Core\Events\ScrollWheelEvent.cpp

set krystal_source_files=^
%krystal_third_party_source_files% ^
%krystal_platform_source_files% ^
%krystal_core_source_files%

set krystal_disabled_warnings=-wd4100 -wd4201
set krystal_compiler_flags=-c -Foobj\ -nologo -Zi -Oi -FC -W4 -WX -MP -EHsc -std:c++latest -MTd
set krystal_linker_flags=-nologo -OUT:Krystal.lib

:: Collect files that need recompilation
set files_to_compile=

for %%f in (%krystal_source_files%) do (
    set "src_file=%%f"
    set "obj_file=obj\%%~nf.obj"
    if not exist !obj_file! (
        set files_to_compile=!files_to_compile! "%%f"
    ) else (
        for %%s in (%%f) do set "src_mod=%%~ts"
        for %%o in (!obj_file!) do set "obj_mod=%%~to"
        if "!src_mod!" gtr "!obj_mod!" (
            set files_to_compile=!files_to_compile! "%%f"
        )
    )
)

:: Compile all files that need recompilation in one batch
if defined files_to_compile (
    :: echo Compiling files: !files_to_compile!
    cl !krystal_compiler_flags! !krystal_disabled_warnings! !files_to_compile! !krystal_defines! !krystal_include_directories!
) else (
    echo No files need recompilation.
)

:: Link object files into a static library
lib !krystal_linker_flags! ./obj/*.obj

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
