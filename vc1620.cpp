//
// Created by bibhu on 2/21/2023.
//

#include <stdexcept>
#include <fstream>
#include <iostream>
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

void Memory::display(int start, int end) const {
    for (int i = start; i <= end; i++) {
        std::cout << memory[i] << std::endl;
    }
}

void Memory::clear() {
    memory.fill(0);
}

VC1620::VC1620() {
    memory_.clear();
    unsigned instruction_counter = 0;
    unsigned opcode = 0;
    unsigned operand1 = 0;
    unsigned operand2 = 0;

}

void VC1620::load_program(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        memory_.write(i, std::stoi(line));
        i++;
    }

}
