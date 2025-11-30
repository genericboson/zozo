@echo off

rem -- If you want to enable ANSI code coloring,
rem -- Add VirtualTerminalLevel=1 as DWORD to HKEY_CURRENT_USER\Console

path out\build\x64-debug\bin

taskkill /f /im LOBBY_SERVER.exe
taskkill /f /im GAME_SERVER.exe