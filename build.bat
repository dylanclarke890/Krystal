REM Compiles and links the project files.
REM Output is placed in the `build` directory. 
@echo off
mkdir .\build
pushd .\build
cl -Zi ..\code\win32_entry.cpp user32.lib
popd