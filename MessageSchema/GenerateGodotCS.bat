cd MessageSchema
FOR %%i IN (*.fbs) DO flatc.exe --csharp -o ../zozo-client/script %%i