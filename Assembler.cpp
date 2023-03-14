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
    int location_of_instruction_to_be_generated = 0;

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