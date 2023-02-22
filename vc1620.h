//
// Created by bibhu on 2/21/2023.
//

#ifndef ASSEMBLER_VC1620_H
#define ASSEMBLER_VC1620_H

#include <array>

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
