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
     * @param line The line to construct the symbolic instruction from.
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
    explicit SymbolicInstruction(const std::string& line);

    /**
     * @brief Default destructor.
     */
    ~SymbolicInstruction() = default;

    /**
     * @brief Checks if the instruction contains a label.
     * @return True if the instruction contains a label, false otherwise.
     */
    [[nodiscard]] bool contains_label() const;

    /**
     * @brief Gets the type of the instruction.
     * @return The type of the instruction.
     */
    [[nodiscard]] InstructionType get_type() const;

    /**
     * @brief Gets the opcode of the instruction.
     * @return The opcode of the instruction in upper case.
     */
    [[nodiscard]] std::string get_opcode() const;

    /**
     * @brief Gets the first operand of the instruction.
     * @return The first operand of the instruction.
     */
    [[nodiscard]] std::string get_operand_1() const;

    /**
     * @brief Gets the second operand of the instruction.
     * @return The second operand of the instruction.
     */
    [[nodiscard]] std::string get_operand_2() const;

    /**
     * @brief Gets the label of the instruction.
     * @return The label of the instruction.
     */
    [[nodiscard]] std::string get_label() const;

    /**
     * @brief Gets the original instruction.
     * @return The original instruction.
     */
    [[nodiscard]] std::string get_original_instruction() const;

  private:
    std::string _original_instruction;

    std::string _label;
    std::string _opcode;
    std::string _operand_1;
    std::string _operand_2;

    /**
     * @brief Checks if the operand count matches the operand count for
     * the instruction. If not, throws UnmatchedOperandCountError.
     * @throws UnmatchedOperandCountError
     */
    void _check_operand_count() const;

    /**
     * @brief Checks if the operand type matches the operand type for
     * the instruction. If not, throws UnmatchedOperandTypeError.
     * @throws UnmatchedOperandTypeError
     */
    void _check_operand_type() const;

    /**
     * @brief Checks if there are any extra elements in the instruction. If so,
     * throws ExtraStatementElementsError.
     * @param extra The extra elements in the instruction.
     * @throws ExtraStatementElementsError
     */
    void _check_extra_elements(const std::string& extra) const;

    /**
     * @brief Checks if the current instruction is "DC." Then, checks if the
     * constant size is valid. If not, throws InvalidConstantSizeError.
     * @throws InvalidConstantSizeError
     */
    void _check_constant_size() const;

    /**
     * @brief Checks if the label is valid.
     * If the label is a symbolic instruction, throws
     * SymbolicOpcodeInLabelError.
     * @throws SymbolicOpcodeInLabelError
     */
    void _check_label() const;
};
