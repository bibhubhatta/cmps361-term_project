//
// Created by bibhu on 3/27/2023.
//

#include <gtest/gtest.h>

#include "Assembler.h"
#include "Exceptions.h"
#include "SymbolicInstruction.h"

// Test the following errors:
// 1. Multiply defined labels. (Reported after the offending statements.)
// 2. Undefined label. Namely, a symbolic operand does not have a matching a
// label.
// 3. Syntax error in construction of the label or operands. For example,
// the operand of a DS must be numeric and those of an ADD instruction must be
// symbolic. Labels and operand must meet the format given in the
// specifications. Extra statement elements. Illegal operation code.
// 4. Insufficient memory for the translation.
// 5. Missing end statement or the end statement is not the last one in the
// program. Constant too large for VC1620 memory. Missing or extra operands

TEST(ErrorsTest, ThrowsMultiplyDefinedLabelsError)
{
    std::string source {" org 100\n"
                        "one dc 1\n"
                        "two dc 2\n"
                        "one dc 1\n"};

    std::string source_file_path {"multiply_defined_labels.txt"};

    std::ofstream source_file {source_file_path};
    source_file << source;
    source_file.close();

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), MultiplyDefinedLabelError);
}

TEST(ErrorsTest, ThrowsUnmatchedOperandCountError)
{
    std::string source {" org 100\n"
                        "one dc 1\n"
                        "two dc 2\n"
                        " add one \n"};

    std::string source_file_path {"unmatched_operand_count.txt"};

    std::ofstream source_file {source_file_path};
    source_file << source;
    source_file.close();

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), UnmatchedOperandCountError);
}