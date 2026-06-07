#include "../../headers/Input/InputEvent.h"

InputEvent::InputEvent(unsigned short type, unsigned short code, int value) : _type(type), _code(code), _value(value)
{}

unsigned short InputEvent::GetType() const
{
    return _type;
}

unsigned short InputEvent::GetCode() const
{
    return _code;
}

int InputEvent::GetValue() const
{
    return _value;
}