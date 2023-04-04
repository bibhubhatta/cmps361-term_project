#pragma once

#include <map>
#include <string>

// Codes to indicate the type of instruction we are processing
enum class InstructionType
{
    MachineLanguage,
    AssemblerInstruction,
    Comment,
    End
};

// Maps symbolic opcode to type
const std::map<std::string, InstructionType, std::less<>> SymbolicOpcode_Type {

    // Assembler Instructions
    {"DC", InstructionType::AssemblerInstruction},
    {"DS", InstructionType::AssemblerInstruction},
    {"ORG", InstructionType::AssemblerInstruction},
    {"END", InstructionType::End},

    // Machine Language Instructions
    {"ADD", InstructionType::MachineLanguage},
    {"SUB", InstructionType::MachineLanguage},
    {"MULT", InstructionType::MachineLanguage},
    {"DIV", InstructionType::MachineLanguage},
    {"COPY", InstructionType::MachineLanguage},
    {"READ", InstructionType::MachineLanguage},
    {"WRITE", InstructionType::MachineLanguage},
    {"B", InstructionType::MachineLanguage},
    {"BM", InstructionType::MachineLanguage},
    {"BZ", InstructionType::MachineLanguage},
    {"BP", InstructionType::MachineLanguage},
    {"HALT", InstructionType::MachineLanguage}};

enum class NumericOpcode
{
    // Assembler Instructions
    DC = 0,
    DS = -1,  // has no numeric instruction
    ORG = -2, // has no numeric instruction
    END = -3, // has no numeric instruction

    // Machine Language Instructions
    ADD = 1,
    SUB = 2,
    MULT = 3,
    DIV = 4,
    COPY = 5,
    READ = 7,
    WRITE = 8,
    B = 9,
    BM = 10,
    BZ = 11,
    BP = 12,
    HALT = 13
};

// Maps symbolic opcode to NumericOpcode
const std::map<std::string, NumericOpcode, std::less<>>
    SymbolicOpcode_NumericOpcode {

        // Assembler Instructions
        {"DC", NumericOpcode::DC},
        {"DS", NumericOpcode::DS},
        {"ORG", NumericOpcode::ORG},
        {"END", NumericOpcode::END},

        // Machine Language Instructions
        {"ADD", NumericOpcode::ADD},
        {"SUB", NumericOpcode::SUB},
        {"MULT", NumericOpcode::MULT},
        {"DIV", NumericOpcode::DIV},
        {"COPY", NumericOpcode::COPY},
        {"READ", NumericOpcode::READ},
        {"WRITE", NumericOpcode::WRITE},
        {"B", NumericOpcode::B},
        {"BM", NumericOpcode::BM},
        {"BZ", NumericOpcode::BZ},
        {"BP", NumericOpcode::BP},
        {"HALT", NumericOpcode::HALT}};

// Maps numeric opcode to number of operands
const std::map<NumericOpcode, int, std::less<>> NumericOpcode_OperandCount {

    // Assembler Instructions
    {NumericOpcode::DC, 1},
    {NumericOpcode::DS, 1},
    {NumericOpcode::ORG, 1},
    {NumericOpcode::END, 0},

    // Machine Language Instructions
    {NumericOpcode::ADD, 2},
    {NumericOpcode::SUB, 2},
    {NumericOpcode::MULT, 2},
    {NumericOpcode::DIV, 2},
    {NumericOpcode::COPY, 2},
    {NumericOpcode::READ, 1},
    {NumericOpcode::WRITE, 1},
    {NumericOpcode::B, 1},
    {NumericOpcode::BM, 2},
    {NumericOpcode::BZ, 2},
    {NumericOpcode::BP, 2},
    {NumericOpcode::HALT, 0}};

// Types of operands
enum class OperandType
{
    Symbolic,
    Numeric,
    None
};

// Maps symbolic opcode to type of operand
const std::map<std::string, OperandType, std::less<>>
    SymbolicOpcode_OperandType {

        // Assembler Instructions
        {"DC", OperandType::Numeric},
        {"DS", OperandType::Numeric},
        {"ORG", OperandType::Numeric},
        {"END", OperandType::None},

        // Machine Language Instructions
        {"ADD", OperandType::Symbolic},
        {"SUB", OperandType::Symbolic},
        {"MULT", OperandType::Symbolic},
        {"DIV", OperandType::Symbolic},
        {"COPY", OperandType::Symbolic},
        {"READ", OperandType::Symbolic},
        {"WRITE", OperandType::Symbolic},
        {"B", OperandType::Symbolic},
        {"BM", OperandType::Symbolic},
        {"BZ", OperandType::Symbolic},
        {"BP", OperandType::Symbolic},
        {"HALT", OperandType::None}};
