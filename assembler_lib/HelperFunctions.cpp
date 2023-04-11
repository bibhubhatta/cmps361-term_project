#include <algorithm>
#include <fstream>
#include <stdexcept>

#include "Exceptions.h"
#include "HelperFunctions.h"

int GetLocationOfNextInstruction(
    const SymbolicInstruction& a_CurrentInstruction, int a_CurrentLocation)
{
    int NextLocation {a_CurrentLocation + 1};

    std::string opcode {a_CurrentInstruction.GetOpcode()};

    if (opcode == "ORG")
    {
        NextLocation = std::stoi(a_CurrentInstruction.GetOperand1());
    }

    if (opcode == "DS")
    {
        NextLocation = a_CurrentLocation + std::stoi(a_CurrentInstruction.GetOperand1());
    }

    return NextLocation;
}

bool IsCommentOrEmpty(const std::string& a_Line)
{
    if (a_Line.empty()) // Empty a_Line
        return true;

    if (a_Line[0] == ';') // Comment
        return true;

    return false;
}

bool LineContainsLabel(const std::string& a_Line)
{
    std::string UncommentedLine = GetUncommentedLine(a_Line);
    return UncommentedLine[0] != ' ' && UncommentedLine[0] != '\t';
}

std::string GetUncommentedLine(const std::string& a_Line)
{
    if (auto CommentPosition {a_Line.find(';')};
        CommentPosition != std::string::npos)
    {
        return a_Line.substr(0, CommentPosition);
    }
    return a_Line;
}

std::string GetUpperCase(const std::string& a_Str)
{
    std::string upper;
    for (auto c : a_Str)
        upper += std::toupper(c);

    return upper;
}

std::string ReplaceCommas(const std::string& a_Str)
{
    std::string replaced {a_Str};
    std::ranges::replace(replaced.begin(), replaced.end(), ',', ' ');
    return replaced;
}

std::string RemoveCommentsAndCommas(const std::string& a_Line)
{
    std::string UncommentedLine {GetUncommentedLine(a_Line)};
    return ReplaceCommas(UncommentedLine);
}

int GetInstructionOperandCount(const std::string& a_Opcode)
{
    std::string UpperOpcode {GetUpperCase(a_Opcode)};

    using enum InstructionType;

    try
    {
        NumericOpcode OpcodeEnum {
            SymbolicOpcode_NumericOpcode.at(UpperOpcode)};
        return NumericOpcode_OperandCount.at(OpcodeEnum);
    }
    catch (const std::out_of_range&)
    {
        throw InvalidOpcodeError {a_Opcode};
    }
}

std::string GetOperandTypeStr(OperandType a_OperandType)
{
    using enum OperandType;

    switch (a_OperandType)
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

OperandType GetOperandType(const std::string& a_Operand)
{
    using enum OperandType;
    if (a_Operand.empty())
        return None;

    if (std::isdigit(a_Operand[0]))
        return Numeric;

    return Symbolic;
}

void CreateSourceFile(const std::string& a_Source,
                        const std::string& a_SourceFilePath)
{
    std::ofstream SourceFile {a_SourceFilePath};
    SourceFile << a_Source;
    SourceFile.close();
}
