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
     * @brief Records instructions and data into simulated memory.
     * @param a_location The a_location in memory to record the a_contents.
     * @param a_contents The a_contents to record in memory.
     */
    void insert(int a_location, long long a_contents);

    /**
     * @brief Runs the program recorded in memory.
     */
    void runProgram();

  private:
    std::array<long long, MEMORY_SIZE> m_memory {0};
};
