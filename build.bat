@echo off
mkdir .\build
pushd .\build

:: Compiler Flags:
::  -Zi - debug info
::  -FC - Full path of source code file with compile-time errors
:: -Wall - compile with optimisations turned on
:: -D compile-time defines

cl -Zi -FC -DKRYSTAL_WIN32=1 ..\code\win32_entry.cpp user32.lib Gdi32.lib

popd