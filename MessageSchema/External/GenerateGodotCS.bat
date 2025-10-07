cd MessageSchema
cd External
FOR %%i IN (*.fbs) DO flatc.exe --csharp -o ../../zozo-client/script %%i