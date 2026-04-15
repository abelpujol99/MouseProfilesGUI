#pragma once
#include "IPosition.h"

class IClickable : public IPosition
{
public:

    ~IClickable() override = default;

    [[nodiscard]] virtual bool CanBeClicked() const = 0;

    virtual void Click() = 0;

};