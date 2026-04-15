#pragma once

#include "Frontend/UI/IPosition.h"

class ISelectable : public IPosition
{
public:

    ~ISelectable() override = default;

    virtual bool CanBeSelected() = 0;

    virtual void OnSelect() = 0;

    virtual void OnUnselect() = 0;
};