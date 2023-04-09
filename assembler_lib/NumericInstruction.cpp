#include <format>

#include "NumericInstruction.h"

NumericInstruction::NumericInstruction(
    const SymbolicInstruction& a_symbolicInstruction,
    const SymbolTable&         a_symbolTable)
{

    std::string symbolicOpcode = a_symbolicInstruction.getOpcode();

    m_opcode = SymbolicOpcode_NumericOpcode.at(symbolicOpcode);

    if (m_hasNoNumericEquivalent())
    {
        return;
    }

    if (m_opcode == NumericOpcode::DC)
    {
        m_operand2 = std::stoi(a_symbolicInstruction.getOperand1());
        return;
    }

    switch (NumericOpcode_OperandCount.at(m_opcode))
    {
    case 0:
        break;

    case 1:
        m_operand1 =
            a_symbolTable.getLocation(a_symbolicInstruction.getOperand1());
        break;

    case 2:
        m_operand1 =
            a_symbolTable.getLocation(a_symbolicInstruction.getOperand1());
        m_operand2 =
            a_symbolTable.getLocation(a_symbolicInstruction.getOperand2());
        break;

    default:
        return;
    }
}

NumericOpcode NumericInstruction::getOpcode() const { return m_opcode; }

int NumericInstruction::getOperand1() const { return m_operand1; }

int NumericInstruction::getOperand2() const { return m_operand2; }

std::string NumericInstruction::getStringRepresentation() const
{
    if (m_hasNoNumericEquivalent())
    {
        return "";
    }

    std::string opcode {std::format("{:02}", static_cast<int>(m_opcode))};
    std::string operand1 {std::format("{:05}", m_operand1)};
    std::string operand2 {std::format("{:05}", m_operand2)};

    return opcode + operand1 + operand2;
}

bool NumericInstruction::m_hasNoNumericEquivalent() const
{
    return static_cast<int>(m_opcode) <= -1;
}

long long NumericInstruction::getNumericRepresentation() const
{
    if (m_hasNoNumericEquivalent())
        return 0;

    return std::stoll(getStringRepresentation());
}
