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
     * @param a_SourceFilePath The path to the source file.
     */
    explicit Assembler(const std::string& a_SourceFilePath);
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
    void Pass1();

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
    void Pass2();

    /**
     * @brief Displays the symbol table.
     */
    void DisplaySymbolTable() const { m_SymbolTable.DisplaySymbolTable(); }

    /**
     * @brief Runs the program in the emulator.
     */
    void RunProgramInEmulator();

  private:
    FileAccess  m_InstructionsFile;
    SymbolTable m_SymbolTable;
    Emulator    m_Emulator;

    /**
     * @brief Checks if the memory is sufficient to hold the program.
     * @param a_LastInstructionLocation The location of the last instruction.
     */
    void m_CheckMemorySufficiency(int a_LastInstructionLocation) const;

    /**
     * @brief Checks if the end statement is valid and throws error if not.
     * @details The end statement is valid if it is the last statement in the
     * program and there are no statements after it. If the end statement is
     * invalid, a StatementAfterEndError is thrown.
     */
    void m_CheckIfEndIsValid();

    /**
     * @brief Records the error message in the error log.
     * @param a_E The exception that was thrown.
     */
    void m_RecordError(const std::exception& a_E,
                       const std::string&    a_Where) const;

    /**
     * @brief Checks if the label is too long.
     * @details If the label is too long, a LabelTooLongError is thrown.
     * @param a_Instruction The instruction that contains the label.
     * @throws LabelTooLongError
     */
    static void m_CheckLabelLength(const SymbolicInstruction& a_Instruction);
};
