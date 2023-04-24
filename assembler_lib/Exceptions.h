/**
 * @file Exceptions.h
 * @brief Defines the exceptions thrown by the assembler.
 */

#pragma once

#include <exception>
#include <string>
#include <utility>

#include <format>

#include "HelperFunctions.h"

/**
 * @brief Exception thrown when an invalid opcode is encountered.
 */
class InvalidOpcodeError : public std::exception
{
  public:
    explicit InvalidOpcodeError(std::string a_Opcode)
        : m_Opcode(std::move(a_Opcode)),
          m_Message {std::format("Invalid opcode: '{}'", m_Opcode)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Opcode;

    std::string m_Message;
};

/**
 * @brief Exception thrown when label is defined more than once.
 */
class MultiplyDefinedLabelError : public std::exception
{
  public:
    explicit MultiplyDefinedLabelError(std::string a_Label,
                                       int         a_PreviousLocation,
                                       int         a_NewLocation)
        : m_Label(std::move(a_Label)), m_PreviousLocation(a_PreviousLocation),
          m_NewLocation(a_NewLocation),
          m_Message {std::format(
              "Multiply defined label: '{}' at address {} and address {}",
              m_Label, m_PreviousLocation, m_NewLocation)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Label;
    int         m_PreviousLocation {0};
    int         m_NewLocation {0};

    std::string m_Message;
};

/**
 * @brief Exception thrown when an instruction has an invalid operand count.
 */
class UnmatchedOperandCountError : public std::exception
{
  public:
    explicit UnmatchedOperandCountError(std::string a_SymbolicOpcode,
                                        int         a_ExpectedCount,
                                        int         a_ActualCount)
        : m_SymbolicOpcode(std::move(a_SymbolicOpcode)),
          m_ExpectedCount(a_ExpectedCount), m_ActualCount(a_ActualCount),
          m_Message {
              std::format("Unmatched operand count in '{}' expected {} but "
                          "found {}",
                          m_SymbolicOpcode, m_ExpectedCount, m_ActualCount)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_SymbolicOpcode;
    int         m_ExpectedCount {0};
    int         m_ActualCount {0};
    std::string m_Message;
};

/**
 * @brief Exception thrown when an instruction has an invalid operand type.
 */
class InvalidOperandTypeError : public std::exception
{
  public:
    explicit InvalidOperandTypeError(std::string a_Operand, OperandType a_Expected,
                                     OperandType a_Actual)
        : m_Operand(std::move(a_Operand)), m_Expected(a_Expected), m_Actual(a_Actual),
          m_Message {std::format("Invalid operand type: '{}' expected {} but "
                                "found {}",
                                m_Operand, GetOperandTypeStr(m_Expected),
                                GetOperandTypeStr(m_Actual))}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Operand;
    OperandType m_Expected {OperandType::None};
    OperandType m_Actual {OperandType::None};

    std::string m_Message;
};

/**
 * @brief Exception thrown when an instruction has extra elements.
 */
class ExtraStatementElementsError : public std::exception
{
  public:
    explicit ExtraStatementElementsError(std::string a_Statement,
                                         std::string a_Extra)
        : m_Statement(std::move(a_Statement)), m_Extra(std::move(a_Extra)),
          m_Message {
              std::format("Extra  element '{}' in '{}'", m_Extra, m_Statement)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Statement;
    std::string m_Extra;

    std::string m_Message;
};

/**
 * @brief Exception thrown when memory is insufficient to run the program.
 */
class InsufficientMemoryError : public std::exception
{
  public:
    explicit InsufficientMemoryError(int a_Required, int a_Available)
        : m_Required(a_Required), m_Available(a_Available),
          m_Message {std::format("Insufficient memory required {} available {}",
                                m_Required, m_Available)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    int m_Required {0};
    int m_Available {0};

    std::string m_Message;
};

/**
 * @brief Exception thrown when END statement is missing.
 */
class MissingEndStatementError : public std::exception
{
  public:
    MissingEndStatementError() = default;
    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Message {"Missing END statement"};
};

/**
 * @brief Exception thrown when END statement is not the last statement.
 */
class StatementAfterEndError : public std::exception
{
  public:
    explicit StatementAfterEndError(std::string a_Statement)
        : m_Statement(std::move(a_Statement)),
          m_Message {std::format("Statement after END: '{}'", m_Statement)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Statement;

    std::string m_Message;
};

/**
 * @brief Exception thrown when a constant is not between 0 and 99,999.
 */
class InvalidConstantSizeError : public std::exception
{
  public:
    explicit InvalidConstantSizeError(std::string a_Constant, int a_Value)
        : m_Constant(std::move(a_Constant)), m_Value(a_Value),
          m_Message {std::format("Invalid constant size: '{}' value {}. "
                                "Constant must be between 0 and 99,999",
                                m_Constant, m_Value)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Constant;
    int         m_Value {0};

    std::string m_Message;
};

/**
 * @brief Exception thrown when a label is not defined.
 */
class UndefinedLabelError : public std::exception
{
  public:
    explicit UndefinedLabelError(std::string a_Label)
        : m_Label(std::move(a_Label)),
          m_Message {std::format("Undefined label: '{}'", m_Label)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Label;

    std::string m_Message;
};

/**
 * @brief Exception thrown when a label is a symbolic opcode.
 */
class SymbolicOpcodeInLabelError : public std::exception
{
  public:
    explicit SymbolicOpcodeInLabelError(std::string a_Label)
        : m_Label(std::move(a_Label)),
          m_Message {std::format("Symbolic opcode in label: '{}'", m_Label)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Label;

    std::string m_Message;
};

/**
 * @brief Exception thrown when a label is too long.
 */
class LabelTooLongError : public std::exception
{
  public:
    explicit LabelTooLongError(std::string a_Label)
        : m_Label(std::move(a_Label)),
          m_Message {std::format("Label too long: '{}' ({} characters). "
                                "Maximum length is 10 characters.",
                                m_Label, m_Label.size())}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_Message.c_str();
    }

  private:
    std::string m_Label;

    std::string m_Message;
};
