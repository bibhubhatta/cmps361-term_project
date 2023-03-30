#pragma once

#include <exception>
#include <format>
#include <string>
#include <utility>

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