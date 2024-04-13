@echo off
REM Sets up the cmd shell environment so that `cl` and `devenv` is available to run.
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
set path=k:\build-scripts;%path%
cd /d K:
