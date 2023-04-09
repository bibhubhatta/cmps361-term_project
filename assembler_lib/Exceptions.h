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
    explicit InvalidOpcodeError(std::string opcode)
        : _opcode(std::move(opcode)),
          _message {std::format("Invalid opcode: '{}'", _opcode)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _opcode;

    std::string _message;
};

/**
 * @brief Exception thrown when label is defined more than once.
 */
class MultiplyDefinedLabelError : public std::exception
{
  public:
    explicit MultiplyDefinedLabelError(std::string label, int previous_location,
                                       int new_location)
        : _label(std::move(label)), _previous_location(previous_location),
          _new_location(new_location),
          _message {std::format(
              "Multiply defined label: '{}' at address {} and address {}",
              _label, _previous_location, _new_location)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _label;
    int         _previous_location {0};
    int         _new_location {0};

    std::string _message;
};

/**
 * @brief Exception thrown when an instruction has an invalid operand count.
 */
class UnmatchedOperandCountError : public std::exception
{
  public:
    explicit UnmatchedOperandCountError(std::string symbolic_opcode,
                                        int expected_count, int actual_count)
        : _symbolic_opcode(std::move(symbolic_opcode)),
          _expected_count(expected_count), _actual_count(actual_count),
          _message {
              std::format("Unmatched operand count in '{}' expected {} but "
                          "found {}",
                          _symbolic_opcode, _expected_count, _actual_count)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _symbolic_opcode;
    int         _expected_count {0};
    int         _actual_count {0};
    std::string _message;
};

/**
 * @brief Exception thrown when an instruction has an invalid operand type.
 */
class InvalidOperandTypeError : public std::exception
{
  public:
    explicit InvalidOperandTypeError(std::string operand, OperandType expected,
                                     OperandType actual)
        : _operand(std::move(operand)), _expected(expected), _actual(actual),
          _message {std::format("Invalid operand type: '{}' expected {} but "
                                "found {}",
                                _operand, get_operand_type_str(_expected),
                                get_operand_type_str(_actual))}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _operand;
    OperandType _expected {OperandType::None};
    OperandType _actual {OperandType::None};

    std::string _message;
};

/**
 * @brief Exception thrown when an instruction has extra elements.
 */
class ExtraStatementElementsError : public std::exception
{
  public:
    explicit ExtraStatementElementsError(std::string statement,
                                         std::string extra)
        : _statement(std::move(statement)), _extra(std::move(extra)),
          _message {
              std::format("Extra  element '{}' in '{}'", _extra, _statement)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _statement;
    std::string _extra;

    std::string _message;
};

/**
 * @brief Exception thrown when memory is insufficient to run the program.
 */
class InsufficientMemoryError : public std::exception
{
  public:
    explicit InsufficientMemoryError(int required, int available)
        : _required(required), _available(available),
          _message {std::format("Insufficient memory required {} available {}",
                                _required, _available)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    int _required {0};
    int _available {0};

    std::string _message;
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
        return _message.c_str();
    }

  private:
    std::string _message {"Missing END statement"};
};

/**
 * @brief Exception thrown when END statement is not the last statement.
 */
class StatementAfterEndError : public std::exception
{
  public:
    explicit StatementAfterEndError(std::string statement)
        : _statement(std::move(statement)),
          _message {std::format("Statement after END: '{}'", _statement)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _statement;

    std::string _message;
};

/**
 * @brief Exception thrown when a constant is not between 0 and 99,999.
 */
class InvalidConstantSizeError : public std::exception
{
  public:
    explicit InvalidConstantSizeError(std::string constant, int value)
        : _constant(std::move(constant)), _value(value),
          _message {std::format("Invalid constant size: '{}' value {}. "
                                "Constant must be between 0 and 99,999",
                                _constant, _value)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _constant;
    int         _value {0};

    std::string _message;
};

/**
 * @brief Exception thrown when a label is not defined.
 */
class UndefinedLabelError : public std::exception
{
  public:
    explicit UndefinedLabelError(std::string label)
        : _label(std::move(label)),
          _message {std::format("Undefined label: '{}'", _label)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _label;

    std::string _message;
};

/**
 * @brief Exception thrown when a label is a symbolic opcode.
 */
class SymbolicOpcodeInLabelError : public std::exception
{
  public:
    explicit SymbolicOpcodeInLabelError(std::string label)
        : _label(std::move(label)),
          _message {std::format("Symbolic opcode in label: '{}'", _label)}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _label;

    std::string _message;
};

/**
 * @brief Exception thrown when a label is too long.
 */
class LabelTooLongError : public std::exception
{
  public:
    explicit LabelTooLongError(std::string label)
        : _label(std::move(label)),
          _message {std::format("Label too long: '{}' ({} characters). "
                                "Maximum length is 10 characters.",
                                _label, _label.size())}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

  private:
    std::string _label;

    std::string _message;
};
