#pragma once

#include "InstructionDefinitions.h"
#include "SymbolTable.h"
#include "SymbolicInstruction.h"

class NumericInstruction
{
  public:
    NumericInstruction(const SymbolicInstruction& symbolic_instruction,
                       const SymbolTable&         symbol_table);

    ~NumericInstruction() = default;

    [[nodiscard]] NumericOpcode get_opcode() const;

    [[nodiscard]] int get_operand_1() const;
    [[nodiscard]] int get_operand_2() const;

    [[nodiscard]] std::string get_string_representation() const;

  private:
    NumericOpcode _opcode {-1};

    int _operand1 {0};
    int _operand2 {0};

    [[nodiscard]] bool _has_no_numeric_equivalent() const;
};