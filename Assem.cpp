/*
 * Assembler main program.
 */

#include "Assembler.h"

int main(int argc, char* argv[])
{
    Assembler assem(argc, argv);

    // Establish the location of the labels:
    assem.pass_1();

    // Display the symbol table.
    assem.display_symbol_table();

    // Output the translation.
    assem.pass_2();

    // Run the emulator on the translation of the assembler language program
    // that was generated in Pass II.
    assem.run_program_in_emulator();

    // Terminate indicating all is well.  If there is an unrecoverable error,
    // the program will terminate at the point that it occurred with an exit(1)
    // call.
    return 0;
}