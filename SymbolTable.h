//
//		Symbol table class.
//
#pragma once

#include <map>
#include <string>

// This class is our symbol table.
class SymbolTable
{
  public:
    SymbolTable() = default;
    ~SymbolTable() = default;

    const int MULTIPLEY_DEFINED_SYMBOL = -999;

    void add_symbol(const std::string& symbol, int location);

    void display_symbol_table() const;

    bool lookup_symbol(const std::string& symbol, int& location);

    int get_location(const std::string& symbol) const;

  private:
    // Maps symbols to location
    std::map<std::string, int, std::less<>> _symbol_table;

    [[nodiscard]] bool _in_table(const std::string& symbol) const;
};
