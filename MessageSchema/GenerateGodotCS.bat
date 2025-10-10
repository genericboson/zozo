cd MessageSchema
cd External
FOR %%i IN (*.fbs) DO flatc.exe --csharp -I ../Common -o ../../zozo-client/script %%i
cd ..
cd Common
FOR %%i IN (*.fbs) DO flatc.exe --csharp -o ../../zozo-client/script %%i