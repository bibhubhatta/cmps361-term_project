#include <iostream>

#include "Emulator.h"
#include "InstructionDefinitions.h"

void Emulator::insert(int a_location, long long int a_contents)
{
    m_memory[a_location] = a_contents;
}

void Emulator::runProgram()
{
    int currentInstructionLocation = 100;

    while (currentInstructionLocation < MEMORY_SIZE)
    {
        long long int currentInstruction =
            m_memory[currentInstructionLocation];

        int operand2 {static_cast<int>(currentInstruction % 1'00000)};
        currentInstruction /= 1'00000;

        int operand1 {static_cast<int>(currentInstruction % 1'00000)};
        currentInstruction /= 1'00000;

        auto opcode = static_cast<NumericOpcode>(currentInstruction);

        using enum NumericOpcode;

        switch (opcode)
        {
        case DC:
        case DS:
            break;
        case ADD:
            m_memory[operand1] += m_memory[operand2];
            break;
        case SUB:
            m_memory[operand1] -= m_memory[operand2];
            break;
        case MULT:
            m_memory[operand1] *= m_memory[operand2];
            break;
        case DIV:
            m_memory[operand1] /= m_memory[operand2];
            break;
        case COPY:
            m_memory[operand1] = m_memory[operand2];
            break;
        case READ:
            std::cout << "? ";
            std::cin >> m_memory[operand1];
            break;
        case WRITE:
            std::cout << m_memory[operand1] << std::endl;
            break;
        case B:
            currentInstructionLocation = operand1;
            continue;
        case BM:
            if (m_memory[operand2] < 0)
            {
                currentInstructionLocation = operand1;
                continue;
            }
            break;
        case BZ:
            if (m_memory[operand2] == 0)
            {
                currentInstructionLocation = operand1;
                continue;
            }
            break;
        case BP:
            if (m_memory[operand2] > 0)
            {
                currentInstructionLocation = operand1;
                continue;
            }
            break;
        case HALT:
            return;
        }

        currentInstructionLocation++;
    }
}