#include "HelperFunctions.h"

int get_location_of_next_instruction(
    const SymbolicInstruction& current_instruction, int current_location)
{
    int next_location{current_location + 1};

    std::string opcode{current_instruction.get_opcode()};

    if (opcode == "ORG")
    {
        next_location = std::stoi(current_instruction.get_operand_1());
    }

    if (opcode == "DS")
    {
        next_location =
            current_location + std::stoi(current_instruction.get_operand_1());
    }

    return next_location;
}

bool is_comment_or_empty(const std::string& line)
{
    if (line.empty()) // Empty line
        return true;

    if (line[0] == ';') // Comment
        return true;

    return false;
}

bool line_contains_label(const std::string& line)
{
    std::string uncommented_line = get_uncommented_line(line);
    return uncommented_line[0] != ' ' && uncommented_line[0] != '\t';
}

std::string get_uncommented_line(const std::string& line)
{
    if (auto comment_position{line.find(';')};
        comment_position != std::string::npos)
    {
        return line.substr(0, comment_position);
    }
    return line;
}

std::string get_upper_case(const std::string& str)
{
    std::string upper;
    for (auto c : str)
        upper += std::toupper(c);

    return upper;
}
