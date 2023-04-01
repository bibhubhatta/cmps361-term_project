#pragma once

#include <exception>
#include <fmt/core.h>
#include <string>
#include <utility>

#include "HelperFunctions.h"

class InvalidOpcodeError : public std::exception
{
  public:
    explicit InvalidOpcodeError(std::string opcode)
        : _opcode(std::move(opcode)), _message {fmt::format(
                                          "Invalid opcode: '{}'", _opcode)}
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

class MultiplyDefinedLabelError : public std::exception
{
  public:
    explicit MultiplyDefinedLabelError(std::string label, int previous_location,
                                       int new_location)
        : _label(std::move(label)), _previous_location(previous_location),
          _new_location(new_location),
          _message {fmt::format("Multiply defined label: {} at {} and {}",
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

class UnmatchedOperandCountError : public std::exception
{
  public:
    explicit UnmatchedOperandCountError(std::string symbolic_opcode,
                                        int expected_count, int actual_count)
        : _symbolic_opcode(std::move(symbolic_opcode)),
          _expected_count(expected_count), _actual_count(actual_count),
          _message {fmt::format("Unmatched operand count in {} expected {} but "
                                "found {}",
                                _symbolic_opcode, _expected_count,
                                _actual_count)}
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

class InvalidOperandTypeError : public std::exception
{
  public:
    explicit InvalidOperandTypeError(std::string operand, OperandType expected,
                                     OperandType actual)
        : _operand(std::move(operand)), _expected(expected),
          _actual(actual), _message {fmt::format(
                               "Invalid operand type: '{}' expected {} but "
                               "found {}",
                               _operand, get_operand_type_str(_expected),
                               get_operand_type_str(_actual))}
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        std::string expected {get_operand_type_str(_expected)};
        std::string actual {get_operand_type_str(_actual)};

        return _message.c_str();
    }

  private:
    std::string _operand;
    OperandType _expected {OperandType::None};
    OperandType _actual {OperandType::None};

    std::string _message;
};

class ExtraStatementElementsError : public std::exception
{
  public:
    explicit ExtraStatementElementsError(std::string statement,
                                         std::string extra)
        : _statement(std::move(statement)),
          _extra(std::move(extra)), _message {fmt::format(
                                        "Extra  element '{}' in '{}'", _extra,
                                        _statement)}
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

class InsufficientMemoryError : public std::exception
{
  public:
    explicit InsufficientMemoryError(int required, int available)
        : _required(required), _available(available),
          _message {fmt::format("Insufficient memory required {} available {}",
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