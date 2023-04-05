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
     * @param file_path The path to the source file.
     */
    explicit FileAccess(const std::string& file_path);

    /**
     * @brief Closes the file.
     */
    ~FileAccess();

    /**
     * @brief Gets the next line from the source file.
     * @return The next line from the source file.
     */
    std::string get_next_line();

    /**
     * @brief Checks if the end of the file has been reached.
     * @return True if the end of the file has been reached, false otherwise.
     */
    [[nodiscard]] bool end_of_file() const { return _source_file.eof(); };

    /**
     * @brief Rewinds the file pointer to the beginning of the file.
     */
    void rewind();

  private:
    std::ifstream _source_file;
};