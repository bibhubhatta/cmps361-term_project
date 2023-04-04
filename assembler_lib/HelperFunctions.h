#pragma once

#include <algorithm>
#include <cctype>
#include <locale>
#include <map>
#include <string>

#include "InstructionDefinitions.h"
#include "SymbolicInstruction.h"

int get_location_of_next_instruction(
    const SymbolicInstruction& current_instruction, int current_location);

bool is_comment_or_empty(const std::string& line);
bool line_contains_label(const std::string& line);

std::string get_uncommented_line(const std::string& line);

std::string get_upper_case(const std::string& str);

std::string replace_commas(const std::string& str);

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

// trim from start (in place)
static inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::ranges::find_if(s.begin(), s.end(),
                                            [](unsigned char ch)
                                            { return !std::isspace(ch); }));
}

// trim from end (in place)
static inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s)
{
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}