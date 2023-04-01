cmake_minimum_required(VERSION 3.18)
project(assembler)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(fmt)
add_subdirectory(googletest)
add_subdirectory(assembler_lib)

target_link_libraries(assembler_lib fmt::fmt)

add_executable(assembler Assem.cpp)
target_link_libraries(assembler assembler_lib)

add_executable(tests tests/test_errors.cpp)
target_link_libraries(tests gtest gtest_main assembler_lib)
