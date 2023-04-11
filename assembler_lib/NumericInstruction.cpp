#include <format>

#include "NumericInstruction.h"

NumericInstruction::NumericInstruction(
    const SymbolicInstruction& a_SymbolicInstruction,
    const SymbolTable&         a_SymbolTable)
{

    std::string SymbolicOpcode = a_SymbolicInstruction.GetOpcode();

    m_Opcode = SymbolicOpcode_NumericOpcode.at(SymbolicOpcode);

    if (m_HasNoNumericEquivalent())
    {
        return;
    }

    if (m_Opcode == NumericOpcode::DC)
    {
        m_Operand2 = std::stoi(a_SymbolicInstruction.GetOperand1());
        return;
    }

    switch (NumericOpcode_OperandCount.at(m_Opcode))
    {
    case 0:
        break;

    case 1:
        m_Operand1 =
            a_SymbolTable.GetLocation(a_SymbolicInstruction.GetOperand1());
        break;

    case 2:
        m_Operand1 =
            a_SymbolTable.GetLocation(a_SymbolicInstruction.GetOperand1());
        m_Operand2 =
            a_SymbolTable.GetLocation(a_SymbolicInstruction.GetOperand2());
        break;

    default:
        return;
    }
}

NumericOpcode NumericInstruction::GetOpcode() const { return m_Opcode; }

int NumericInstruction::GetOperand1() const { return m_Operand1; }

int NumericInstruction::GetOperand2() const { return m_Operand2; }

std::string NumericInstruction::GetStringRepresentation() const
{
    if (m_HasNoNumericEquivalent())
    {
        return "";
    }

    std::string opcode {std::format("{:02}", static_cast<int>(m_Opcode))};
    std::string operand1 {std::format("{:05}", m_Operand1)};
    std::string operand2 {std::format("{:05}", m_Operand2)};

    return opcode + operand1 + operand2;
}

bool NumericInstruction::m_HasNoNumericEquivalent() const
{
    return static_cast<int>(m_Opcode) <= -1;
}

long long NumericInstruction::GetNumericRepresentation() const
{
    if (m_HasNoNumericEquivalent())
        return 0;

    return std::stoll(GetStringRepresentation());
}
