#include <iostream>

#include "Errors.h"

std::vector<std::string> Errors::m_errorMessages;

void Errors::initErrorReporting() { m_errorMessages.clear(); }

void Errors::recordError(const std::string& a_message)
{
    m_errorMessages.push_back(a_message);
}

void Errors::displayErrors()
{
    for (const auto& error : m_errorMessages)
    {
        std::cerr << error << std::endl;
    }
}