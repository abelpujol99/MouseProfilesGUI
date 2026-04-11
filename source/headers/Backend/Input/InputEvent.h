#pragma once

#include "Backend/CodeUsings.h"

class InputEvent
{
public:

    InputEvent(unsigned short type, Code code, int value);

    unsigned short GetType() const;

    Code GetCode() const;

    int GetValue() const;

private:
    unsigned short _type;
    Code _code;
    int _value;
};