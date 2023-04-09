/**
 * @file Assembler.h
 * @brief The assembler class.
 * @details This class is the container for all the components that make up the
 * assembler. It is responsible for assembling the program.
 */

#pragma once

#include "Emulator.h"
#include "FileAccess.h"
#include "SymbolTable.h"
#include "SymbolicInstruction.h"

/**
 * @brief The assembler class.
 * @details This class is the container for all the components that make up the
 * assembler. It is responsible for assembling the program.
 */
class Assembler
{
  public:
    /**
     * @brief Constructs an assembler object.
     * @param a_source_file_path The path to the source file.
     */
    explicit Assembler(const std::string& a_source_file_path);
    ~Assembler() = default;

    /**
     * @brief Establishes the location of the symbols.
     * @details This is the first pass of the assembler. It establishes the
     * location of the symbols. It also checks if the memory is sufficient to
     * hold the program.
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
    void pass_1();

    /**
     * @brief Translates the symbolic instructions to numeric instructions.
     * @details This is the second pass of the assembler. It translates the
     * symbolic instructions to numeric instructions, and writes them to the
     * memory.
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
     * @throws UndefinedLabelError
     */
    void pass_2();

    /**
     * @brief Displays the symbol table.
     */
    void display_symbol_table() const { _symbol_table.display_symbol_table(); }

    /**
     * @brief Runs the program in the emulator.
     */
    void run_program_in_emulator();

  private:
    FileAccess  _instructions_file;
    SymbolTable _symbol_table;
    Emulator    _emulator;

    /**
     * @brief Checks if the memory is sufficient to hold the program.
     * @param a_last_instruction_location The location of the last instruction.
     */
    void _check_memory_sufficiency(int a_last_instruction_location) const;

    /**
     * @brief Checks if the end statement is valid and throws error if not.
     * @details The end statement is valid if it is the last statement in the
     * program and there are no statements after it. If the end statement is
     * invalid, a StatementAfterEndError is thrown.
     */
    void _check_if_end_is_valid();

    /**
     * @brief Records the error message in the error log.
     * @param a_e The exception that was thrown.
     */
    void _record_error(const std::exception& a_e,
                       const std::string&    a_where) const;

    /**
     * @brief Checks if the label is too long.
     * @details If the label is too long, a LabelTooLongError is thrown.
     * @param a_instruction The a_instruction that contains the label.
     * @throws LabelTooLongError
     */
    static void _check_label_length(const SymbolicInstruction& a_instruction);
};
