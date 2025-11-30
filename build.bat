@echo off
Title Building Keyboard Tool...
echo ---------------------------------------------------
echo STEP 1: COMPILING C++ CODE TO EXE
echo ---------------------------------------------------
echo looking for g++ compiler...

:: check if g++ is installed
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] g++ compiler not found!
    echo Please install MinGW-w64 or add it to your PATH.
    pause
    exit /b
)


:: 1. Compile the Icon Resource
windres resource.rc -o resource.o

:: 2. Compile C++ and Link Resource
:: Compile command for MinGW (GCC)
:: FIXED: Added -DUNICODE -D_UNICODE to fix the char* conversion errors
g++ lazykey.cpp resource.o -o LazyKey.exe -lgdiplus -lgdi32 -luser32 -lkernel32 -mwindows -static-libgcc -static-libstdc++ -DUNICODE -D_UNICODE

if %errorlevel% equ 0 (
    echo.
    echo [SUCCESS] LazyKey.exe created successfully!
    echo You can now run 'LazyKey.exe' to test it.
    echo.
    echo Next Step: Open 'installer_config.iss' to make the Setup file.
) else (
    echo [FAIL] Compilation failed. Check the errors above.
)
pause