#include <iostream>

#include "Emulator.h"
#include "InstructionDefinitions.h"

void Emulator::insert(int a_location, long long int a_contents)
{
    _memory[a_location] = a_contents;
}

void Emulator::run_program()
{
    int current_instruction_location = 100;

    while (current_instruction_location < MEMORY_SIZE)
    {
        long long int current_instruction =
            _memory[current_instruction_location];

        int operand2 {static_cast<int>(current_instruction % 1'00000)};
        current_instruction /= 1'00000;

        int operand1 {static_cast<int>(current_instruction % 1'00000)};
        current_instruction /= 1'00000;

        auto opcode = static_cast<NumericOpcode>(current_instruction);

        using enum NumericOpcode;

        switch (opcode)
        {
        case DC:
        case DS:
            break;
        case ADD:
            _memory[operand1] += _memory[operand2];
            break;
        case SUB:
            _memory[operand1] -= _memory[operand2];
            break;
        case MULT:
            _memory[operand1] *= _memory[operand2];
            break;
        case DIV:
            _memory[operand1] /= _memory[operand2];
            break;
        case COPY:
            _memory[operand1] = _memory[operand2];
            break;
        case READ:
            std::cout << "? ";
            std::cin >> _memory[operand1];
            break;
        case WRITE:
            std::cout << _memory[operand1] << std::endl;
            break;
        case B:
            current_instruction_location = operand1;
            continue;
        case BM:
            if (_memory[operand2] < 0)
            {
                current_instruction_location = operand1;
                continue;
            }
            break;
        case BZ:
            if (_memory[operand2] == 0)
            {
                current_instruction_location = operand1;
                continue;
            }
            break;
        case BP:
            if (_memory[operand2] > 0)
            {
                current_instruction_location = operand1;
                continue;
            }
            break;
        case HALT:
            return;
        }

        current_instruction_location++;
    }
}