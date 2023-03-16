cmake_minimum_required(VERSION 3.24)
project(assembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(assembler
        Assembler.h Assembler.cpp
        SymbolTable.h SymbolTable.cpp
        HelperFunctions.h HelperFunctions.cpp
        SymbolicInstruction.h SymbolicInstruction.cpp
        NumericInstruction.cpp NumericInstruction.h
        FileAccess.h FileAccess.cpp
        Emulator.h Emulator.cpp
        Errors.h
        Assem.cpp
        )
