//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once

#include "Emulator.h"
#include "FileAccess.h"
#include "Instruction.h"
#include "SymTab.h"

class Assembler
{
  public:
    Assembler(int argc, char* argv[]); // TODO: Change this to take filename
    ~Assembler(); // TODO: Remove destructor if it does nothing

    // Pass I - establish the locations of the symbols
    void pass_1();

    // Pass II - generate a translation
    void pass_2();

    void display_symbol_table() { _symbol_table.display_symbol_table(); }

    void run_program_in_emulator() const;

  private:
    FileAccess _instructions_file;
    SymbolTable _symbol_table;
    emulator _emulator;
};
