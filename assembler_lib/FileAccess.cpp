#include <iostream>

#include "FileAccess.h"

FileAccess::FileAccess(const std::string& a_FilePath)
{
    m_SourceFile.open(a_FilePath, std::ios::in);

    if (!m_SourceFile.is_open())
    {
        std::cerr << "Source file could not be opened, assembler terminated.\n";
        exit(1);
    }
}

FileAccess::~FileAccess() { m_SourceFile.close(); }

std::string FileAccess::GetNextLine()
{
    m_CurrentLineNumber++;

    if (m_SourceFile.eof())
    {
        std::cerr << "End of file.\n";
        exit(1);
    }

    std::string NextLine;
    std::getline(m_SourceFile, NextLine);

    m_PreviousLine = m_CurrentLine;
    m_CurrentLine = NextLine;

    return NextLine;
}

void FileAccess::rewind()
{
    // Clean all file flags and go back to the beginning of the file.
    m_SourceFile.clear();
    m_SourceFile.seekg(0, std::ios::beg);
    m_CurrentLineNumber = 0;
}

std::string FileAccess::GetCurrentLine() const { return m_CurrentLine; }

std::string FileAccess::GetPreviousLine() const { return m_PreviousLine; }
