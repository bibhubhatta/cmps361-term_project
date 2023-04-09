/**
 * @file Errors.h
 * @brief Error reporting class.
 * @details This class is responsible for collecting and displaying error
 * messages.
 */

#pragma once

#include <string>
#include <vector>

class Errors
{
  public:
    /**
     * @brief Initializes error reports.
     */
    static void initErrorReporting();

    /**
     * @brief Records an error a_message.
     * @param a_message The error a_message.
     */
    static void recordError(const std::string& a_message);

    /**
     * @brief Displays the collected error message.
     */
    static void displayErrors();

  private:
    static std::vector<std::string> m_errorMessages;
};