/*
 * Assembler main program.
 */
#include <iostream>

#include "Assembler.h"

/**
 * @brief Checks that there is exactly one run time parameter.
 * @param argc
 */
void check_argument_count(int argc)
{
    if (argc != 2)
    {
        std::cerr << "Usage: Assem <FileName>" << std::endl;
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    check_argument_count(argc);

    std::string source_file_path = argv[1];

    Assembler assem(source_file_path);

    // Establish the location of the labels:
    assem.pass_1();

    std::cout << "Symbol Table:\n\n";
    assem.display_symbol_table();
    std::cout
        << "___________________________________________________________\n\n";

    std::cout << "Translation of the Assembler Language Program:\n\n";
    assem.pass_2();
    std::cout
        << "___________________________________________________________\n\n";

    // Run the emulator on the translation of the assembler language program
    // that was generated in Pass II.
    assem.run_program_in_emulator();

    // Terminate indicating all is well.  If there is an unrecoverable error,
    // the program will terminate at the point that it occurred with an exit(1)
    // call.
    return 0;
}