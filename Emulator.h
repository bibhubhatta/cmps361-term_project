//
//		Emulator class - supports the emulation of VC1620 programs
//
#pragma once

#include <array>

class Emulator
{
  public:
    const static int MEMORY_SIZE = 100'000;

    Emulator() = default;

    // Records instructions and data into simulated memory.
    void insert(int location, long long contents);

    // Runs the program recorded in memory.
    void run_program();

  private:
    std::array<long long, MEMORY_SIZE> _memory {0};
};
