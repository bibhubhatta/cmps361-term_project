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
     * @brief Adds a symbol to the symbol table.
     * @param symbol The symbol to add.
     * @param location The location of the symbol.
     */
    void add_symbol(const std::string& symbol, int location);

    /**
     * @brief Displays the symbol table.
     */
    void display_symbol_table() const;

    /**
     * @brief Checks if a symbol is in the symbol table.
     * @param symbol The symbol to check.
     * @return True if the symbol is in the symbol table, false otherwise.
     */
    [[nodiscard]] bool lookup_symbol(const std::string& symbol, int& location);

    /**
     * @brief Gets the location of a symbol.
     * @param symbol The symbol to get the location of.
     * @return The location of the symbol.
     */
    [[nodiscard]] int get_location(const std::string& symbol) const;

  private:
    // Maps symbols to location
    std::map<std::string, int, std::less<>> _symbol_table;

    /**
     * @brief Checks if a symbol is in the symbol table.
     * @param symbol The symbol to check.
     * @return True if the symbol is in the symbol table, false otherwise.
     */
    [[nodiscard]] bool _in_table(const std::string& symbol) const;
};
