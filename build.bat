@echo off
REM Compiles and links the project files.
REM Output is placed in the `build` directory. 
mkdir .\build
pushd .\build
cl -Zi -FC ..\code\win32_entry.cpp user32.lib Gdi32.lib
popd