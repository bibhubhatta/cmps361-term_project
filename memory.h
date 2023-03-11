#ifndef MEMORY_H
#define MEMORY_H

#include <string>

class Memory {
public:
    Memory();
    void clear();
    void set(int address, int value);
    int get(int address) const;
    bool load_program(const std::string& filename, int start_address);

private:
    int memory_[100000];
};

#endif // MEMORY_H
