@echo off
cls

pushd K:\data

devenv /debugexe "B:\build\KrystalEditor.exe"

popd

exit /b %ERRORLEVEL%