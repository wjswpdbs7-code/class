$ErrorActionPreference = "Stop"

Write-Host "[1/2] Restoring packages..."
dotnet restore

Write-Host "[2/2] Publishing single-file executable (win-x64)..."
dotnet publish -c Release -r win-x64 --self-contained true /p:PublishSingleFile=true /p:IncludeNativeLibrariesForSelfExtract=true /p:PublishTrimmed=false

Write-Host ""
Write-Host "Publish completed."
Write-Host "Output: .\bin\Release\net8.0-windows10.0.19041.0\win-x64\publish\"
