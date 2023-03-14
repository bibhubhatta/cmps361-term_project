//
// Class to parse and provide information about instructions.  Note: you will be
// adding more functionality.
//
#pragma once

#include <string>

// Codes to indicate the type of instruction we are processing
enum class InstructionType
{
    MachineLanguage, // A machine language instruction.
    AssemblerInstr,  // Assembler Language instruction.
    Comment,         // Comment or blank line
    End              // end instruction.
};

// The elements of an instruction.
class Instruction
{
  public:
    explicit Instruction(std::string_view line);
    ~Instruction() = default;

    [[nodiscard]] int
    get_location_of_next_instruction(int current_location) const;

    [[nodiscard]] inline bool is_label() const { return !_label.empty(); };
    [[nodiscard]] inline std::string get_label() const { return _label; };

    [[nodiscard]] InstructionType get_type() const;

  private:
    std::string _original_instruction;
    std::string _uncommented_instruction;

    // The elements of an instruction
    std::string _label;
    std::string _symbolic_opcode;
    std::string _symbolic_operand_1;
    std::string _symbolic_operand_2;

    // Derived values.
    int _numeric_opcode{}; // machine language equivalent numeric opcode

    InstructionType _instruction_type;

    bool _is_numeric_operand{}; // == true if the operand is numeric
    int _operand_1{}; // The value of the first operand if it is numeric
    int _operand_2{}; // The value of the second operand if it is numeric

    // Private helper functions

    static bool _is_comment_or_empty(std::string_view line);
    static bool _contains_label(std::string_view uncommented_instruction);

    [[nodiscard]] static std::string
    _get_uncommented_instruction(const std::string& instruction);

    void _parse();

    static std::string _get_lower_case(const std::string& str);
};
