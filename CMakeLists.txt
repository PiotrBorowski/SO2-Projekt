cmake_minimum_required(VERSION 3.13)
project(SO2_Projekt)

set(CMAKE_CXX_STANDARD 11)

SET(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
SET(GCC_COVERAGE_LINK_FLAGS    "-pthread")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

include_directories(.)
include_directories(SO2Threads)

add_executable(SO2_Projekt
        SO2Threads/main.cpp SO2Threads/Philosopher.cpp SO2Threads/Philosopher.h SO2Threads/Fork.cpp SO2Threads/Fork.h)
