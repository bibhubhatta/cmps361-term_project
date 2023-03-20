cmake_minimum_required(VERSION 3.24)
project(assembler)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(assembler_lib)
target_include_directories(assembler_lib PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}")

add_executable(assembler
        Assem.cpp)

target_link_libraries(assembler assembler_lib)
