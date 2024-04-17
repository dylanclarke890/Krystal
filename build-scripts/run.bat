@echo off
REM Builds and runs the exe in debug mode using Visual Studio.
call build.bat
if %ERRORLEVEL% equ 0 devenv \build\WindowsEntry.exe /run \build\WindowsEntry.sln