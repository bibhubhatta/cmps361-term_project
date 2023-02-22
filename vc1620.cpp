//
// Created by bibhu on 2/21/2023.
//

#include "vc1620.h"


Memory::Memory(int size) {
    m_size = size;
    m_data = new int[m_size];
    for (int i = 0; i < m_size; i++) {
        m_data[i] = 0;  // Initialize all memory locations to 0
    }
}

Memory::~Memory() {
    delete[] m_data;
}

int Memory::read(int address) const {
    return m_data[address];
}

void Memory::write(int address, int value) {
    m_data[address] = value;
}

