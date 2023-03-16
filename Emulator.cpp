#include <iostream>

#include "Emulator.h"
#include "InstructionDefinitions.h"

void Emulator::insert(int location, long long int contents)
{
    _memory[location] = contents;
}

void Emulator::run_program()
{
    std::cout << "Implement the Emulator::run_program() function";
}
