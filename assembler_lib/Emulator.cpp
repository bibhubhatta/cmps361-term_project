#include <iostream>

#include "Emulator.h"
#include "InstructionDefinitions.h"

void Emulator::insert(int a_Location, long long int a_Contents)
{
    m_Memory[a_Location] = a_Contents;
}

void Emulator::RunProgram()
{
    int CurrentInstructionLocation = 100;

    while (CurrentInstructionLocation < MEMORY_SIZE)
    {
        long long int CurrentInstruction =
            m_Memory[CurrentInstructionLocation];

        int operand2 {static_cast<int>(CurrentInstruction % 1'00000)};
        CurrentInstruction /= 1'00000;

        int operand1 {static_cast<int>(CurrentInstruction % 1'00000)};
        CurrentInstruction /= 1'00000;

        auto opcode = static_cast<NumericOpcode>(CurrentInstruction);

        using enum NumericOpcode;

        switch (opcode)
        {
        case DC:
        case DS:
            break;
        case ADD:
            m_Memory[operand1] += m_Memory[operand2];
            break;
        case SUB:
            m_Memory[operand1] -= m_Memory[operand2];
            break;
        case MULT:
            m_Memory[operand1] *= m_Memory[operand2];
            break;
        case DIV:
            m_Memory[operand1] /= m_Memory[operand2];
            break;
        case COPY:
            m_Memory[operand1] = m_Memory[operand2];
            break;
        case READ:
            std::cout << "? ";
            std::cin >> m_Memory[operand1];
            break;
        case WRITE:
            std::cout << m_Memory[operand1] << std::endl;
            break;
        case B:
            CurrentInstructionLocation = operand1;
            continue;
        case BM:
            if (m_Memory[operand2] < 0)
            {
                CurrentInstructionLocation = operand1;
                continue;
            }
            break;
        case BZ:
            if (m_Memory[operand2] == 0)
            {
                CurrentInstructionLocation = operand1;
                continue;
            }
            break;
        case BP:
            if (m_Memory[operand2] > 0)
            {
                CurrentInstructionLocation = operand1;
                continue;
            }
            break;
        case HALT:
            return;
        }

        CurrentInstructionLocation++;
    }
}