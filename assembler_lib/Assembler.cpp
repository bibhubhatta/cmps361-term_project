#include <iostream>

#include <format>

#include "Assembler.h"
#include "Errors.h"
#include "Exceptions.h"
#include "HelperFunctions.h"
#include "InstructionDefinitions.h"
#include "NumericInstruction.h"

Assembler::Assembler(const std::string& a_SourceFilePath)
    : m_InstructionsFile(a_SourceFilePath)
{
}

void Assembler::Pass1()
{
    int CurrentInstructionLocation = 0;

    while (!m_InstructionsFile.EndOfFile())
    {
        try
        {
            std::string         line {m_InstructionsFile.GetNextLine()};
            SymbolicInstruction CurrentInstruction(line);

            switch (CurrentInstruction.GetType())
            {
            case InstructionType::End:
                m_CheckMemorySufficiency(CurrentInstructionLocation);
                m_CheckIfEndIsValid();
                return;
            case InstructionType::Comment:
                continue;

            default:
                if (CurrentInstruction.ContainsLabel())
                {
                    m_SymbolTable.AddSymbol(CurrentInstruction.GetLabel(),
                                             CurrentInstructionLocation);

                    m_CheckLabelLength(CurrentInstruction);
                }
                CurrentInstructionLocation = GetLocationOfNextInstruction(
                    CurrentInstruction, CurrentInstructionLocation);
            }
        }

        catch (std::exception& e)
        {
            m_RecordError(e, "pass 1");
        }
    }

    try
    {
        m_CheckMemorySufficiency(CurrentInstructionLocation);
        throw MissingEndStatementError();
    }
    catch (std::exception& e)
    {
        m_RecordError(e, "pass 1");
    }
}

void Assembler::m_CheckLabelLength(const SymbolicInstruction& a_Instruction)
{
    if (a_Instruction.GetLabel().length() > 10)
    {
        throw LabelTooLongError(a_Instruction.GetLabel());
    }
}

void Assembler::m_RecordError(const std::exception& a_E,
                              const std::string&    a_Where) const
{
    std::string ErrorDescription {
        std::format("Error {} occurred at '{}' in line {} during {}",
                    a_E.what(),
                    m_InstructionsFile.GetCurrentLine(),
                    m_InstructionsFile.GetCurrentLineNumber(), a_Where)};
    Errors::RecordError(ErrorDescription);
}

void Assembler::m_CheckIfEndIsValid()
{
    std::string StatementsAfterEnd;
    while (!m_InstructionsFile.EndOfFile())
    {
        StatementsAfterEnd += m_InstructionsFile.GetNextLine();
    }

    trim(StatementsAfterEnd);

    if (!StatementsAfterEnd.empty())
    {
        throw StatementAfterEndError(StatementsAfterEnd);
    }
}

void Assembler::m_CheckMemorySufficiency(int a_LastInstructionLocation) const
{
    if (a_LastInstructionLocation >= Emulator::MEMORY_SIZE)
    {
        throw InsufficientMemoryError(a_LastInstructionLocation + 1,
                                      Emulator::MEMORY_SIZE);
    }
}

void Assembler::Pass2()
{
    m_InstructionsFile.rewind();

    std::cout << std::format("{:<10}{:<15}{:<30}\n", // Set format
                             "Location", "Contents", "Original Statement");

    int CurrentInstructionLocation = 0;

    while (!m_InstructionsFile.EndOfFile())
    {
        try
        {
            std::string         line {m_InstructionsFile.GetNextLine()};
            SymbolicInstruction CurrentSymbolicInstruction(line);

            switch (CurrentSymbolicInstruction.GetType())
            {
            case InstructionType::End:
                std::cout << std::format(
                    "{:<10}{:<15}{:<30}\n", // Set format
                    "",                     // No location
                    "",                     // No contents
                    CurrentSymbolicInstruction.GetOriginalInstruction());
                return;
            case InstructionType::Comment:
                std::cout << std::format(
                    "{:<10}{:<15}{:<30}\n", // Set format
                    "",                     // No location
                    "",                     // No contents
                    CurrentSymbolicInstruction.GetOriginalInstruction());
                continue;

            default:
                NumericInstruction CurrentNumericInstruction(
                    CurrentSymbolicInstruction, m_SymbolTable);

                std::cout << std::format(
                    "{:<10}{:<15}{:<30}\n", // Set format
                    CurrentInstructionLocation,
                    CurrentNumericInstruction.GetStringRepresentation(),
                    CurrentSymbolicInstruction.GetOriginalInstruction());

                m_CheckMemorySufficiency(CurrentInstructionLocation);

                m_Emulator.insert(
                    CurrentInstructionLocation,
                    CurrentNumericInstruction.GetNumericRepresentation());
            }

            CurrentInstructionLocation = GetLocationOfNextInstruction(
                CurrentSymbolicInstruction, CurrentInstructionLocation);
        }
        catch (std::exception& e)
        {
            m_RecordError(e, "pass 2");
        }
    }
}

void Assembler::RunProgramInEmulator() { m_Emulator.RunProgram(); }