#include <format>

#include "NumericInstruction.h"

NumericInstruction::NumericInstruction(
    const SymbolicInstruction& symbolic_instruction,
    const SymbolTable&         symbol_table)
{

    std::string symbolic_opcode = symbolic_instruction.get_opcode();

    _opcode = SymbolicOpcode_NumericOpcode.at(symbolic_opcode);

    if (_has_no_numeric_equivalent())
    {
        return;
    }

    if (_opcode == NumericOpcode::DC)
    {
        _operand2 = std::stoi(symbolic_instruction.get_operand_1());
        return;
    }

    switch (NumericOpcode_OperandCount.at(_opcode))
    {
    case 0:
        break;

    case 1:
        _operand1 =
            symbol_table.get_location(symbolic_instruction.get_operand_1());
        break;

    case 2:
        _operand1 =
            symbol_table.get_location(symbolic_instruction.get_operand_1());
        _operand2 =
            symbol_table.get_location(symbolic_instruction.get_operand_2());
        break;

    default:
        return;
    }
}

NumericOpcode NumericInstruction::get_opcode() const { return _opcode; }

int NumericInstruction::get_operand_1() const { return _operand1; }

int NumericInstruction::get_operand_2() const { return _operand2; }

std::string NumericInstruction::get_string_representation() const
{
    if (_has_no_numeric_equivalent())
    {
        return "";
    }

    std::string opcode {std::format("{:02}", static_cast<int>(_opcode))};
    std::string operand1 {std::format("{:05}", _operand1)};
    std::string operand2 {std::format("{:05}", _operand2)};

    return opcode + operand1 + operand2;
}

bool NumericInstruction::_has_no_numeric_equivalent() const
{
    return static_cast<int>(_opcode) <= -1;
}

long long NumericInstruction::get_numeric_representation() const
{
    if (_has_no_numeric_equivalent())
        return 0;

    return std::stoll(get_string_representation());
}
