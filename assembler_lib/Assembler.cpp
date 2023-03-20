//
//      Implementation of the Assembler class.
//

#include <format>
#include <iostream>

#include "Assembler.h"
#include "Errors.h"
#include "HelperFunctions.h"
#include "InstructionDefinitions.h"
#include "NumericInstruction.h"

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
        std::string         line {_instructions_file.get_next_line()};
        SymbolicInstruction current_instruction(line);

        switch (current_instruction.get_type())
        {
        case InstructionType::End:
            return;
        case InstructionType::Comment:
            continue;

        default:
            if (current_instruction.contains_label())
            {
                _symbol_table.add_symbol(current_instruction.get_label(),
                                         current_instruction_location);
            }
            current_instruction_location = get_location_of_next_instruction(
                current_instruction, current_instruction_location);
        }
    }
}

void Assembler::pass_2()
{
    _instructions_file.rewind();

    std::cout << std::format("{:<10}{:<15}{:<30}\n", // Set format
                             "Location", "Contents", "Original Statement");

    int current_instruction_location = 0;

    while (!_instructions_file.end_of_file())
    {
        std::string         line {_instructions_file.get_next_line()};
        SymbolicInstruction current_symbolic_instruction(line);

        switch (current_symbolic_instruction.get_type())
        {
        case InstructionType::End:
            std::cout << std::format(
                "{:<10}{:<15}{:<30}\n", // Set format
                "",                     // No location
                "",                     // No contents
                current_symbolic_instruction.get_original_instruction());
            return;
        case InstructionType::Comment:
            std::cout << std::format(
                "{:<10}{:<15}{:<30}\n", // Set format
                "",                     // No location
                "",                     // No contents
                current_symbolic_instruction.get_original_instruction());
            continue;

        default:
            NumericInstruction current_numeric_instruction(
                current_symbolic_instruction, _symbol_table);

            std::cout << std::format(
                "{:<10}{:<15}{:<30}\n", // Set format
                current_instruction_location,
                current_numeric_instruction.get_string_representation(),
                current_symbolic_instruction.get_original_instruction());

            _emulator.insert(
                current_instruction_location,
                current_numeric_instruction.get_numeric_representation());
        }

        current_instruction_location = get_location_of_next_instruction(
            current_symbolic_instruction, current_instruction_location);
    }
}

void Assembler::run_program_in_emulator() { _emulator.run_program(); }