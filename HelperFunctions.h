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