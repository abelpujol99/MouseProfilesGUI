#pragma once
#include "Frontend/UI/Helpers/IParentPosition.h"

class IClickable : public IParentPosition
{
public:

    ~IClickable() override = default;

    [[nodiscard]] virtual bool CanBeClicked() const = 0;

    virtual void Click() = 0;

    virtual void Subscribe() = 0;

    virtual void Unsubscribe() = 0;

};