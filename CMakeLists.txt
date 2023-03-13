cmake_minimum_required(VERSION 3.24)
project(assembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(assembler
        stdafx.h stdafx.cpp
        Assembler.h Assembler.cpp
        SymTab.h SymTab.cpp
        Instruction.h Instruction.cpp
        FileAccess.h FileAccess.cpp
        Errors.h
        Emulator.h
        Assem.cpp
        )
