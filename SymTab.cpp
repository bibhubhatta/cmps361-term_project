//
//		Implementation of the symbol table class.  This is the format I want for
// commenting functions.
//

#include <iomanip>
#include <iostream>

#include "SymTab.h"

void SymbolTable::add_symbol(const std::string& symbol, int location)
{
    if (_in_table(symbol))
    {
        _symbol_table[symbol] = MULTIPLEY_DEFINED_SYMBOL;
        return;
    }

    _symbol_table[symbol] = location;
}

void SymbolTable::display_symbol_table() const
{
    std::cout << std::setw(10) << std::left << "Symbol #"          // Column 1
              << std::setw(10) << std::left << "Symbol"            // Column 2
              << std::setw(10) << std::left << "Location" << '\n'; // Column 3

    int counter{0};
    for (const auto& [symbol, location] : _symbol_table)
    {
        std::cout << std::setw(10) << std::left << counter++ // Column 1
                  << std::setw(10) << std::left << symbol    // Column 2
                  << std::setw(10) << std::left << location << '\n';
    }
}

bool SymbolTable::_in_table(const std::string& symbol) const
{
    auto symbol_pointer{_symbol_table.find(symbol)};
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
