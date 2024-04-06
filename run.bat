@echo off
REM Launches and runs the exe in debug mode using Visual Studio.
call build.bat
devenv \build\win32_handmade.exe /run \build\win32_handmade.sln