#pragma once

#include <exception>
#include <format>
#include <string>
#include <utility>

class InvalidOpcodeError : public std::exception
{
  public:
    explicit InvalidOpcodeError(std::string opcode) : _opcode(std::move(opcode))
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        std::string message {std::format("Invalid opcode: {}", _opcode)};

        return message.c_str();
    }

  private:
    std::string _opcode;
};

class MultiplyDefinedLabelError : public std::exception
{
  public:
    explicit MultiplyDefinedLabelError(std::string label, int previous_location,
                                       int new_location)
        : _label(std::move(label)), _previous_location(previous_location),
          _new_location(new_location)
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        std::string message {
            std::format("Multiply defined label: {} at {} and {}", _label,
                        _previous_location, _new_location)};

        return message.c_str();
    }

  private:
    std::string _label;
    int         _previous_location {0};
    int         _new_location {0};
};

class UnmatchedOperandCountError : public std::exception
{
  public:
    explicit UnmatchedOperandCountError(std::string symbolic_opcode,
                                        int expected_count, int actual_count)
        : _symbolic_opcode(std::move(symbolic_opcode)),
          _expected_count(expected_count), _actual_count(actual_count)
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        std::string message {
            std::format("Unmatched operand count for label: {} expected {} but "
                        "found {}",
                        _symbolic_opcode, _expected_count, _actual_count)};

        return message.c_str();
    }

  private:
    std::string _symbolic_opcode;
    int         _expected_count {0};
    int         _actual_count {0};
};