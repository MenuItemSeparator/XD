@echo off
REM Bat file for building XD project in Debug configuration
REM This script must be run from the _cmake folder

cd /d "%~dp0"
echo Building XD project in Debug configuration...
cmake --build . --config Debug
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)
echo Build completed successfully!
pause
