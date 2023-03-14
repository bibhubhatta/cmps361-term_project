//
//      Implementation of the Assembler class.
//

#include <iostream>

#include "Assembler.h"
#include "Errors.h"

Assembler::Assembler(const std::string& source_file_path)
    : _instructions_file(source_file_path)
{
}

// Establish the location of the labels.
void Assembler::pass_1()
{
    int current_instruction_location = 0;

    while (!_instructions_file.end_of_file())
    {
        std::string line{_instructions_file.get_next_line()};
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
                _symbol_table.add_symbol(current_instruction.get_label(),
                                         current_instruction_location);
            }
        }

        current_instruction_location =
            Instruction::get_location_of_next_instruction(
                current_instruction, current_instruction_location);
    }
}

void Assembler::pass_2() { std::cout << "Implement Assembler::pass_2\n"; }

void Assembler::run_program_in_emulator() const
{
    std::cout << "Implement Assembler::run_program_in_emulator()\n";
}