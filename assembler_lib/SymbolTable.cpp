//
//		Implementation of the symbol table class.  This is the format I want for
// commenting functions.
//

#include <format>
#include <iostream>

#include "Exceptions.h"
#include "SymbolTable.h"

void SymbolTable::addSymbol(const std::string& a_symbol, int a_location)
{
    if (m_inTable(a_symbol))
    {
        int previousLocation {m_symbolTable.at(a_symbol)};

        m_symbolTable[a_symbol] = MULTIPLEY_DEFINED_SYMBOL;

        // If the a_symbol is defined more than twice, the exception won't specify
        // the a_location of the second definition because a_location is set to
        // MULTIPLEY_DEFINED_SYMBOL.

        throw MultiplyDefinedLabelError(a_symbol, previousLocation,
                                        a_location);
    }

    m_symbolTable[a_symbol] = a_location;
}

void SymbolTable::displaySymbolTable() const
{
    std::cout << std::format("{:<10}{:<10}{:<10}\n", // Set format
                             "Symbol #", "Symbol", "Location");

    int counter {0};
    for (const auto& [symbol, location] : m_symbolTable)
    {
        std::cout << std::format("{:<10}{:<10}{:<10}\n", // Set format
                                 counter, symbol, location);
        ++counter;
    }
}

bool SymbolTable::m_inTable(const std::string& a_symbol) const
{
    auto symbolPointer {m_symbolTable.find(a_symbol)};
    return symbolPointer != m_symbolTable.end();
}

bool SymbolTable::lookupSymbol(const std::string& a_symbol, int& a_location)
{
    if (!m_inTable(a_symbol))
    {
        return false;
    }

    a_location = m_symbolTable.at(a_symbol);
    return true;
}

int SymbolTable::getLocation(const std::string& a_symbol) const
{
    if (!m_inTable(a_symbol))
    {
        throw UndefinedLabelError(a_symbol);
    }

    return m_symbolTable.at(a_symbol);
}
