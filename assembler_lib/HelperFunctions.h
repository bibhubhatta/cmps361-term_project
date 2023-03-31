#pragma once

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