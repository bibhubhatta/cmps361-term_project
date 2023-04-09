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
     * @param a_filePath The path to the source file.
     */
    explicit FileAccess(const std::string& a_filePath);

    /**
     * @brief Closes the file.
     */
    ~FileAccess();

    /**
     * @brief Gets the current line from the source file.
     * @return The current line from the source file.
     */
    std::string getCurrentLine() const;

    /**
     * @brief Gets the next line from the source file.
     * @return The next line from the source file.
     */
    std::string getNextLine();

    /**
     * @brief Checks if the end of the file has been reached.
     * @return True if the end of the file has been reached, false otherwise.
     */
    [[nodiscard]] bool endOfFile() const { return m_sourceFile.eof(); };

    /**
     * @brief Rewinds the file pointer to the beginning of the file.
     */
    void rewind();

    /**
     * @brief Gets the current line number.
     * @return The current line number.
     */
    [[nodiscard]] inline int getCurrentLineNumber() const
    {
        return m_currentLineNumber;
    }

  private:
    std::ifstream m_sourceFile;
    int           m_currentLineNumber {0};
    std::string   m_currentLine;
};