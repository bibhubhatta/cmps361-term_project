/*
 * Assembler main program.
 */
#include <iostream>

#include "Assembler.h"
#include "Errors.h"

/**
 * @brief Checks that there is exactly one run time parameter.
 * @param argc
 */
void CheckArgumentCount(int argc)
{
    if (argc != 2)
    {
        std::cerr << "Usage: Assem <FileName>" << std::endl;
        exit(1);
    }
}

/**
 * @brief Displays the symbol table.
 * @param assem instance of the Assembler class.
 */
void DisplaySymbolTable(const Assembler& assem)
{
    std::cout << "Symbol Table:\n\n";
    assem.displaySymbolTable();
    std::cout << "________________________________________________________\n\n";
}

/**
 * @brief Displays the translation of the Assembler Language Program.
 * @param assem the assembler.
 */
void DisplayTranslation(Assembler& assem)
{
    std::cout << "Translation of the Assembler Language Program:\n\n";
    assem.pass2();
    std::cout << "________________________________________________________\n\n";
}

/**
 * @brief Prompts user to press enter to continue.
 */
void PressEnterToContinue()
{
    std::cout << "Press enter to continue...";
    std::cin.get();
    std::cout << std::endl;
}

/**
 * @brief Main program.
 * @param argc number of command line arguments.
 * @param argv array of command line arguments.
 * @return 0 if all is well, 1 if there is an unrecoverable error.
 */
int main(int argc, char* argv[])
{
    try
    {
        CheckArgumentCount(argc);

        std::string sourceFilePath = argv[1];

        Errors::initErrorReporting();

        Assembler assem(sourceFilePath);

        assem.pass1();

        DisplaySymbolTable(assem);
        PressEnterToContinue();

        DisplayTranslation(assem);
        // Display the errors that were encountered during the translation.
        Errors::displayErrors();

        PressEnterToContinue();

        // Run the emulator on the translation of the assembler language program
        // that was generated in Pass II.
        std::cout << "\nResults from emulating program:\n\n";
        assem.runProgramInEmulator();
        std::cout << "\nEnd of emulation\n\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    // Terminate indicating all is well.  If there is an unrecoverable error,
    // the program will terminate at the point that it occurred with an exit(1)
    // call.
    return 0;
}