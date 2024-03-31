@echo off
REM Launches and runs the exe in debug mode using Visual Studio.
call build.bat
devenv \build\win32_entry.exe /run \build\win32_entry.sln