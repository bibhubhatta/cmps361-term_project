#include <iostream>

#include "Errors.h"

std::vector<std::string> Errors::m_ErrorMessages;

void Errors::InitErrorReporting() { m_ErrorMessages.clear(); }

void Errors::RecordError(const std::string& a_Message)
{
    std::cerr << a_Message << '\n';
    m_ErrorMessages.push_back(a_Message);
}

void Errors::DisplayErrors()
{
    for (const auto& error : m_ErrorMessages)
    {
        std::cerr << error << std::endl;
    }
}

bool Errors::HasErrors()
{
    if (!m_ErrorMessages.empty())
    {
        return true;
    }
    return false;
}
