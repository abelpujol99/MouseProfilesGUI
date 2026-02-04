#pragma once

class IHoldState
{
public:

    virtual ~IHoldState() = default;

    virtual void Hold() = 0;

    virtual bool IsHolding() const = 0;
};