//
// Created by bibhu on 2/21/2023.
//

#ifndef ASSEMBLER_VC1620_H
#define ASSEMBLER_VC1620_H

class Memory {
public:
    Memory(int size = 100'000);  // Constructor, default size is 100000 words
    ~Memory();  // Destructor
    int read(int address) const;  // Read the value stored at the specified memory address
    void write(int address, int value);  // Write the specified value to the specified memory address
private:
    int *m_data;  // Pointer to the start of the memory array
    int m_size;  // Size of the memory array
};

#endif //ASSEMBLER_VC1620_H
