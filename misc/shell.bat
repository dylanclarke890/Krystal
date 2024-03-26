REM Sets up the cmd shell environment so that `cl` is available to run.
@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
set path=k:\misc;%path%
cd /d K:
