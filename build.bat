@echo off
mkdir .\build
pushd .\build

:: Compiler Flags:
::  -Zi - debug info
::  -FC - Full path of source code file with compile-time errors
:: -Wall - compile with optimisations turned on

cl -Zi -FC ..\code\win32_entry.cpp user32.lib Gdi32.lib

popd