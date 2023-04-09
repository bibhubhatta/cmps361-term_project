/**
 * @file SymbolTable.h
 * @brief SymbolTable class declaration.
 */

#pragma once

#include <map>
#include <string>

/**
 * @brief SymbolTable class.
 * @details This class represents a symbol table. It is used to store the
 * symbols and their locations.
 */
class SymbolTable
{
  public:
    /**
     * @brief Constructs a symbol table object.
     */
    SymbolTable() = default;

    /**
     * @brief Default destructor.
     */
    ~SymbolTable() = default;

    const int MULTIPLEY_DEFINED_SYMBOL = -999;

    /**
     * @brief Adds a a_symbol to the a_symbol table.
     * @param a_symbol The a_symbol to add.
     * @param a_location The a_location of the a_symbol.
     */
    void addSymbol(const std::string& a_symbol, int a_location);

    /**
     * @brief Displays the symbol table.
     */
    void displaySymbolTable() const;

    /**
     * @brief Checks if a a_symbol is in the a_symbol table.
     * @param a_symbol The a_symbol to check.
     * @return True if the a_symbol is in the a_symbol table, false otherwise.
     */
    [[nodiscard]] bool lookupSymbol(const std::string& a_symbol,
                                     int&               a_location);

    /**
     * @brief Gets the location of a a_symbol.
     * @param a_symbol The a_symbol to get the location of.
     * @return The location of the a_symbol.
     */
    [[nodiscard]] int getLocation(const std::string& a_symbol) const;

  private:
    // Maps symbols to location
    std::map<std::string, int, std::less<>> m_symbolTable;

    /**
     * @brief Checks if a a_symbol is in the a_symbol table.
     * @param a_symbol The a_symbol to check.
     * @return True if the a_symbol is in the a_symbol table, false otherwise.
     */
    [[nodiscard]] bool m_inTable(const std::string& a_symbol) const;
};
