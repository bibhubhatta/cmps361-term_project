#include <iostream>
#include <sstream>

#include "HelperFunctions.h"
#include "InstructionDefinitions.h"
#include "SymbolicInstruction.h"

SymbolicInstruction::SymbolicInstruction(const std::string& line)
    : _original_instruction(line)
{
    if (is_comment_or_empty(line))
        return;

    std::string uncommented_instruction = get_uncommented_line(line);

    std::istringstream iss {uncommented_instruction};

    std::string extra; // Used to check if there is anything after instruction

    if (line_contains_label(uncommented_instruction))
        iss >> _label;

    iss >> _opcode >> _operand_1 >> _operand_2 >> extra;

    if (!extra.empty())
    {
        // TODO: Add error to error list, for now just print to console
        std::cout << "Error: Extra characters at end of instruction: "
                  << _original_instruction << std::endl;
        exit(1);
    }
}

bool SymbolicInstruction::contains_label() const { return !_label.empty(); }

InstructionType SymbolicInstruction::get_type() const
{
    using enum InstructionType;

    if (is_comment_or_empty(_original_instruction))
        return Comment;

    std::string upper_symbolic_opcode {get_upper_case(_opcode)};

    if (auto it {INSTRUCTION_TYPE.find(upper_symbolic_opcode)};
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

std::string SymbolicInstruction::get_opcode() const
{
    return get_upper_case(_opcode);
}

std::string SymbolicInstruction::get_operand_1() const { return _operand_1; }

std::string SymbolicInstruction::get_operand_2() const { return _operand_2; }

std::string SymbolicInstruction::get_label() const { return _label; }

std::string SymbolicInstruction::get_original_instruction() const
{
    return _original_instruction;
}
