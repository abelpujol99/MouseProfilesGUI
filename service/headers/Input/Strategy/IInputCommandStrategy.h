#pragma once

#include <cstdint>

class IInputCommandStrategy
{

public:

    virtual ~IInputCommandStrategy() = default;

    virtual void ChangeProfile(uint8_t profileIndex) = 0;
};