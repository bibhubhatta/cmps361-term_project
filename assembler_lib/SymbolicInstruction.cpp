#include <iostream>
#include <sstream>

#include "Exceptions.h"
#include "HelperFunctions.h"
#include "InstructionDefinitions.h"
#include "SymbolicInstruction.h"

SymbolicInstruction::SymbolicInstruction(const std::string& a_Line)
    : m_OriginalInstruction(a_Line)
{
    if (IsCommentOrEmpty(a_Line))
        return;

    std::string ProcessedLine {RemoveCommentsAndCommas(a_Line)};

    std::istringstream iss {ProcessedLine};

    std::string extra; // Used to check if there is anything after instruction

    if (LineContainsLabel(ProcessedLine))
        iss >> m_Label;

    iss >> m_Opcode >> m_Operand1 >> m_Operand2 >> extra;

    m_CheckLabel();
    m_CheckOperandCount();
    m_CheckOperandType();
    m_CheckExtraElements(extra);
    m_CheckConstantSize();
}

void SymbolicInstruction::m_CheckExtraElements(const std::string& a_Extra) const
{
    if (!a_Extra.empty())
    {
        throw ExtraStatementElementsError(m_OriginalInstruction, a_Extra);
    }
}

/**
 * @brief Checks if the number of operands matches the number of operands for
 * the instruction. If not, throws UnmatchedOperandCountError.
 */
void SymbolicInstruction::m_CheckOperandCount() const
{
    int OperandCount {GetInstructionOperandCount(GetOpcode())};

    if (OperandCount == 0 && !m_Operand1.empty())
    {
        throw UnmatchedOperandCountError(m_OriginalInstruction, 0, 1);
    }

    if (OperandCount == 0 && !m_Operand2.empty())
    {
        throw UnmatchedOperandCountError(m_OriginalInstruction, 0, 2);
    }

    if (OperandCount == 1 && m_Operand1.empty())
    {
        throw UnmatchedOperandCountError(m_OriginalInstruction, 1, 0);
    }

    if (OperandCount == 1 && !m_Operand2.empty())
    {
        throw UnmatchedOperandCountError(m_OriginalInstruction, 1, 2);
    }

    if (OperandCount == 2 && (m_Operand1.empty() || m_Operand2.empty()))
    {
        if (m_Operand1.empty())
            throw UnmatchedOperandCountError(m_OriginalInstruction, 2, 1);
        else
        {
            throw UnmatchedOperandCountError(m_OriginalInstruction, 2, 0);
        }
    }
}

bool SymbolicInstruction::ContainsLabel() const { return !m_Label.empty(); }

InstructionType SymbolicInstruction::GetType() const
{
    using enum InstructionType;

    if (IsCommentOrEmpty(m_OriginalInstruction))
        return Comment;

    try
    {
        std::string opcode {GetOpcode()};
        return SymbolicOpcode_Type.at(opcode);
    }
    catch (const std::out_of_range&)
    {
        std::cerr << "Error: Invalid instruction: " << m_OriginalInstruction
                  << '\n';
        exit(1);
    }
}

std::string SymbolicInstruction::GetOpcode() const
{
    return GetUpperCase(m_Opcode);
}

std::string SymbolicInstruction::GetOperand1() const { return m_Operand1; }

std::string SymbolicInstruction::GetOperand2() const { return m_Operand2; }

std::string SymbolicInstruction::GetLabel() const { return m_Label; }

std::string SymbolicInstruction::GetOriginalInstruction() const
{
    return m_OriginalInstruction;
}

void SymbolicInstruction::m_CheckOperandType() const
{
    using enum OperandType;

    std::string opcode {GetOpcode()};
    int         OperandCount {GetInstructionOperandCount(opcode)};
    OperandType ExpectedType {SymbolicOpcode_OperandType.at(opcode)};
    OperandType ActualType1 {GetOperandType(m_Operand1)};
    OperandType ActualType2 {GetOperandType(m_Operand2)};

    switch (OperandCount)
    {
    case 0:
        break;
    case 1:
        if (SymbolicOpcode_OperandType.at(opcode) !=
            GetOperandType(m_Operand1))
        {
            throw InvalidOperandTypeError(m_Operand1, ExpectedType,
                                          ActualType1);
        }
        break;
    case 2:
        if (SymbolicOpcode_OperandType.at(opcode) !=
            GetOperandType(m_Operand1))
        {
            throw InvalidOperandTypeError(m_Operand1, ExpectedType,
                                          ActualType1);
        }

        if (SymbolicOpcode_OperandType.at(opcode) !=
            GetOperandType(m_Operand2))
        {
            throw InvalidOperandTypeError(m_Operand2, ExpectedType,
                                          ActualType2);
        }
        break;
    default:
        break;
    }
}

void SymbolicInstruction::m_CheckConstantSize() const
{
    std::string opcode {GetUpperCase(m_Opcode)};

    if (opcode == "DC" && (stoi(m_Operand1) > 99'999 || stoi(m_Operand1) < 0))
    {
        throw InvalidConstantSizeError(m_OriginalInstruction, stoi(m_Operand1));
    }
}

void SymbolicInstruction::m_CheckLabel() const
{
    std::string label = GetUpperCase(m_Label);
    if (SymbolicOpcode_Type.contains(label))
    {
        // Ignore this error because 'b' is used to branch, but the
        // example code uses it as a label.
        // throw SymbolicOpcodeInLabelError(m_Label);
    }
}
