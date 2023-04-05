//
//		Implementation of the symbol table class.  This is the format I want for
// commenting functions.
//

#include <fmt/core.h>
#include <iostream>

#include "Exceptions.h"
#include "SymbolTable.h"

void SymbolTable::add_symbol(const std::string& symbol, int location)
{
    if (_in_table(symbol))
    {
        int previous_location {_symbol_table.at(symbol)};

        _symbol_table[symbol] = MULTIPLEY_DEFINED_SYMBOL;

        // If the symbol is defined more than twice, the exception won't specify
        // the location of the second definition because location is set to
        // MULTIPLEY_DEFINED_SYMBOL.

        throw MultiplyDefinedLabelError(symbol, previous_location, location);
    }

    _symbol_table[symbol] = location;
}

void SymbolTable::display_symbol_table() const
{
    std::cout << fmt::format("{:<10}{:<10}{:<10}\n", // Set format
                             "Symbol #", "Symbol", "Location");

    int counter {0};
    for (const auto& [symbol, location] : _symbol_table)
    {
        std::cout << fmt::format("{:<10}{:<10}{:<10}\n", // Set format
                                 counter, symbol, location);
        ++counter;
    }
}

bool SymbolTable::_in_table(const std::string& symbol) const
{
    auto symbol_pointer {_symbol_table.find(symbol)};
    return symbol_pointer != _symbol_table.end();
}

bool SymbolTable::lookup_symbol(const std::string& symbol, int& location)
{
    if (!_in_table(symbol))
    {
        return false;
    }

    location = _symbol_table.at(symbol);
    return true;
}

int SymbolTable::get_location(const std::string& symbol) const
{
    if (!_in_table(symbol))
    {
        throw UndefinedLabelError(symbol);
    }

    return _symbol_table.at(symbol);
}
