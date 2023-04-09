#include <iostream>

#include "FileAccess.h"

FileAccess::FileAccess(const std::string& a_filePath)
{
    m_sourceFile.open(a_filePath, std::ios::in);

    if (!m_sourceFile.is_open())
    {
        std::cerr << "Source file could not be opened, assembler terminated.\n";
        exit(1);
    }
}

FileAccess::~FileAccess() { m_sourceFile.close(); }

std::string FileAccess::getNextLine()
{
    m_currentLineNumber++;

    if (m_sourceFile.eof())
    {
        std::cerr << "End of file.\n";
        exit(1);
    }

    std::string nextLine;
    std::getline(m_sourceFile, nextLine);

    m_currentLine = nextLine;

    return nextLine;
}

void FileAccess::rewind()
{
    // Clean all file flags and go back to the beginning of the file.
    m_sourceFile.clear();
    m_sourceFile.seekg(0, std::ios::beg);
    m_currentLineNumber = 0;
}
std::string FileAccess::getCurrentLine() const { return m_currentLine; }
