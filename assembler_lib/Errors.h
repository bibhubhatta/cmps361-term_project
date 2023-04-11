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
     * @brief Records an error a_Message.
     * @param a_Message The error a_Message.
     */
    static void RecordError(const std::string& a_Message);

    /**
     * @brief Displays the collected error message.
     */
    static void DisplayErrors();

  private:
    static std::vector<std::string> m_ErrorMessages;
};