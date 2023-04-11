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
     * @brief Adds a a_Symbol to the a_Symbol table.
     * @param a_Symbol The a_Symbol to add.
     * @param a_Location The a_Location of the a_Symbol.
     */
    void AddSymbol(const std::string& a_Symbol, int a_Location);

    /**
     * @brief Displays the symbol table.
     */
    void DisplaySymbolTable() const;

    /**
     * @brief Checks if a a_Symbol is in the a_Symbol table.
     * @param a_Symbol The a_Symbol to check.
     * @return True if the a_Symbol is in the a_Symbol table, false otherwise.
     */
    [[nodiscard]] bool LookupSymbol(const std::string& a_Symbol,
                                     int&               a_Location);

    /**
     * @brief Gets the location of a a_Symbol.
     * @param a_Symbol The a_Symbol to get the location of.
     * @return The location of the a_Symbol.
     */
    [[nodiscard]] int GetLocation(const std::string& a_Symbol) const;

  private:
    // Maps symbols to location
    std::map<std::string, int, std::less<>> m_SymbolTable;

    /**
     * @brief Checks if a a_Symbol is in the a_Symbol table.
     * @param a_Symbol The a_Symbol to check.
     * @return True if the a_Symbol is in the a_Symbol table, false otherwise.
     */
    [[nodiscard]] bool m_InTable(const std::string& a_Symbol) const;
};
