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

std::string Instruction::_get_upper_case(const std::string& str)
{
    std::string upper;
    for (auto c : str)
        upper += std::toupper(c);

    return upper;
}

InstructionType Instruction::get_type() const
{
    using enum InstructionType;

    if (_is_comment_or_empty(_original_instruction))
        return Comment;

    std::string upper_symbolic_opcode{_get_upper_case(_symbolic_opcode)};

    if (auto it{INSTRUCTION_TYPE.find(upper_symbolic_opcode)};
        it != INSTRUCTION_TYPE.end())
    {
        return it->second;
    }
    else
    {
        std::cerr << "Error: Invalid instruction: " << _original_instruction
                  << '\n';
        exit(1);
    }
}

int Instruction::get_location_of_next_instruction(
    const Instruction& current_instruction, int current_location)
{
    int next_location{current_location + 1};

    std::string opcode{current_instruction.get_symbolic_opcode()};

    if (opcode == "ORG")
    {
        next_location = current_instruction.get_symbolic_operand_1();
    }

    if (opcode == "DS")
    {
        next_location =
            current_location + current_instruction.get_symbolic_operand_1();
    }

    return next_location;
}

std::string Instruction::get_symbolic_opcode() const
{
    return _get_upper_case(_symbolic_opcode);
}

int Instruction::get_symbolic_operand_1() const
{
    return std::stoi(_symbolic_operand_1);
}

std::string Instruction::get_original_instruction() const
{
    return _original_instruction;
}

std::string Instruction::get_numeric_instruction() const
{
    std::string numeric_instruction{
        get_numeric_opcode() + get_numeric_operand1() + get_numeric_operand2()};

    return numeric_instruction;
}

std::string Instruction::get_numeric_opcode() const
{
    std::string numeric_opcode{std::to_string(_numeric_opcode)};
    numeric_opcode.insert(0, 2 - numeric_opcode.size(), '0');
    return numeric_opcode;
}

std::string Instruction::get_numeric_operand1() const
{
    std::string numeric_operand_1{std::to_string(_operand_1)};
    numeric_operand_1.insert(0, 5 - numeric_operand_1.size(), '0');
    return numeric_operand_1;
}

std::string Instruction::get_numeric_operand2() const
{
    std::string numeric_operand_2{std::to_string(_operand_2)};
    numeric_operand_2.insert(0, 5 - numeric_operand_2.size(), '0');
    return numeric_operand_2;
}

bool Instruction::is_numeric_operand() const { return _is_numeric_operand; }
