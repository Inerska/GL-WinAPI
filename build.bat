@echo off

if not exist build mkdir build
pushd build
cmake .. -G "Visual Studio 16"
cmake --build .
cd Debug
.\WINGLAPI.exe
popd build