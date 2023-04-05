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
 * @param current_instruction    The current instruction
 * @param current_location       The current location
 * @return The location of the next instruction
 */
int get_location_of_next_instruction(
    const SymbolicInstruction& current_instruction, int current_location);

/**
 * @brief Check if the line is a comment or empty
 * @param line  The line to check
 * @return True if the line is a comment or empty, false otherwise
 */
bool is_comment_or_empty(const std::string& line);

/**
 * @brief Check if the line contains a label
 * @param line  The line to check
 * @return True if the line contains a label, false otherwise
 */
bool line_contains_label(const std::string& line);

/**
 * @brief Get the uncommented line
 * @param line  The line to get the uncommented line from
 * @return The uncommented line
 */
std::string get_uncommented_line(const std::string& line);

/**
 * @brief Get the upper case version of the string
 * @param str   The string to get the upper case version of
 * @return The upper case version of the string
 */
std::string get_upper_case(const std::string& str);

/**
 * @brief Replace all commas in the string with spaces
 * @param str
 * @return
 */
std::string replace_commas(const std::string& str);

/**
 * @brief Remove all comments and commas from the line
 * @param line  The line to remove the comments and commas from
 * @return The line without comments and commas
 */
std::string remove_comments_and_commas(const std::string& line);

/**
 * @brief Get the instruction operand count
 * @param opcode    The instruction opcode
 * @return The number of operands for the instruction
 */
int get_instruction_operand_count(const std::string& opcode);

/**
 * @brief Get the instruction operand type
 * @param operand   The operand
 * @return The operand type
 */
OperandType get_operand_type(const std::string& operand);

/**
 * @brief Get the instruction operand type
 * @param operand_type The operand type
 * @return The string representation of the operand type
 */
std::string get_operand_type_str(OperandType operand_type);

/**
 * @brief Create a source file with the given source code and path
 * @param source
 * @param source_file_path
 */
void create_source_file(const std::string& source,
                        const std::string& source_file_path);

/**
 * @brief Trim all whitespaces from the start of the string
 * @param s The string to trim
 */
inline void ltrim(std::string& s);

/**
 * @brief Trim all whitespaces from the end of the string
 * @param s The string to trim
 */
inline void rtrim(std::string& s);

/**
 * @brief Trim all whitespaces from the start and end of the string
 * @param s The string to trim
 */
inline void trim(std::string& s);

/** @brief Trim all whitespaces from the start of the string
 * @param s The string to trim
 * @return The trimmed string
 */
inline std::string ltrim_copy(std::string s);

/** @brief Trim all whitespaces from the end of the string
 * @param s The string to trim
 * @return The trimmed string
 */
inline std::string rtrim_copy(std::string s);

/** @brief Trim all whitespaces from the start and end of the string
 * @param s The string to trim
 * @return The trimmed string
 */
inline std::string trim_copy(std::string s);

// The following functions should be ideally defined in the cpp file, but they
// are included here to avoid linker errors.

void ltrim(std::string& s)
{
    s.erase(s.begin(), std::ranges::find_if(s.begin(), s.end(),
                                            [](unsigned char ch)
                                            { return !std::isspace(ch); }));
}

void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
}

void trim(std::string& s)
{
    rtrim(s);
    ltrim(s);
}

std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}