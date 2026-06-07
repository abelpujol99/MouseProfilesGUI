#pragma once

#include "CodeUsings.h"

class InputEvent
{
public:

    InputEvent(unsigned short type, Code code, int value);

    [[nodiscard]] unsigned short GetType() const;

    [[nodiscard]] Code GetCode() const;

    [[nodiscard]] int GetValue() const;

private:
    unsigned short _type;
    Code _code;
    int _value;
};