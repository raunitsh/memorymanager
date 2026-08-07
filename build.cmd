@echo off
setlocal

set TARGET=main.exe
set INCLUDES=-Iincludes
set SOURCES=main.cpp RMemoryManager.cpp RFixedPool.cpp
set CFLAGS=-std=c++17 -g -Wall

if "%~1"=="" goto build_and_run
if /i "%~1"=="clean" goto clean
if /i "%~1"=="build" goto build
if /i "%~1"=="run" goto run
if /i "%~1"=="all" goto build_and_run
if /i "%~1"=="buildandrun" goto build_and_run
if /i "%~1"=="help" goto usage
if /i "%~1"=="-h" goto usage
if /i "%~1"=="--help" goto usage

echo Unknown option: %~1
goto usage

:clean
echo Cleaning build artifacts...
if exist %TARGET% del /f /q %TARGET%
if exist *.obj del /f /q *.obj
if exist *.o del /f /q *.o
if exist *.pdb del /f /q *.pdb
if exist *.ilk del /f /q *.ilk
echo Clean completed.
goto end

:build
echo Building %TARGET% with clang++...
clang++ %CFLAGS% %INCLUDES% %SOURCES% -o %TARGET%
if %ERRORLEVEL% neq 0 (
    echo Build failed!
    exit /b %ERRORLEVEL%
)
echo Build succeeded.
goto end

:run
if not exist %TARGET% (
    echo %TARGET% not found. Building first...
    call :build
    if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
)
echo Running %TARGET%...
echo ----------------------------------------
.\%TARGET%
set EXIT_CODE=%ERRORLEVEL%
echo ----------------------------------------
echo Program exited with code %EXIT_CODE%
goto end

:build_and_run
call :clean
call :build
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
call :run
goto end

:usage
echo.
echo Usage: build.cmd [clean ^| build ^| run ^| all]
echo.
echo   clean  - Remove built executable and temporary files
echo   build  - Compile the project with clang++
echo   run    - Run the compiled executable (builds if missing)
echo   all    - Clean, build, and run (default when run without arguments)
echo.

:end
