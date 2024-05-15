@echo off
cd WINDOWS_GUI
rd /s /q build
mkdir build
cd build
set my_path=%CD%
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
call "C:\Qt\6.8.0\msvc2019_64\bin\qtenv2.bat"
cd /D %my_path%
cd Release
windeployqt.exe --quick .
call WINDOWS_GUI.exe

REM mklink .\..\..\run_gui.lnk .\WINDOWS_GUI.exe

