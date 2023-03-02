//
// Created by bibhu on 2/21/2023.
//

#ifndef ASSEMBLER_VC1620_H
#define ASSEMBLER_VC1620_H

#include <array>
#include <unordered_map>
#include <string>


const std::unordered_map<std::string, std::string> opcodeMap = {
        {"ADD",   "01"},
        {"SUB",   "02"},
        {"MULT",  "03"},
        {"DIV",   "04"},
        {"COPY",  "05"},
        {"READ",  "07"},
        {"WRITE", "08"},
        {"B",     "09"},
        {"BM",    "10"},
        {"BZ",    "11"},
        {"BP",    "12"},
        {"HALT",  "13"}
};

enum Opcode {
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

class Memory {
public:
    static const int MEMORY_SIZE = 100000;
    static const int WORD_SIZE = 12;

    Memory();

    void write(int address, int value);

    int read(int address) const;

private:
    std::array<int, MEMORY_SIZE> memory;
};

#endif //ASSEMBLER_VC1620_H
