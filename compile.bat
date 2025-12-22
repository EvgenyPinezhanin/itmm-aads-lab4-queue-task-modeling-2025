@echo off
chcp 1251 > nul
echo ============================================
echo Компиляция проекта с поддержкой русского
echo ============================================
echo.

REM Проверяем компилятор
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo ОШИБКА: Компилятор g++ не найден!
    echo Установите MinGW или добавьте в PATH
    pause
    exit /b 1
)

REM Создаем папку bin если нет
if not exist "bin" mkdir bin

echo Компиляция примера использования...
REM Ключевые флаги для русской кодировки
g++ -std=c++17 -Iinclude -Isrc ^
    -fexec-charset=CP1251 ^
    -finput-charset=UTF-8 ^
    src/tcomputecentermodel.cpp ^
    samples/sample_modeling.cpp ^
    -o bin/sample_modeling.exe

if %errorlevel% equ 0 (
    echo [OK] Пример скомпилирован
) else (
    echo [ERROR] Ошибка компиляции примера
    pause
    exit /b 1
)

echo.
echo Компиляция тестов...
g++ -std=c++17 -Iinclude -Igtest ^
    -fexec-charset=CP1251 ^
    -finput-charset=UTF-8 ^
    src/tcomputecentermodel.cpp ^
    test/test_main.cpp ^
    test/test_tqueue.cpp ^
    test/test_tcomputecentermodel.cpp ^
    gtest/gtest-all.cc ^
    -o bin/run_tests.exe

if %errorlevel% equ 0 (
    echo [OK] Тесты скомпилированы
) else (
    echo [ERROR] Ошибка компиляции тестов
    pause
    exit /b 1
)

echo.
echo ============================================
echo КОМПИЛЯЦИЯ УСПЕШНО ЗАВЕРШЕНА!
echo ============================================
echo.
echo Созданы файлы:
echo   bin\sample_modeling.exe
echo   bin\run_tests.exe
echo.
echo Для запуска введите:
echo   .\bin\sample_modeling.exe
echo   .\bin\run_tests.exe
echo.
pause