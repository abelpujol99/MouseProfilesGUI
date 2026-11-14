#pragma once

#include <cstdint>

class IInputTypeStrategy
{

public:

    virtual ~IInputTypeStrategy() = default;

    virtual void ChangeProfile(uint8_t profileIndex) = 0;
};