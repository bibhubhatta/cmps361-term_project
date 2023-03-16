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
const std::map<std::string, InstructionType, std::less<>> INSTRUCTION_TYPE {
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

// Maps symbolic instruction to opcode
const std::map<std::string, int, std::less<>> INSTRUCTION_OPCODE {
    // Assembler Instructions
    {"DC", 0}, // Variable declaration
    {"DS", 0}, // Variable declaration
    {"ORG", 0},
    {"END", 0},

    // Machine Language Instructions
    {"ADD", 1},   // 01
    {"SUB", 2},   // 02
    {"MULT", 3},  // 03
    {"DIV", 4},   // 04
    {"COPY", 5},  // 05
    {"READ", 7},  // 07
    {"WRITE", 8}, // 08
    {"B", 9},     // 09
    {"BM", 10},   // 10
    {"BZ", 11},   // 11
    {"BP", 12},   // 12
    {"HALT", 13}  // 13
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
    {"BM", 1},    // 10
    {"BZ", 1},    // 11
    {"BP", 1},    // 12
    {"HALT", 0}   // 13
};

// Maps symbolic instruction to number of operands
const std::map<std::string, int, std::less<>> INSTRUCTION_OPERAND_LENGTH {
    // Assembler Instructions
    {"DC", 4}, // Variable declaration
    {"DS", 4}, // Variable declaration
    {"ORG", 4},
    {"END", 0}};
