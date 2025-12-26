@echo off
"C:\UE_4.27Chaos_Source\Engine\Binaries\Win64\UE4Editor-Cmd.exe" "C:\Users\nicho\Documents\Unreal Projects\Starcel9\Starcel9.uproject" -run=Cook -TargetPlatform=WindowsNoEditor,WindowsClient,WindowsServer -Build -CookAll -ForceAllContentToCook -IncludeEngineContent -Stage -Archive

@echo off
REM =========================================================
REM  UE4.27 Chaos - Clean Build and Cook for All Windows Platforms
REM =========================================================

REM --- Set locale and Python settings to avoid locale errors ---
set LC_ALL=C
set LANG=C
set PYTHONUTF8=1
set PYTHONCOERCECLOCALE=0

REM --- Paths ---
set UE4_EDITOR="C:\UE_4.27Chaos_Source\Engine\Binaries\Win64\UE4Editor-Cmd.exe"
set PROJECT="C:\Users\nicho\Documents\Unreal Projects\Starcel9\Starcel9.uproject"

REM --- Clean intermediate data for a fresh cook ---
echo Cleaning Saved, Intermediate, and DerivedDataCache folders...
rmdir /s /q "%~dp0Saved"
rmdir /s /q "%~dp0Intermediate"
rmdir /s /q "%~dp0DerivedDataCache"

REM --- Cook each Windows platform ---
for %%P in (WindowsNoEditor WindowsClient WindowsServer) do (
    echo =============================================
    echo Cooking %%P platform...
    echo =============================================
    %UE4_EDITOR% %PROJECT% -run=Cook -TargetPlatform=%%P -Build -CookAll -unattended -CrashForUAT -utf8output -ForceAllContentToCook -IncludeEngineContent
)

echo =============================================
echo Cooking complete for all platforms.
echo =============================================
pause
