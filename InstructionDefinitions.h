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
