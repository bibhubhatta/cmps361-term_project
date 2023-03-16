cmake_minimum_required(VERSION 3.24)
project(assembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(assembler
        Assembler.h Assembler.cpp
        SymTab.h SymTab.cpp
        HelperFunctions.h HelperFunctions.cpp
        SymbolicInstruction.h SymbolicInstruction.cpp
        FileAccess.h FileAccess.cpp
        Errors.h
        Emulator.h
        Assem.cpp
        )
