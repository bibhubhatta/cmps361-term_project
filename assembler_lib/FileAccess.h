/**
 * @file FileAccess.h
 * @brief File access class.
 * @details This class is responsible for opening and closing the source file.
 * It also provides a method to get the next line from the source file.
 */

#pragma once

#include <fstream>
#include <string>

/**
 * @brief File access class.
 * @details This class is responsible for opening and closing the source file.
 * It also provides a method to get the next line from the source file.
 */
class FileAccess
{
  public:
    /**
     * @brief Constructs a file access object.
     * @param a_FilePath The path to the source file.
     */
    explicit FileAccess(const std::string& a_FilePath);

    /**
     * @brief Closes the file.
     */
    ~FileAccess();

    /**
     * @brief Gets the current line from the source file.
     * @return The current line from the source file.
     */
    std::string GetCurrentLine() const;

    /**
     * @brief Gets the next line from the source file.
     * @return The next line from the source file.
     */
    std::string GetNextLine();

    /**
     * @brief Gets the previous line from the source file.
     * @return The previous line from the source file.
     */
    std::string GetPreviousLine() const;

    /**
     * @brief Checks if the end of the file has been reached.
     * @return True if the end of the file has been reached, false otherwise.
     */
    [[nodiscard]] bool EndOfFile() const { return m_SourceFile.eof(); };

    /**
     * @brief Rewinds the file pointer to the beginning of the file.
     */
    void rewind();

    /**
     * @brief Gets the current line number.
     * @return The current line number.
     */
    [[nodiscard]] inline int GetCurrentLineNumber() const
    {
        return m_CurrentLineNumber;
    }

    /**
     * @brief Gets the previous line number.
     * @return The previous line number.
     */
    [[nodiscard]] inline int GetPreviousLineNumber() const
    {
        return m_CurrentLineNumber - 1;
    }

  private:
    std::ifstream m_SourceFile;
    int           m_CurrentLineNumber {0};
    std::string   m_CurrentLine;
    std::string   m_PreviousLine;
};