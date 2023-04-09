#include <iostream>

#include <format>

#include "Assembler.h"
#include "Errors.h"
#include "Exceptions.h"
#include "HelperFunctions.h"
#include "InstructionDefinitions.h"
#include "NumericInstruction.h"

Assembler::Assembler(const std::string& a_sourceFilePath)
    : m_instructionsFile(a_sourceFilePath)
{
}

void Assembler::pass1()
{
    int currentInstructionLocation = 0;

    while (!m_instructionsFile.endOfFile())
    {
        try
        {
            std::string         line {m_instructionsFile.getNextLine()};
            SymbolicInstruction currentInstruction(line);

            switch (currentInstruction.getType())
            {
            case InstructionType::End:
                m_checkMemorySufficiency(currentInstructionLocation);
                m_checkIfEndIsValid();
                return;
            case InstructionType::Comment:
                continue;

            default:
                if (currentInstruction.containsLabel())
                {
                    m_symbolTable.addSymbol(currentInstruction.getLabel(),
                                             currentInstructionLocation);

                    m_checkLabelLength(currentInstruction);
                }
                currentInstructionLocation = GetLocationOfNextInstruction(
                    currentInstruction, currentInstructionLocation);
            }
        }

        catch (std::exception& e)
        {
            m_recordError(e, "pass 1");
        }
    }

    try
    {
        m_checkMemorySufficiency(currentInstructionLocation);
        throw MissingEndStatementError();
    }
    catch (std::exception& e)
    {
        m_recordError(e, "pass 1");
    }
}

void Assembler::m_checkLabelLength(const SymbolicInstruction& a_instruction)
{
    if (a_instruction.getLabel().length() > 10)
    {
        throw LabelTooLongError(a_instruction.getLabel());
    }
}

void Assembler::m_recordError(const std::exception& a_e,
                              const std::string&    a_where) const
{
    std::string errorDescription {
        std::format("Error {} occurred at '{}' in line {} during {}",
                    a_e.what(),
                    m_instructionsFile.getCurrentLine(),
                    m_instructionsFile.getCurrentLineNumber(), a_where)};
    Errors::recordError(errorDescription);
}

void Assembler::m_checkIfEndIsValid()
{
    std::string statementsAfterEnd;
    while (!m_instructionsFile.endOfFile())
    {
        statementsAfterEnd += m_instructionsFile.getNextLine();
    }

    Trim(statementsAfterEnd);

    if (!statementsAfterEnd.empty())
    {
        throw StatementAfterEndError(statementsAfterEnd);
    }
}

void Assembler::m_checkMemorySufficiency(int a_lastInstructionLocation) const
{
    if (a_lastInstructionLocation >= Emulator::MEMORY_SIZE)
    {
        throw InsufficientMemoryError(a_lastInstructionLocation + 1,
                                      Emulator::MEMORY_SIZE);
    }
}

void Assembler::pass2()
{
    m_instructionsFile.rewind();

    std::cout << std::format("{:<10}{:<15}{:<30}\n", // Set format
                             "Location", "Contents", "Original Statement");

    int currentInstructionLocation = 0;

    while (!m_instructionsFile.endOfFile())
    {
        try
        {
            std::string         line {m_instructionsFile.getNextLine()};
            SymbolicInstruction currentSymbolicInstruction(line);

            switch (currentSymbolicInstruction.getType())
            {
            case InstructionType::End:
                std::cout << std::format(
                    "{:<10}{:<15}{:<30}\n", // Set format
                    "",                     // No location
                    "",                     // No contents
                    currentSymbolicInstruction.getOriginalInstruction());
                return;
            case InstructionType::Comment:
                std::cout << std::format(
                    "{:<10}{:<15}{:<30}\n", // Set format
                    "",                     // No location
                    "",                     // No contents
                    currentSymbolicInstruction.getOriginalInstruction());
                continue;

            default:
                NumericInstruction currentNumericInstruction(
                    currentSymbolicInstruction, m_symbolTable);

                std::cout << std::format(
                    "{:<10}{:<15}{:<30}\n", // Set format
                    currentInstructionLocation,
                    currentNumericInstruction.getStringRepresentation(),
                    currentSymbolicInstruction.getOriginalInstruction());

                m_checkMemorySufficiency(currentInstructionLocation);

                m_emulator.insert(
                    currentInstructionLocation,
                    currentNumericInstruction.getNumericRepresentation());
            }

            currentInstructionLocation = GetLocationOfNextInstruction(
                currentSymbolicInstruction, currentInstructionLocation);
        }
        catch (std::exception& e)
        {
            m_recordError(e, "pass 2");
        }
    }
}

void Assembler::runProgramInEmulator() { m_emulator.runProgram(); }