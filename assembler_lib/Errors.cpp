#include <iostream>

#include "Errors.h"

std::vector<std::string> Errors::_error_messages;

void Errors::init_error_reporting() { _error_messages.clear(); }

void Errors::record_error(const std::string& message)
{
    _error_messages.push_back(message);
}

void Errors::display_errors()
{
    for (const auto& error : _error_messages)
    {
        std::cerr << error << std::endl;
    }
}