@echo off
setlocal

echo [1/2] Restoring packages...
dotnet restore
if errorlevel 1 goto :error

echo [2/2] Publishing single-file executable (win-x64)...
dotnet publish -c Release -r win-x64 --self-contained true /p:PublishSingleFile=true /p:IncludeNativeLibrariesForSelfExtract=true /p:PublishTrimmed=false
if errorlevel 1 goto :error

echo.
echo Publish completed.
echo Output: .\bin\Release\net8.0-windows10.0.19041.0\win-x64\publish\
goto :end

:error
echo Publish failed.
exit /b 1

:end
endlocal
