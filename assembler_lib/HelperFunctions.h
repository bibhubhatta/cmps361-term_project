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
 * @param a_CurrentInstruction    The current instruction
 * @param a_CurrentLocation       The current location
 * @return The location of the next instruction
 */
int GetLocationOfNextInstruction(
    const SymbolicInstruction& a_CurrentInstruction, int a_CurrentLocation);

/**
 * @brief Check if the a_Line is a comment or empty
 * @param a_Line  The a_Line to check
 * @return True if the a_Line is a comment or empty, false otherwise
 */
bool IsCommentOrEmpty(const std::string& a_Line);

/**
 * @brief Check if the a_Line contains a label
 * @param a_Line  The a_Line to check
 * @return True if the a_Line contains a label, false otherwise
 */
bool LineContainsLabel(const std::string& a_Line);

/**
 * @brief Get the uncommented a_Line
 * @param a_Line  The a_Line to get the uncommented a_Line from
 * @return The uncommented a_Line
 */
std::string GetUncommentedLine(const std::string& a_Line);

/**
 * @brief Get the upper case version of the string
 * @param a_Str   The string to get the upper case version of
 * @return The upper case version of the string
 */
std::string GetUpperCase(const std::string& a_Str);

/**
 * @brief Replace all commas in the string with spaces
 * @param a_Str
 * @return
 */
std::string ReplaceCommas(const std::string& a_Str);

/**
 * @brief Remove all comments and commas from the a_Line
 * @param a_Line  The a_Line to remove the comments and commas from
 * @return The a_Line without comments and commas
 */
std::string RemoveCommentsAndCommas(const std::string& a_Line);

/**
 * @brief Get the instruction operand count
 * @param a_Opcode    The instruction a_Opcode
 * @return The number of operands for the instruction
 */
int GetInstructionOperandCount(const std::string& a_Opcode);

/**
 * @brief Get the instruction a_Operand type
 * @param a_Operand   The a_Operand
 * @return The a_Operand type
 */
OperandType GetOperandType(const std::string& a_Operand);

/**
 * @brief Get the instruction operand type
 * @param a_OperandType The operand type
 * @return The string representation of the operand type
 */
std::string GetOperandTypeStr(OperandType a_OperandType);

/**
 * @brief Create a a_Source file with the given a_Source code and path
 * @param a_Source
 * @param a_SourceFilePath
 */
void CreateSourceFile(const std::string& a_Source,
                        const std::string& a_SourceFilePath);

/**
 * @brief Trim all whitespaces from the start of the string
 * @param a_S The string to trim
 */
inline void ltrim(std::string& a_S);

/**
 * @brief Trim all whitespaces from the end of the string
 * @param a_S The string to trim
 */
inline void rtrim(std::string& a_S);

/**
 * @brief Trim all whitespaces from the start and end of the string
 * @param a_S The string to trim
 */
inline void trim(std::string& a_S);

/** @brief Trim all whitespaces from the start of the string
 * @param a_S The string to trim
 * @return The trimmed string
 */
inline std::string LtrimCopy(std::string a_S);

/** @brief Trim all whitespaces from the end of the string
 * @param a_S The string to trim
 * @return The trimmed string
 */
inline std::string RtrimCopy(std::string a_S);

/** @brief Trim all whitespaces from the start and end of the string
 * @param a_S The string to trim
 * @return The trimmed string
 */
inline std::string TrimCopy(std::string a_S);

// The following functions should be ideally defined in the cpp file, but they
// are included here to avoid linker errors.

void ltrim(std::string& a_S)
{
    a_S.erase(a_S.begin(), std::ranges::find_if(a_S.begin(), a_S.end(),
                                            [](unsigned char ch)
                                            { return !std::isspace(ch); }));
}

void rtrim(std::string& a_S)
{
    a_S.erase(std::find_if(a_S.rbegin(), a_S.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
              a_S.end());
}

void trim(std::string& a_S)
{
    rtrim(a_S);
    ltrim(a_S);
}

std::string LtrimCopy(std::string a_S)
{
    ltrim(a_S);
    return a_S;
}

std::string RtrimCopy(std::string a_S)
{
    rtrim(a_S);
    return a_S;
}

std::string TrimCopy(std::string a_S)
{
    trim(a_S);
    return a_S;
}