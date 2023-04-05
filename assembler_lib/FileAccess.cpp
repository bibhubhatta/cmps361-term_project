#include <iostream>

#include "FileAccess.h"

FileAccess::FileAccess(const std::string& file_path)
{
    _source_file.open(file_path, std::ios::in);

    if (!_source_file.is_open())
    {
        std::cerr << "Source file could not be opened, assembler terminated.\n";
        exit(1);
    }
}

FileAccess::~FileAccess() { _source_file.close(); }

std::string FileAccess::get_next_line()
{
    if (_source_file.eof())
    {
        std::cerr << "End of file.\n";
        exit(1);
    }

    std::string next_line;
    std::getline(_source_file, next_line);

    return next_line;
}

void FileAccess::rewind()
{
    // Clean all file flags and go back to the beginning of the file.
    _source_file.clear();
    _source_file.seekg(0, std::ios::beg);
}