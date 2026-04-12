#pragma once

class IHoldState
{
public:

    virtual ~IHoldState() = default;

    virtual void Hold() = 0;

    [[nodiscard]] virtual bool IsHolding() const = 0;
};