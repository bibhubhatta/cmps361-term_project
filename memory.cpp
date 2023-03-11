#include "memory.h"

// Constructor: initialize all memory locations to 0
Memory::Memory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
}

// Getter method for the value at a specific memory location
int Memory::get_value(int address) const {
    if (address < 0 || address >= MEMORY_SIZE) {
        throw std::out_of_range("Memory address out of range.");
    }
    return memory[address];
}

// Setter method for the value at a specific memory location
void Memory::set_value(int address, int value) {
    if (address < 0 || address >= MEMORY_SIZE) {
        throw std::out_of_range("Memory address out of range.");
    }
    memory[address] = value;
}

// Reset all memory locations to 0
void Memory::reset() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
}
