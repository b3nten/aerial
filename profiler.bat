:: Windows Batch Script (build_tracy.bat)
@echo off
set BUILD_DIR=./.profiler
set EXECUTABLE=%BUILD_DIR%\Release\tracy-profiler.exe

if exist "%BUILD_DIR%" (
    if exist "%EXECUTABLE%" (
        echo Tracy build already exists, running executable...
        "%EXECUTABLE%"
    ) else (
        echo Build directory exists but executable not found. Rebuilding...
        goto :build
    )
) else (
    echo Build directory not found. Starting fresh build...
    goto :build
)
goto :eof

:build
:: Configure CMake
cmake -B ./.profiler -S Aerial/external/Tracy/profiler -DCMAKE_BUILD_TYPE=Release

:: Build the project
cmake --build ./.profiler --config Release --parallel

if exist "%EXECUTABLE%" (
    echo Build completed! Running executable...
    "%EXECUTABLE%"
) else (
    echo Build completed but executable not found.
)
pause