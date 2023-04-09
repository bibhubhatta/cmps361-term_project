#include <algorithm>
#include <fstream>
#include <stdexcept>

#include "Exceptions.h"
#include "HelperFunctions.h"

int get_location_of_next_instruction(
    const SymbolicInstruction& a_current_instruction, int a_current_location)
{
    int next_location {a_current_location + 1};

    std::string opcode {a_current_instruction.get_opcode()};

    if (opcode == "ORG")
    {
        next_location = std::stoi(a_current_instruction.get_operand_1());
    }

    if (opcode == "DS")
    {
        next_location = a_current_location + std::stoi(a_current_instruction.get_operand_1());
    }

    return next_location;
}

bool is_comment_or_empty(const std::string& a_line)
{
    if (a_line.empty()) // Empty a_line
        return true;

    if (a_line[0] == ';') // Comment
        return true;

    return false;
}

bool line_contains_label(const std::string& a_line)
{
    std::string uncommented_line = get_uncommented_line(a_line);
    return uncommented_line[0] != ' ' && uncommented_line[0] != '\t';
}

std::string get_uncommented_line(const std::string& a_line)
{
    if (auto comment_position {a_line.find(';')};
        comment_position != std::string::npos)
    {
        return a_line.substr(0, comment_position);
    }
    return a_line;
}

std::string get_upper_case(const std::string& a_str)
{
    std::string upper;
    for (auto c : a_str)
        upper += std::toupper(c);

    return upper;
}

std::string replace_commas(const std::string& a_str)
{
    std::string replaced {a_str};
    std::ranges::replace(replaced.begin(), replaced.end(), ',', ' ');
    return replaced;
}

std::string remove_comments_and_commas(const std::string& a_line)
{
    std::string uncommented_line {get_uncommented_line(a_line)};
    return replace_commas(uncommented_line);
}

int get_instruction_operand_count(const std::string& a_opcode)
{
    std::string upper_opcode {get_upper_case(a_opcode)};

    using enum InstructionType;

    try
    {
        NumericOpcode opcode_enum {
            SymbolicOpcode_NumericOpcode.at(upper_opcode)};
        return NumericOpcode_OperandCount.at(opcode_enum);
    }
    catch (const std::out_of_range&)
    {
        throw InvalidOpcodeError {a_opcode};
    }
}

std::string get_operand_type_str(OperandType a_operand_type)
{
    using enum OperandType;

    switch (a_operand_type)
    {
    case Symbolic:
        return "Symbolic";
    case Numeric:
        return "Numeric";
    case None:
        return "None";
    }

    return "Unknown";
}

OperandType get_operand_type(const std::string& a_operand)
{
    using enum OperandType;
    if (a_operand.empty())
        return None;

    if (std::isdigit(a_operand[0]))
        return Numeric;

    return Symbolic;
}

void create_source_file(const std::string& a_source,
                        const std::string& a_source_file_path)
{
    std::ofstream source_file {a_source_file_path};
    source_file << a_source;
    source_file.close();
}
