/**
 * @file HelperFunctions.h
 * @brief Helper functions for the assembler.
 * @details This file contains helper functions for the assembler.
 * These functions are used by multiple classes.
 */

#pragma once

#include <algorithm>
#include <cctype>
#include <locale>
#include <map>
#include <string>

#include "InstructionDefinitions.h"
#include "SymbolicInstruction.h"

/**
 * @brief Get the location of the next instruction
 * @param a_currentInstruction    The current instruction
 * @param a_currentLocation       The current location
 * @return The location of the next instruction
 */
int getLocationOfNextInstruction(
    const SymbolicInstruction& a_currentInstruction, int a_currentLocation);

/**
 * @brief Check if the a_line is a comment or empty
 * @param a_line  The a_line to check
 * @return True if the a_line is a comment or empty, false otherwise
 */
bool isCommentOrEmpty(const std::string& a_line);

/**
 * @brief Check if the a_line contains a label
 * @param a_line  The a_line to check
 * @return True if the a_line contains a label, false otherwise
 */
bool lineContainsLabel(const std::string& a_line);

/**
 * @brief Get the uncommented a_line
 * @param a_line  The a_line to get the uncommented a_line from
 * @return The uncommented a_line
 */
std::string getUncommentedLine(const std::string& a_line);

/**
 * @brief Get the upper case version of the string
 * @param a_str   The string to get the upper case version of
 * @return The upper case version of the string
 */
std::string getUpperCase(const std::string& a_str);

/**
 * @brief Replace all commas in the string with spaces
 * @param a_str
 * @return
 */
std::string replaceCommas(const std::string& a_str);

/**
 * @brief Remove all comments and commas from the a_line
 * @param a_line  The a_line to remove the comments and commas from
 * @return The a_line without comments and commas
 */
std::string removeCommentsAndCommas(const std::string& a_line);

/**
 * @brief Get the instruction operand count
 * @param a_opcode    The instruction a_opcode
 * @return The number of operands for the instruction
 */
int getInstructionOperandCount(const std::string& a_opcode);

/**
 * @brief Get the instruction a_operand type
 * @param a_operand   The a_operand
 * @return The a_operand type
 */
OperandType getOperandType(const std::string& a_operand);

/**
 * @brief Get the instruction operand type
 * @param a_operandType The operand type
 * @return The string representation of the operand type
 */
std::string getOperandTypeStr(OperandType a_operandType);

/**
 * @brief Create a a_source file with the given a_source code and path
 * @param a_source
 * @param a_sourceFilePath
 */
void createSourceFile(const std::string& a_source,
                        const std::string& a_sourceFilePath);

/**
 * @brief Trim all whitespaces from the start of the string
 * @param a_s The string to trim
 */
inline void ltrim(std::string& a_s);

/**
 * @brief Trim all whitespaces from the end of the string
 * @param a_s The string to trim
 */
inline void rtrim(std::string& a_s);

/**
 * @brief Trim all whitespaces from the start and end of the string
 * @param a_s The string to trim
 */
inline void trim(std::string& a_s);

/** @brief Trim all whitespaces from the start of the string
 * @param a_s The string to trim
 * @return The trimmed string
 */
inline std::string ltrimCopy(std::string a_s);

/** @brief Trim all whitespaces from the end of the string
 * @param a_s The string to trim
 * @return The trimmed string
 */
inline std::string rtrimCopy(std::string a_s);

/** @brief Trim all whitespaces from the start and end of the string
 * @param a_s The string to trim
 * @return The trimmed string
 */
inline std::string trimCopy(std::string a_s);

// The following functions should be ideally defined in the cpp file, but they
// are included here to avoid linker errors.

void ltrim(std::string& a_s)
{
    a_s.erase(a_s.begin(), std::ranges::find_if(a_s.begin(), a_s.end(),
                                            [](unsigned char ch)
                                            { return !std::isspace(ch); }));
}

void rtrim(std::string& a_s)
{
    a_s.erase(std::find_if(a_s.rbegin(), a_s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
              a_s.end());
}

void trim(std::string& a_s)
{
    rtrim(a_s);
    ltrim(a_s);
}

std::string ltrimCopy(std::string a_s)
{
    ltrim(a_s);
    return a_s;
}

std::string rtrimCopy(std::string a_s)
{
    rtrim(a_s);
    return a_s;
}

std::string trimCopy(std::string a_s)
{
    trim(a_s);
    return a_s;
}