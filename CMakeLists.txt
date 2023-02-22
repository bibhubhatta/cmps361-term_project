cmake_minimum_required(VERSION 3.24)
project(assembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(assembler main.cpp vc1620.cpp vc1620.h)
