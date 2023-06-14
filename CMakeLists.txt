cmake_minimum_required(VERSION 3.23)
project(LZW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "--static")


add_executable(LZW main.cpp Dictionary.hpp Dictionary.cpp BitsManipulator.hpp BitsManipulator.cpp LZW_Archiver.hpp LZW_Archiver.cpp File_service.hpp)
