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
     * @param a_symbolic_instruction The symbolic instruction to convert to a
     * numeric instruction.
     * @param a_symbol_table The symbol table.
     */
    NumericInstruction(const SymbolicInstruction& a_symbolic_instruction,
                       const SymbolTable&         a_symbol_table);

    /**
     * @brief Destroys a numeric instruction object.
     */
    ~NumericInstruction() = default;

    /**
     * @brief Gets the opcode of the numeric instruction.
     * @return The opcode of the numeric instruction.
     */
    [[nodiscard]] NumericOpcode get_opcode() const;

    /**
     * @brief Gets the first operand of the numeric instruction.
     * @return The first operand of the numeric instruction.
     */
    [[nodiscard]] int get_operand_1() const;

    /**
     * @brief Gets the second operand of the numeric instruction.
     * @return The second operand of the numeric instruction.
     */
    [[nodiscard]] int get_operand_2() const;

    /**
     * @brief Gets the string representation of the numeric instruction.
     * @return The string representation of the numeric instruction.
     */
    [[nodiscard]] std::string get_string_representation() const;

    /**
     * @brief Gets the numeric representation of the numeric instruction.
     * @return The numeric representation of the numeric instruction.
     */
    [[nodiscard]] long long get_numeric_representation() const;

  private:
    NumericOpcode _opcode {-1};

    int _operand1 {0};
    int _operand2 {0};

    /**
     * @brief Checks if the numeric instruction has no numeric equivalent.
     * @return True if the numeric instruction has no numeric equivalent, false
     * otherwise.
     */
    [[nodiscard]] bool _has_no_numeric_equivalent() const;
};