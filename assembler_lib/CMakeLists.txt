cmake_minimum_required(VERSION 3.24)
project(assembler_lib)

set(CMAKE_CXX_STANDARD 20)

add_library(assembler_lib
        Assembler.h Assembler.cpp
        SymbolTable.h SymbolTable.cpp
        HelperFunctions.h HelperFunctions.cpp
        SymbolicInstruction.h SymbolicInstruction.cpp
        NumericInstruction.cpp NumericInstruction.h
        FileAccess.h FileAccess.cpp
        Emulator.h Emulator.cpp
        Errors.h
        )

