//
//		Implementation of the symbol table class.  This is the format I want for
// commenting functions.
//

#include <format>
#include <iostream>

#include "Exceptions.h"
#include "SymbolTable.h"

void SymbolTable::AddSymbol(const std::string& a_Symbol, int a_Location)
{
    if (m_InTable(a_Symbol))
    {
        int PreviousLocation {m_SymbolTable.at(a_Symbol)};

        m_SymbolTable[a_Symbol] = MULTIPLEY_DEFINED_SYMBOL;

        // If the a_Symbol is defined more than twice, the exception won't specify
        // the a_Location of the second definition because a_Location is set to
        // MULTIPLEY_DEFINED_SYMBOL.

        throw MultiplyDefinedLabelError(a_Symbol, PreviousLocation,
                                        a_Location);
    }

    m_SymbolTable[a_Symbol] = a_Location;
}

void SymbolTable::DisplaySymbolTable() const
{
    std::cout << std::format("{:<10}{:<10}{:<10}\n", // Set format
                             "Symbol #", "Symbol", "Location");

    int counter {0};
    for (const auto& [symbol, location] : m_SymbolTable)
    {
        std::cout << std::format("{:<10}{:<10}{:<10}\n", // Set format
                                 counter, symbol, location);
        ++counter;
    }
}

bool SymbolTable::m_InTable(const std::string& a_Symbol) const
{
    auto SymbolPointer {m_SymbolTable.find(a_Symbol)};
    return SymbolPointer != m_SymbolTable.end();
}

bool SymbolTable::LookupSymbol(const std::string& a_Symbol, int& a_Location)
{
    if (!m_InTable(a_Symbol))
    {
        return false;
    }

    a_Location = m_SymbolTable.at(a_Symbol);
    return true;
}

int SymbolTable::GetLocation(const std::string& a_Symbol) const
{
    if (!m_InTable(a_Symbol))
    {
        throw UndefinedLabelError(a_Symbol);
    }

    return m_SymbolTable.at(a_Symbol);
}
