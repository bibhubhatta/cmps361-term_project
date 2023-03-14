#include <iostream>
#include <sstream>

#include "Instruction.h"

Instruction::Instruction(std::string_view line) : _original_instruction(line)
{
    if (_is_comment_or_empty(line))
    {
        _instruction_type = InstructionType::Comment;
        return;
    }

    _uncommented_instruction =
        _get_uncommented_instruction(_original_instruction);

    _parse();
}

bool Instruction::_is_comment_or_empty(std::string_view line)
{
    if (line.empty()) // Empty line
        return true;

    if (line[0] == ';') // Comment
        return true;

    return false;
}

bool Instruction::_contains_label(std::string_view uncommented_instruction)
{
    return uncommented_instruction[0] != ' ' &&
           uncommented_instruction[0] != '\t';
}

std::string
Instruction::_get_uncommented_instruction(const std::string& instruction)
{
    if (auto comment_position{instruction.find(';')};
        comment_position != std::string::npos)
    {
        return instruction.substr(0, comment_position);
    }
    return instruction;
}

void Instruction::_parse()
{
    std::istringstream iss{_uncommented_instruction};

    std::string
        extra; // Used to check if there is anything after the instruction

    if (_contains_label(_uncommented_instruction))
        iss >> _label;

    iss >> _symbolic_opcode >> _symbolic_operand_1 >> _symbolic_operand_2 >>
        extra;

    if (!extra.empty())
    {
        // TODO: Add error to error list, for now just print to console
        std::cout << "Error: Extra characters at end of instruction: "
                  << _original_instruction << std::endl;
        exit(1);
    }
}

std::string Instruction::_get_lower_case(const std::string& str)
{
    std::string lower;
    for (auto c : str)
        lower += std::tolower(c);

    return lower;
}

InstructionType Instruction::get_type() const
{
    using enum InstructionType;

    if (_is_comment_or_empty(_original_instruction))
        return Comment;

    std::string lower_symbolic_opcode{_get_lower_case(lower_symbolic_opcode)};

    if (lower_symbolic_opcode == "halt")
        return End;

    return AssemblerInstr;
}

int Instruction::get_location_of_next_instruction(int current_location) const
{
    std::cout << "Implement Instruction::get_location_of_next_instruction\n";
    return 0;
}
