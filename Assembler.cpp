//
//      Implementation of the Assembler class.
//

#include <iostream>

#include "Assembler.h"
#include "Errors.h"

Assembler::Assembler(int argc, char* argv[]) : _instructions_file(argc, argv) {}

Assembler::~Assembler() {}

// Establish the location of the labels.
void Assembler::pass_1()
{
    int location_of_instruction_to_be_generated = 0;

    std::string line;
    while (_instructions_file.GetNextLine(line))
    {
        switch (Instruction::InstructionType st =
                    _instruction.ParseInstruction(line))
        {
        case Instruction::InstructionType::ST_End:
            return;
        case Instruction::InstructionType::ST_Comment:
            continue;
        default:
            if (_instruction.isLabel())
            {
                _symbol_table.AddSymbol(
                    _instruction.GetLabel(),
                    location_of_instruction_to_be_generated);
            }
        }

        location_of_instruction_to_be_generated =
            _instruction.LocationNextInstruction(
                location_of_instruction_to_be_generated);
    }
}

void Assembler::pass_2() { std::cout << "Implement Assembler::pass_2\n"; }

void Assembler::run_program_in_emulator() const
{
    std::cout << "Implement Assembler::run_program_in_emulator()\n";
}