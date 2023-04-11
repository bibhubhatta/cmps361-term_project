/**
 * @file NumericInstruction.h
 * @brief NumericInstruction class declaration.
 */

#pragma once

#include "InstructionDefinitions.h"
#include "SymbolTable.h"
#include "SymbolicInstruction.h"

/**
 * @brief NumericInstruction class.
 * @details This class represents a numeric instruction. It is used to
 * represent the numeric instructions that are written to the memory.
 */
class NumericInstruction
{
  public:
    /**
     * @brief Constructs a numeric instruction object.
     * @param a_SymbolicInstruction The symbolic instruction to convert to a
     * numeric instruction.
     * @param a_SymbolTable The symbol table.
     */
    NumericInstruction(const SymbolicInstruction& a_SymbolicInstruction,
                       const SymbolTable&         a_SymbolTable);

    /**
     * @brief Destroys a numeric instruction object.
     */
    ~NumericInstruction() = default;

    /**
     * @brief Gets the opcode of the numeric instruction.
     * @return The opcode of the numeric instruction.
     */
    [[nodiscard]] NumericOpcode GetOpcode() const;

    /**
     * @brief Gets the first operand of the numeric instruction.
     * @return The first operand of the numeric instruction.
     */
    [[nodiscard]] int GetOperand1() const;

    /**
     * @brief Gets the second operand of the numeric instruction.
     * @return The second operand of the numeric instruction.
     */
    [[nodiscard]] int GetOperand2() const;

    /**
     * @brief Gets the string representation of the numeric instruction.
     * @return The string representation of the numeric instruction.
     */
    [[nodiscard]] std::string GetStringRepresentation() const;

    /**
     * @brief Gets the numeric representation of the numeric instruction.
     * @return The numeric representation of the numeric instruction.
     */
    [[nodiscard]] long long GetNumericRepresentation() const;

  private:
    NumericOpcode m_Opcode {-1};

    int m_Operand1 {0};
    int m_Operand2 {0};

    /**
     * @brief Checks if the numeric instruction has no numeric equivalent.
     * @return True if the numeric instruction has no numeric equivalent, false
     * otherwise.
     */
    [[nodiscard]] bool m_HasNoNumericEquivalent() const;
};