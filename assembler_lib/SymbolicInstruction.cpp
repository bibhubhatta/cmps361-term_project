#include <iostream>
#include <sstream>

#include "Exceptions.h"
#include "HelperFunctions.h"
#include "InstructionDefinitions.h"
#include "SymbolicInstruction.h"

SymbolicInstruction::SymbolicInstruction(const std::string& line)
    : _original_instruction(line)
{
    if (is_comment_or_empty(line))
        return;

    std::string processed_line {remove_comments_and_commas(line)};

    std::istringstream iss {processed_line};

    std::string extra; // Used to check if there is anything after instruction

    if (line_contains_label(processed_line))
        iss >> _label;

    iss >> _opcode >> _operand_1 >> _operand_2 >> extra;

    _check_operand_count();
    _check_operand_type();

    if (!extra.empty())
    {
        // TODO: Add error to error list, for now just print to console
        std::cout << "Error: Extra characters at end of instruction: "
                  << _original_instruction << std::endl;
        exit(1);
    }
}

/**
 * @brief Checks if the number of operands matches the number of operands for
 * the instruction. If not, throws UnmatchedOperandCountError.
 */
void SymbolicInstruction::_check_operand_count() const
{
    int operand_count {get_instruction_operand_count(_opcode)};

    if (operand_count == 1 && _operand_1.empty())
    {
        throw UnmatchedOperandCountError(_original_instruction, 1, 0);
    }

    if (operand_count == 2 && (_operand_1.empty() || _operand_2.empty()))
    {
        if (_operand_1.empty())
            throw UnmatchedOperandCountError(_original_instruction, 2, 1);
        else
        {
            throw UnmatchedOperandCountError(_original_instruction, 2, 0);
        }
    }
}

bool SymbolicInstruction::contains_label() const { return !_label.empty(); }

InstructionType SymbolicInstruction::get_type() const
{
    using enum InstructionType;

    if (is_comment_or_empty(_original_instruction))
        return Comment;

    try
    {
        std::string opcode {get_opcode()};
        return SymbolicOpcode_Type.at(opcode);
    }
    catch (const std::out_of_range&)
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

void SymbolicInstruction::_check_operand_type() const
{
    using enum OperandType;

    std::string opcode {get_opcode()};
    int         operand_count {get_instruction_operand_count(opcode)};
    OperandType expected_type {SymbolicOpcode_OperandType.at(opcode)};
    OperandType actual_type_1 {get_operand_type(_operand_1)};
    OperandType actual_type_2 {get_operand_type(_operand_2)};

    switch (operand_count)
    {
    case 0:
        break;
    case 1:
        if (SymbolicOpcode_OperandType.at(opcode) !=
            get_operand_type(_operand_1))
        {
            throw InvalidOperandTypeError(_operand_1, expected_type,
                                          actual_type_1);
        }
        break;
    case 2:
        if (SymbolicOpcode_OperandType.at(opcode) !=
            get_operand_type(_operand_1))
        {
            throw InvalidOperandTypeError(_operand_1, expected_type,
                                          actual_type_1);
        }

        if (SymbolicOpcode_OperandType.at(opcode) !=
            get_operand_type(_operand_2))
        {
            throw InvalidOperandTypeError(_operand_2, expected_type,
                                          actual_type_2);
        }
        break;
    default:
        break;
    }
}
