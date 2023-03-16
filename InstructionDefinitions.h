#pragma once

#include <map>
#include <string>

// Codes to indicate the type of instruction we are processing
enum class InstructionType
{
    MachineLanguage,      // A machine language instruction.
    AssemblerInstruction, // Assembler Language instruction.
    Comment,              // Comment or blank line
    End                   // end instruction.
};

// Maps symbolic instruction to type
const std::map<std::string, InstructionType, std::less<>>
    SYMBOLIC_INSTRUCTION_TYPE {
        // Assembler Instructions
        {"DC", InstructionType::AssemblerInstruction},
        {"DS", InstructionType::AssemblerInstruction},
        {"ORG", InstructionType::AssemblerInstruction},
        {"END", InstructionType::End},

        // Machine Language Instructions
        {"ADD", InstructionType::MachineLanguage},   // 01
        {"SUB", InstructionType::MachineLanguage},   // 02
        {"MULT", InstructionType::MachineLanguage},  // 03
        {"DIV", InstructionType::MachineLanguage},   // 04
        {"COPY", InstructionType::MachineLanguage},  // 05
        {"READ", InstructionType::MachineLanguage},  // 07
        {"WRITE", InstructionType::MachineLanguage}, // 08
        {"B", InstructionType::MachineLanguage},     // 09
        {"BM", InstructionType::MachineLanguage},    // 10
        {"BZ", InstructionType::MachineLanguage},    // 11
        {"BP", InstructionType::MachineLanguage},    // 12
        {"HALT", InstructionType::MachineLanguage}   // 13
    };

enum class NumericOpcode
{
    // Assembler Instructions
    DC = 0,   // 00
    DS = -1,  // has no numeric instruction
    ORG = -1, // has no numeric instruction
    END = -1, // has no numeric instruction

    // Machine Language Instructions
    ADD = 1,   // 01
    SUB = 2,   // 02
    MULT = 3,  // 03
    DIV = 4,   // 04
    COPY = 5,  // 05
    READ = 7,  // 07
    WRITE = 8, // 08
    B = 9,     // 09
    BM = 10,   // 10
    BZ = 11,   // 11
    BP = 12,   // 12
    HALT = 13  // 13
};

// Maps symbolic instruction to NumericOpcode
const std::map<std::string, NumericOpcode, std::less<>> NUMERIC_OPCODE {
    // Assembler Instructions
    {"DC", NumericOpcode::DC},   // 00
    {"DS", NumericOpcode::DS},   // 00
    {"ORG", NumericOpcode::ORG}, // 00
    {"END", NumericOpcode::END}, // 00

    // Machine Language Instructions
    {"ADD", NumericOpcode::ADD},     // 01
    {"SUB", NumericOpcode::SUB},     // 02
    {"MULT", NumericOpcode::MULT},   // 03
    {"DIV", NumericOpcode::DIV},     // 04
    {"COPY", NumericOpcode::COPY},   // 05
    {"READ", NumericOpcode::READ},   // 07
    {"WRITE", NumericOpcode::WRITE}, // 08
    {"B", NumericOpcode::B},         // 09
    {"BM", NumericOpcode::BM},       // 10
    {"BZ", NumericOpcode::BZ},       // 11
    {"BP", NumericOpcode::BP},       // 12
    {"HALT", NumericOpcode::HALT}    // 13
};

// Maps symbolic instruction to number of operands
const std::map<std::string, int, std::less<>> INSTRUCTION_OPERAND_COUNT {
    // Assembler Instructions
    {"DC", 1}, // Variable declaration
    {"DS", 1}, // Variable declaration
    {"ORG", 1},
    {"END", 0},

    // Machine Language Instructions
    {"ADD", 2},   // 01
    {"SUB", 2},   // 02
    {"MULT", 2},  // 03
    {"DIV", 2},   // 04
    {"COPY", 2},  // 05
    {"READ", 1},  // 07
    {"WRITE", 1}, // 08
    {"B", 1},     // 09
    {"BM", 2},    // 10
    {"BZ", 2},    // 11
    {"BP", 2},    // 12
    {"HALT", 0}   // 13
};

// Maps symbolic instruction to number of operands
const std::map<std::string, int, std::less<>> INSTRUCTION_OPERAND_LENGTH {
    // Assembler Instructions
    {"DC", 4}, // Variable declaration
    {"DS", 4}, // Variable declaration
    {"ORG", 4},
    {"END", 0}};

// Maps numeric instruction to number of operands
const std::map<NumericOpcode, int, std::less<>>
    NUMERIC_INSTRUCTION_OPERAND_COUNT {
        // Assembler Instructions
        {NumericOpcode::DC, 1}, // Variable declaration
        {NumericOpcode::DS, 1}, // Variable declaration
        {NumericOpcode::ORG, 1},
        {NumericOpcode::END, 0},

        // Machine Language Instructions
        {NumericOpcode::ADD, 2},   // 01
        {NumericOpcode::SUB, 2},   // 02
        {NumericOpcode::MULT, 2},  // 03
        {NumericOpcode::DIV, 2},   // 04
        {NumericOpcode::COPY, 2},  // 05
        {NumericOpcode::READ, 1},  // 07
        {NumericOpcode::WRITE, 1}, // 08
        {NumericOpcode::B, 1},     // 09
        {NumericOpcode::BM, 2},    // 10
        {NumericOpcode::BZ, 2},    // 11
        {NumericOpcode::BP, 2},    // 12
        {NumericOpcode::HALT, 0}   // 13
    };

// Maps numeric instruction to InstructionType
const std::map<NumericOpcode, InstructionType, std::less<>>
    NUMERIC_INSTRUCTION_TYPE {
        // Assembler Instructions
        {NumericOpcode::DC,
         InstructionType::AssemblerInstruction}, // Variable declaration
        {NumericOpcode::DS,
         InstructionType::AssemblerInstruction}, // Variable declaration
        {NumericOpcode::ORG, InstructionType::AssemblerInstruction},
        {NumericOpcode::END, InstructionType::End},

        // Machine Language Instructions
        {NumericOpcode::ADD, InstructionType::MachineLanguage},   // 01
        {NumericOpcode::SUB, InstructionType::MachineLanguage},   // 02
        {NumericOpcode::MULT, InstructionType::MachineLanguage},  // 03
        {NumericOpcode::DIV, InstructionType::MachineLanguage},   // 04
        {NumericOpcode::COPY, InstructionType::MachineLanguage},  // 05
        {NumericOpcode::READ, InstructionType::MachineLanguage},  // 07
        {NumericOpcode::WRITE, InstructionType::MachineLanguage}, // 08
        {NumericOpcode::B, InstructionType::MachineLanguage},     // 09
        {NumericOpcode::BM, InstructionType::MachineLanguage},    // 10
        {NumericOpcode::BZ, InstructionType::MachineLanguage},    // 11
        {NumericOpcode::BP, InstructionType::MachineLanguage},    // 12
        {NumericOpcode::HALT, InstructionType::MachineLanguage}   // 13
    };