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
        Instruction current_instruction(line);

        switch (current_instruction.get_type())
        {
        case InstructionType::End:
            return;
        case InstructionType::Comment:
            continue;
        default:
            if (current_instruction.is_label())
            {
                _symbol_table.add_symbol(
                    current_instruction.get_label(),
                    location_of_instruction_to_be_generated);
            }
        }

        location_of_instruction_to_be_generated =
            current_instruction.get_location_of_next_instruction(
                location_of_instruction_to_be_generated);
    }
}

void Assembler::pass_2() { std::cout << "Implement Assembler::pass_2\n"; }

void Assembler::run_program_in_emulator() const
{
    std::cout << "Implement Assembler::run_program_in_emulator()\n";
}