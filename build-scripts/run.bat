@echo off
cls

devenv B:\build\KrystalEditor.exe -run B:\build\KrystalEditor.sln

exit /b %ERRORLEVEL%