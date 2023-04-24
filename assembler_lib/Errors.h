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
    static void InitErrorReporting();

    /**
     * @brief Records an error message.
     * @param a_Message The error message.
     */
    static void RecordError(const std::string& a_Message);

    /**
     * @brief Displays the collected error message.
     */
    static void DisplayErrors();

    /**
     * @brief Checks if any error has been reported.
     * @return True if there are errors, false otherwise.
     */
    static bool HasErrors();

  private:
    static std::vector<std::string> m_ErrorMessages;
};