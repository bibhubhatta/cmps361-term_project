//
// Created by bibhu on 2/21/2023.
//

#include <stdexcept>
#include "vc1620.h"


Memory::Memory() {
    memory.fill(0);
}

void Memory::write(int address, int value) {
    if (address < 0 || address >= MEMORY_SIZE) {
        throw std::out_of_range("Invalid memory address");
    }

    if (value < 0 || value >= 14'000000'00000) {
        throw std::out_of_range("Invalid memory value");
    }

    memory[address] = value;
}

int Memory::read(int address) const {
    if (address < 0 || address >= MEMORY_SIZE) {
        throw std::out_of_range("Invalid memory address");
    }

    return memory[address];
}

