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
     * @param a_Location The location in memory to record the a_Contents.
     * @param a_Contents The contents to record in memory.
     */
    void insert(int a_Location, long long a_Contents);

    /**
     * @brief Runs the program recorded in memory.
     */
    void RunProgram();

  private:
    std::array<long long, MEMORY_SIZE> m_Memory {0};
};
