@echo off

for /r %~dp0 %%i in (DB_*.fbs) do "FlatMemGenerator.exe" "%%i"