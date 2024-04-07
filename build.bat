@echo off
IF NOT EXIST .\build mkdir .\build
pushd .\build

:: TODO: check out Chandler Carruth - optimisation guy on LLVM

:: Compiler Flags:
:: |  FLAG  | DESCRIPTION
:: | D      | compiler level #defines
:: | Oi     | use intrinsics whenever possible
:: | Zi     | debug info
:: | W4     | compile-time warnings
:: | WX     | treat warnings as errors
:: | wd     | disable warnings for a specific warning code
:: | FC     | compile-time errors show full path to source code
:: | nologo | turn off compiler name banner
cl -nologo -Zi -Oi -FC -W4 -WX -DKRYSTAL_WIN32=1 ..\code\win32_handmade.cpp user32.lib Gdi32.lib

popd