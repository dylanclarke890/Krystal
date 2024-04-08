@echo off
REM Launches and runs the exe in debug mode using Visual Studio.
call build.bat
devenv \build\WindowsEntry.exe /run \build\WindowsEntry.sln