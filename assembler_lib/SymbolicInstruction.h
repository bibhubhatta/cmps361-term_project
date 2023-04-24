/**
 * @file SymbolicInstruction.h
 * @brief SymbolicInstruction class declaration.
 * @details This class represents a symbolic instruction. It is used to
 * represent the symbolic instructions that are read from the source file.
 */

#pragma once

#include <map>
#include <string>

#include "InstructionDefinitions.h"

/**
 * @brief SymbolicInstruction class.
 * @details This class represents a symbolic instruction. It is used to
 * represent the symbolic instructions that are read from the source file.
 */
class SymbolicInstruction
{
  public:
    /**
     * @brief Constructs a symbolic instruction object.
     * @param a_Line The a_Line to construct the symbolic instruction from.
     * @throws InvalidOpcodeError
     * @throws MultiplyDefinedLabelError
     * @throws UnmatchedOperandCountError
     * @throws InvalidOperandTypeError
     * @throws ExtraStatementElementsError
     * @throws InsufficientMemoryError
     * @throws MissingEndStatementError
     * @throws StatementAfterEndError
     * @throws InvalidConstantSizeError
     * @throws SymbolicOpcodeInLabelError
     */
    explicit SymbolicInstruction(const std::string& a_Line);

    /**
     * @brief Default destructor.
     */
    ~SymbolicInstruction() = default;

    /**
     * @brief Checks if the instruction contains a label.
     * @return True if the instruction contains a label, false otherwise.
     */
    [[nodiscard]] bool ContainsLabel() const;

    /**
     * @brief Gets the type of the instruction.
     * @return The type of the instruction.
     */
    [[nodiscard]] InstructionType GetType() const;

    /**
     * @brief Gets the opcode of the instruction.
     * @return The opcode of the instruction in upper case.
     */
    [[nodiscard]] std::string GetOpcode() const;

    /**
     * @brief Gets the first operand of the instruction.
     * @return The first operand of the instruction.
     */
    [[nodiscard]] std::string GetOperand1() const;

    /**
     * @brief Gets the second operand of the instruction.
     * @return The second operand of the instruction.
     */
    [[nodiscard]] std::string GetOperand2() const;

    /**
     * @brief Gets the label of the instruction.
     * @return The label of the instruction.
     */
    [[nodiscard]] std::string GetLabel() const;

    /**
     * @brief Gets the original instruction.
     * @return The original instruction.
     */
    [[nodiscard]] std::string GetOriginalInstruction() const;

  private:
    std::string m_OriginalInstruction;

    std::string m_Label;
    std::string m_Opcode;
    std::string m_Operand1;
    std::string m_Operand2;

    /**
     * @brief Checks if the operand count matches the operand count for
     * the instruction. If not, throws UnmatchedOperandCountError.
     * @throws UnmatchedOperandCountError
     */
    void m_CheckOperandCount() const;

    /**
     * @brief Checks if the operand type matches the operand type for
     * the instruction. If not, throws UnmatchedOperandTypeError.
     * @throws UnmatchedOperandTypeError
     */
    void m_CheckOperandType() const;

    /**
     * @brief Checks if there are any extra elements in the instruction. If so,
     * throws ExtraStatementElementsError.
     * @param a_Extra The etra elements in the instruction.
     * @throws ExtraStatementElementsError
     */
    void m_CheckExtraElements(const std::string& a_Extra) const;

    /**
     * @brief Checks if the current instruction is "DC." Then, checks if the
     * constant size is valid. If not, throws InvalidConstantSizeError.
     * @throws InvalidConstantSizeError
     */
    void m_CheckConstantSize() const;

    /**
     * @brief Checks if the label is valid.
     * If the label is a symbolic instruction, throws
     * SymbolicOpcodeInLabelError.
     * @throws SymbolicOpcodeInLabelError
     */
    void m_CheckLabel() const;
};
