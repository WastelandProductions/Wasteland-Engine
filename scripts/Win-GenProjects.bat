@echo off
pushd ..\

:: Generate project files for Visual Studio Community (2026 and 2022 fallback)
echo Generating Visual Studio Community solutions...
call vendor\bin\premake\premake5.exe vs2026
if %errorlevel% neq 0 (
    echo VS2026 action not found, trying VS2022...
    call vendor\bin\premake\premake5.exe vs2022
)

:: Generate project files for Visual Studio Code (Makefile format)
echo.
echo Generating VS Code Compilation Database...
call vendor\bin\premake\premake5.exe gmake2

popd
PAUSE