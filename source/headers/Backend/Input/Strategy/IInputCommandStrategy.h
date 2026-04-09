#pragma once

class IInputCommandStrategy
{

public:

    virtual ~IInputCommandStrategy() = default;

    virtual void ChangeProfile(int profileIndex) = 0;

    virtual void RegisterValue(int value) = 0;
};