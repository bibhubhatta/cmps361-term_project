//
// Created by bibhu on 3/27/2023.
//

#include <gtest/gtest.h>

#include "Assembler.h"
#include "Exceptions.h"
#include "HelperFunctions.h"
#include "SymbolicInstruction.h"

// 1. Multiply defined labels. (Reported after the offending statements.)
TEST(ErrorsTest, ThrowsMultiplyDefinedLabelsError)
{
    std::string source {" org 100\n"
                        "one dc 1\n"
                        "two dc 2\n"
                        "one dc 1\n"};

    std::string source_file_path {"multiply_defined_labels.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), MultiplyDefinedLabelError);
}

// 2. Undefined label. Namely, a symbolic operand does not have a matching a
// label.

// 3. Syntax error in construction of the label or operands. For example,
// a. the operand of a DS must be numeric and those of an ADD instruction must
// be symbolic.
TEST(ErrorsTest, ThrowsInvalidOperandTypeError1)
{
    std::string source {" org operand\n"};

    std::string source_file_path {"invalid_operand_type_symbolic.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), InvalidOperandTypeError);
}

// b. Labels and operand must meet the format given in the specifications.
TEST(ErrorsTest, ThrowsUnmatchedOperandCountError)
{
    std::string source {" org 100\n"
                        "one dc 1\n"
                        "two dc 2\n"
                        " add one \n"};

    std::string source_file_path {"unmatched_operand_count.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), UnmatchedOperandCountError);
}
TEST(ErrorsTest, ThrowsInvalidOperandTypeError2)
{
    std::string source {" add 2 3"};

    std::string source_file_path {"invalid_operand_type_numeric.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), InvalidOperandTypeError);
}
TEST(ErrorsTest, ThrowsInvalidOperandTypeError3)
{
    std::string source {" mult 2 asd"};

    std::string source_file_path {"invalid_operand_type_numeric_2.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), InvalidOperandTypeError);
}

// c. Extra statement elements.
TEST(ErrorsTest, ExtraStatementElementsError)
{
    std::string source {" add one two three\n"};

    std::string source_file_path {"extra_statement_elements.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), ExtraStatementElementsError);
}

// d. Illegal operation code.
TEST(ErrorsTest, ThrowsInvalidOpcodeError)
{
    std::string source {" invalid opcode\n"};

    std::string source_file_path {"invalid_operation_code.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), InvalidOpcodeError);
}

// 4. Insufficient memory for the translation.
TEST(ErrorsTest, ThrowsInsufficientMemoryError)
{
    std::string source {" org 100\n"};

    for (int i = 0; i < 100'000 - 100; i++)
    {
        source += " ds 1\n";
    }

    source += " dc 1\n";
    source += " end\n";

    std::string source_file_path {"insufficient_memory.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), InsufficientMemoryError);
}

// 5. Missing end statement or the end statement is not the last one in the
// program.
TEST(ErrorsTest, ThrowsMissingEndStatementError)
{
    std::string source {" org 100\n"
                        "one dc 1\n"
                        "two dc 2\n"};

    std::string source_file_path {"missing_end_statement.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), MissingEndStatementError);
}
TEST(ErrorsTest, ThrowsStatementAfterEndError)
{
    std::string source {" org 100\n"
                        "one dc 1\n"
                        "two dc 2\n"
                        " end\n"
                        " three dc 3\n"};

    std::string source_file_path {"statement_after_end.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), StatementAfterEndError);
}
TEST(ErrorsTest, DoesNotThrowStatementAfterEndError)
{
    std::string source {" org 100\n"
                        "one dc 1\n"
                        "two dc 2\n"
                        " end\n"
                        "\n"
                        "\t"};

    std::string source_file_path {"not_statement_after_end.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_NO_THROW(assembler.pass_1());
}

// 6. Constant too large for VC1620 memory. Missing or extra operands
TEST(ErrorsTest, ThrowsInvalidConstantSizeError)
{
    std::string source {" org 100\n"
                        "large_constant dc 100000\n"
                        " end\n"};

    std::string source_file_path {"constant_too_large.txt"};

    create_source_file(source, source_file_path);

    Assembler assembler {source_file_path};
    ASSERT_THROW(assembler.pass_1(), InvalidConstantSizeError);
}
