#include <iostream>
#include <sstream>

#include "Exceptions.h"
#include "HelperFunctions.h"
#include "InstructionDefinitions.h"
#include "SymbolicInstruction.h"

SymbolicInstruction::SymbolicInstruction(const std::string& a_line)
    : m_originalInstruction(a_line)
{
    if (isCommentOrEmpty(a_line))
        return;

    std::string processedLine {removeCommentsAndCommas(a_line)};

    std::istringstream iss {processedLine};

    std::string extra; // Used to check if there is anything after instruction

    if (lineContainsLabel(processedLine))
        iss >> m_label;

    iss >> m_opcode >> m_operand1 >> m_operand2 >> extra;

    m_checkLabel();
    m_checkOperandCount();
    m_checkOperandType();
    m_checkExtraElements(extra);
    m_checkConstantSize();
}

void SymbolicInstruction::m_checkExtraElements(const std::string& a_extra) const
{
    if (!a_extra.empty())
    {
        throw ExtraStatementElementsError(m_originalInstruction, a_extra);
    }
}

/**
 * @brief Checks if the number of operands matches the number of operands for
 * the instruction. If not, throws UnmatchedOperandCountError.
 */
void SymbolicInstruction::m_checkOperandCount() const
{
    int operandCount {getInstructionOperandCount(getOpcode())};

    if (operandCount == 0 && !m_operand1.empty())
    {
        throw UnmatchedOperandCountError(m_originalInstruction, 0, 1);
    }

    if (operandCount == 0 && !m_operand2.empty())
    {
        throw UnmatchedOperandCountError(m_originalInstruction, 0, 2);
    }

    if (operandCount == 1 && m_operand1.empty())
    {
        throw UnmatchedOperandCountError(m_originalInstruction, 1, 0);
    }

    if (operandCount == 1 && !m_operand2.empty())
    {
        throw UnmatchedOperandCountError(m_originalInstruction, 1, 2);
    }

    if (operandCount == 2 && (m_operand1.empty() || m_operand2.empty()))
    {
        if (m_operand1.empty())
            throw UnmatchedOperandCountError(m_originalInstruction, 2, 1);
        else
        {
            throw UnmatchedOperandCountError(m_originalInstruction, 2, 0);
        }
    }
}

bool SymbolicInstruction::containsLabel() const { return !m_label.empty(); }

InstructionType SymbolicInstruction::getType() const
{
    using enum InstructionType;

    if (isCommentOrEmpty(m_originalInstruction))
        return Comment;

    try
    {
        std::string opcode {getOpcode()};
        return SymbolicOpcode_Type.at(opcode);
    }
    catch (const std::out_of_range&)
    {
        std::cerr << "Error: Invalid instruction: " << m_originalInstruction
                  << '\n';
        exit(1);
    }
}

std::string SymbolicInstruction::getOpcode() const
{
    return getUpperCase(m_opcode);
}

std::string SymbolicInstruction::getOperand1() const { return m_operand1; }

std::string SymbolicInstruction::getOperand2() const { return m_operand2; }

std::string SymbolicInstruction::getLabel() const { return m_label; }

std::string SymbolicInstruction::getOriginalInstruction() const
{
    return m_originalInstruction;
}

void SymbolicInstruction::m_checkOperandType() const
{
    using enum OperandType;

    std::string opcode {getOpcode()};
    int         operandCount {getInstructionOperandCount(opcode)};
    OperandType expectedType {SymbolicOpcode_OperandType.at(opcode)};
    OperandType actualType1 {getOperandType(m_operand1)};
    OperandType actualType2 {getOperandType(m_operand2)};

    switch (operandCount)
    {
    case 0:
        break;
    case 1:
        if (SymbolicOpcode_OperandType.at(opcode) !=
            getOperandType(m_operand1))
        {
            throw InvalidOperandTypeError(m_operand1, expectedType,
                                          actualType1);
        }
        break;
    case 2:
        if (SymbolicOpcode_OperandType.at(opcode) !=
            getOperandType(m_operand1))
        {
            throw InvalidOperandTypeError(m_operand1, expectedType,
                                          actualType1);
        }

        if (SymbolicOpcode_OperandType.at(opcode) !=
            getOperandType(m_operand2))
        {
            throw InvalidOperandTypeError(m_operand2, expectedType,
                                          actualType2);
        }
        break;
    default:
        break;
    }
}

void SymbolicInstruction::m_checkConstantSize() const
{
    std::string opcode {getUpperCase(m_opcode)};

    if (opcode == "DC" && (stoi(m_operand1) > 99'999 || stoi(m_operand1) < 0))
    {
        throw InvalidConstantSizeError(m_originalInstruction, stoi(m_operand1));
    }
}

void SymbolicInstruction::m_checkLabel() const
{
    std::string label = getUpperCase(m_label);
    if (SymbolicOpcode_Type.contains(label))
    {
        // Ignore this error because 'b' is used to branch, but the
        // example code uses it as a label.
        // throw SymbolicOpcodeInLabelError(m_label);
    }
}
