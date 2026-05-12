@echo off

REM INI 파일 복사
xcopy /C /R /Y D:\projects\zozo\Backup\*.ini D:\projects\zozo\out\build\x64-debug\bin\

REM 심볼릭 링크 생성
mklink /J D:\projects\zozo\out\build\x64-debug\bin\StaticData D:\projects\zozo\StaticData

pause

