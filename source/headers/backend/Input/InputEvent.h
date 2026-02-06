#pragma once

class InputEvent
{
public:

    InputEvent(unsigned short type, unsigned short code, int value);

    unsigned short GetType() const;

    unsigned short GetCode() const;

    int GetValue() const;

private:
    unsigned short _type;
    unsigned short _code;
    int _value;
};