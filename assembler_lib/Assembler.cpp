#include <iostream>

#include <fmt/core.h>

#include "Assembler.h"
#include "Errors.h"
#include "Exceptions.h"
#include "HelperFunctions.h"
#include "InstructionDefinitions.h"
#include "NumericInstruction.h"

Assembler::Assembler(const std::string& source_file_path)
    : _instructions_file(source_file_path)
{
}

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
            _check_memory_sufficiency(current_instruction_location);
            _check_if_end_is_valid();

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

    _check_memory_sufficiency(current_instruction_location);
    throw MissingEndStatementError();
}

void Assembler::_check_if_end_is_valid()
{
    std::string statements_after_end;
    while (!_instructions_file.end_of_file())
    {
        statements_after_end += _instructions_file.get_next_line();
    }

    trim(statements_after_end);

    if (!statements_after_end.empty())
    {
        throw StatementAfterEndError(statements_after_end);
    }
}

void Assembler::_check_memory_sufficiency(int last_instruction_location) const
{
    if (last_instruction_location >= Emulator::MEMORY_SIZE)
    {
        throw InsufficientMemoryError(last_instruction_location + 1,
                                      Emulator::MEMORY_SIZE);
    }
}

void Assembler::pass_2()
{
    _instructions_file.rewind();

    std::cout << fmt::format("{:<10}{:<15}{:<30}\n", // Set format
                             "Location", "Contents", "Original Statement");

    int current_instruction_location = 0;

    while (!_instructions_file.end_of_file())
    {
        std::string         line {_instructions_file.get_next_line()};
        SymbolicInstruction current_symbolic_instruction(line);

        switch (current_symbolic_instruction.get_type())
        {
        case InstructionType::End:
            std::cout << fmt::format(
                "{:<10}{:<15}{:<30}\n", // Set format
                "",                     // No location
                "",                     // No contents
                current_symbolic_instruction.get_original_instruction());
            return;
        case InstructionType::Comment:
            std::cout << fmt::format(
                "{:<10}{:<15}{:<30}\n", // Set format
                "",                     // No location
                "",                     // No contents
                current_symbolic_instruction.get_original_instruction());
            continue;

        default:
            NumericInstruction current_numeric_instruction(
                current_symbolic_instruction, _symbol_table);

            std::cout << fmt::format(
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