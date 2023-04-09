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
    explicit InvalidOpcodeError(std::string a_opcode)
        : m_opcode(std::move(a_opcode)),
          m_message {std::format("Invalid a_opcode: '{}'", m_opcode)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_opcode;

    std::string m_message;
};

/**
 * @brief Exception thrown when label is defined more than once.
 */
class MultiplyDefinedLabelError : public std::exception
{
  public:
    explicit MultiplyDefinedLabelError(std::string a_label,
                                       int         a_previousLocation,
                                       int         a_newLocation)
        : m_label(std::move(a_label)), m_previousLocation(a_previousLocation),
          m_newLocation(a_newLocation),
          m_message {std::format(
              "Multiply defined a_label: '{}' at address {} and address {}",
              m_label, m_previousLocation, m_newLocation)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_label;
    int         m_previousLocation {0};
    int         m_newLocation {0};

    std::string m_message;
};

/**
 * @brief Exception thrown when an instruction has an invalid operand count.
 */
class UnmatchedOperandCountError : public std::exception
{
  public:
    explicit UnmatchedOperandCountError(std::string a_symbolicOpcode,
                                        int         a_expectedCount,
                                        int         a_actualCount)
        : m_symbolicOpcode(std::move(a_symbolicOpcode)),
          m_expectedCount(a_expectedCount), m_actualCount(a_actualCount),
          m_message {
              std::format("Unmatched operand count in '{}' expected {} but "
                          "found {}",
                          m_symbolicOpcode, m_expectedCount, m_actualCount)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_symbolicOpcode;
    int         m_expectedCount {0};
    int         m_actualCount {0};
    std::string m_message;
};

/**
 * @brief Exception thrown when an instruction has an invalid operand type.
 */
class InvalidOperandTypeError : public std::exception
{
  public:
    explicit InvalidOperandTypeError(std::string a_operand, OperandType a_expected,
                                     OperandType a_actual)
        : m_operand(std::move(a_operand)), m_expected(a_expected), m_actual(a_actual),
          m_message {std::format("Invalid a_operand type: '{}' a_expected {} but "
                                "found {}",
                                m_operand, getOperandTypeStr(m_expected),
                                getOperandTypeStr(m_actual))}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_operand;
    OperandType m_expected {OperandType::None};
    OperandType m_actual {OperandType::None};

    std::string m_message;
};

/**
 * @brief Exception thrown when an instruction has extra elements.
 */
class ExtraStatementElementsError : public std::exception
{
  public:
    explicit ExtraStatementElementsError(std::string a_statement,
                                         std::string a_extra)
        : m_statement(std::move(a_statement)), m_extra(std::move(a_extra)),
          m_message {
              std::format("Extra  element '{}' in '{}'", m_extra, m_statement)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_statement;
    std::string m_extra;

    std::string m_message;
};

/**
 * @brief Exception thrown when memory is insufficient to run the program.
 */
class InsufficientMemoryError : public std::exception
{
  public:
    explicit InsufficientMemoryError(int a_required, int a_available)
        : m_required(a_required), m_available(a_available),
          m_message {std::format("Insufficient memory a_required {} a_available {}",
                                m_required, m_available)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    int m_required {0};
    int m_available {0};

    std::string m_message;
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
        return m_message.c_str();
    }

  private:
    std::string m_message {"Missing END statement"};
};

/**
 * @brief Exception thrown when END statement is not the last statement.
 */
class StatementAfterEndError : public std::exception
{
  public:
    explicit StatementAfterEndError(std::string a_statement)
        : m_statement(std::move(a_statement)),
          m_message {std::format("Statement after END: '{}'", m_statement)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_statement;

    std::string m_message;
};

/**
 * @brief Exception thrown when a constant is not between 0 and 99,999.
 */
class InvalidConstantSizeError : public std::exception
{
  public:
    explicit InvalidConstantSizeError(std::string a_constant, int a_value)
        : m_constant(std::move(a_constant)), m_value(a_value),
          m_message {std::format("Invalid a_constant size: '{}' a_value {}. "
                                "Constant must be between 0 and 99,999",
                                m_constant, m_value)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_constant;
    int         m_value {0};

    std::string m_message;
};

/**
 * @brief Exception thrown when a label is not defined.
 */
class UndefinedLabelError : public std::exception
{
  public:
    explicit UndefinedLabelError(std::string a_label)
        : m_label(std::move(a_label)),
          m_message {std::format("Undefined a_label: '{}'", m_label)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_label;

    std::string m_message;
};

/**
 * @brief Exception thrown when a label is a symbolic opcode.
 */
class SymbolicOpcodeInLabelError : public std::exception
{
  public:
    explicit SymbolicOpcodeInLabelError(std::string a_label)
        : m_label(std::move(a_label)),
          m_message {std::format("Symbolic opcode in a_label: '{}'", m_label)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_label;

    std::string m_message;
};

/**
 * @brief Exception thrown when a label is too long.
 */
class LabelTooLongError : public std::exception
{
  public:
    explicit LabelTooLongError(std::string a_label)
        : m_label(std::move(a_label)),
          m_message {std::format("Label too long: '{}' ({} characters). "
                                "Maximum length is 10 characters.",
                                m_label, m_label.size())}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

  private:
    std::string m_label;

    std::string m_message;
};
