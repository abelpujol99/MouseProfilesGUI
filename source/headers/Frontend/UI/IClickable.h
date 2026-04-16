#pragma once
#include "IParentPosition.h"

class IClickable : public IParentPosition
{
public:

    ~IClickable() override = default;

    [[nodiscard]] virtual bool CanBeClicked() const = 0;

    virtual void Click() = 0;

};