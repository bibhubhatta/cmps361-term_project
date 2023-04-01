//
// Class to parse and provide information about instructions.  Note: you will be
// adding more functionality.
//
#pragma once

#include <map>
#include <string>

#include "InstructionDefinitions.h"

// The elements of an instruction.
class SymbolicInstruction
{
  public:
    explicit SymbolicInstruction(const std::string& line);
    ~SymbolicInstruction() = default;

    [[nodiscard]] bool contains_label() const;

    [[nodiscard]] InstructionType get_type() const;

    [[nodiscard]] std::string get_opcode() const;
    [[nodiscard]] std::string get_operand_1() const;
    [[nodiscard]] std::string get_operand_2() const;
    [[nodiscard]] std::string get_label() const;

    [[nodiscard]] std::string get_original_instruction() const;

  private:
    std::string _original_instruction;

    std::string _label;
    std::string _opcode;
    std::string _operand_1;
    std::string _operand_2;
    void        _check_operand_count() const;

    /**
     * @brief Checks if the operand type matches the operand type for
     * the instruction. If not, throws UnmatchedOperandTypeError.
     */
    void _check_operand_type() const;

    /**
     * @brief Checks if there are any extra elements in the instruction. If so,
     * throws ExtraStatementElementsError.
     * @param extra The extra elements in the instruction.
     */
    void _check_extra_elements(const std::string& extra) const;
};
