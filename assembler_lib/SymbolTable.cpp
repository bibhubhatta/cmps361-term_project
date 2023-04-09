//
//		Implementation of the symbol table class.  This is the format I want for
// commenting functions.
//

#include <format>
#include <iostream>

#include "Exceptions.h"
#include "SymbolTable.h"

void SymbolTable::add_symbol(const std::string& a_symbol, int a_location)
{
    if (_in_table(a_symbol))
    {
        int previous_location {_symbol_table.at(a_symbol)};

        _symbol_table[a_symbol] = MULTIPLEY_DEFINED_SYMBOL;

        // If the a_symbol is defined more than twice, the exception won't specify
        // the a_location of the second definition because a_location is set to
        // MULTIPLEY_DEFINED_SYMBOL.

        throw MultiplyDefinedLabelError(a_symbol, previous_location,
                                        a_location);
    }

    _symbol_table[a_symbol] = a_location;
}

void SymbolTable::display_symbol_table() const
{
    std::cout << std::format("{:<10}{:<10}{:<10}\n", // Set format
                             "Symbol #", "Symbol", "Location");

    int counter {0};
    for (const auto& [symbol, location] : _symbol_table)
    {
        std::cout << std::format("{:<10}{:<10}{:<10}\n", // Set format
                                 counter, symbol, location);
        ++counter;
    }
}

bool SymbolTable::_in_table(const std::string& a_symbol) const
{
    auto symbol_pointer {_symbol_table.find(a_symbol)};
    return symbol_pointer != _symbol_table.end();
}

bool SymbolTable::lookup_symbol(const std::string& a_symbol, int& a_location)
{
    if (!_in_table(a_symbol))
    {
        return false;
    }

    a_location = _symbol_table.at(a_symbol);
    return true;
}

int SymbolTable::get_location(const std::string& a_symbol) const
{
    if (!_in_table(a_symbol))
    {
        throw UndefinedLabelError(a_symbol);
    }

    return _symbol_table.at(a_symbol);
}
