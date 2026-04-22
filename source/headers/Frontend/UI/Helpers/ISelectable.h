#pragma once

#include "IParentPosition.h"

class ISelectable : public IParentPosition
{
public:

    ~ISelectable() override = default;

    virtual bool CanBeSelected() = 0;

    virtual void OnSelect() = 0;

    virtual void OnUnselect() = 0;
};