#include <algorithm>
#include <fstream>
#include <stdexcept>

#include "Exceptions.h"
#include "HelperFunctions.h"

int getLocationOfNextInstruction(
    const SymbolicInstruction& a_currentInstruction, int a_currentLocation)
{
    int nextLocation {a_currentLocation + 1};

    std::string opcode {a_currentInstruction.getOpcode()};

    if (opcode == "ORG")
    {
        nextLocation = std::stoi(a_currentInstruction.getOperand1());
    }

    if (opcode == "DS")
    {
        nextLocation = a_currentLocation + std::stoi(a_currentInstruction.getOperand1());
    }

    return nextLocation;
}

bool isCommentOrEmpty(const std::string& a_line)
{
    if (a_line.empty()) // Empty a_line
        return true;

    if (a_line[0] == ';') // Comment
        return true;

    return false;
}

bool lineContainsLabel(const std::string& a_line)
{
    std::string uncommentedLine = getUncommentedLine(a_line);
    return uncommentedLine[0] != ' ' && uncommentedLine[0] != '\t';
}

std::string getUncommentedLine(const std::string& a_line)
{
    if (auto commentPosition {a_line.find(';')};
        commentPosition != std::string::npos)
    {
        return a_line.substr(0, commentPosition);
    }
    return a_line;
}

std::string getUpperCase(const std::string& a_str)
{
    std::string upper;
    for (auto c : a_str)
        upper += std::toupper(c);

    return upper;
}

std::string replaceCommas(const std::string& a_str)
{
    std::string replaced {a_str};
    std::ranges::replace(replaced.begin(), replaced.end(), ',', ' ');
    return replaced;
}

std::string removeCommentsAndCommas(const std::string& a_line)
{
    std::string uncommentedLine {getUncommentedLine(a_line)};
    return replaceCommas(uncommentedLine);
}

int getInstructionOperandCount(const std::string& a_opcode)
{
    std::string upperOpcode {getUpperCase(a_opcode)};

    using enum InstructionType;

    try
    {
        NumericOpcode opcodeEnum {
            SymbolicOpcode_NumericOpcode.at(upperOpcode)};
        return NumericOpcode_OperandCount.at(opcodeEnum);
    }
    catch (const std::out_of_range&)
    {
        throw InvalidOpcodeError {a_opcode};
    }
}

std::string getOperandTypeStr(OperandType a_operandType)
{
    using enum OperandType;

    switch (a_operandType)
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

OperandType getOperandType(const std::string& a_operand)
{
    using enum OperandType;
    if (a_operand.empty())
        return None;

    if (std::isdigit(a_operand[0]))
        return Numeric;

    return Symbolic;
}

void createSourceFile(const std::string& a_source,
                        const std::string& a_sourceFilePath)
{
    std::ofstream sourceFile {a_sourceFilePath};
    sourceFile << a_source;
    sourceFile.close();
}
