/**
 * @file Emulator.h
 * @brief The emulator class.
 * @details This class is responsible for emulating the VC1620.
 */

#pragma once

#include <array>

/**
 * @brief The emulator class.
 * @details This class is responsible for emulating the VC1620.
 */
class Emulator
{
  public:
    const static int MEMORY_SIZE = 100'000;

    /**
     * @brief Constructs an emulator object.
     */
    Emulator() = default;
    ~Emulator() = default;

    /**
     * @brief Sets the origin of the instructions in the memory.
     * @param instruction_origin The origin of the instructions.
     */
    void set_instruction_origin(int instruction_origin);

    /**
     * @brief Records instructions and data into simulated memory.
     * @param location The location in memory to record the contents.
     * @param contents The contents to record in memory.
     */
    void insert(int location, long long contents);

    /**
     * @brief Runs the program recorded in memory.
     */
    void run_program();

  private:
    std::array<long long, MEMORY_SIZE> _memory {0};

    int _instruction_origin {0};
};
