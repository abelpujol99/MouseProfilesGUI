#pragma once

#include "IParentPosition.h"

class IScrollable : public IParentPosition
{
public:

    ~IScrollable() override = default;

    virtual bool CanBeScrolled() = 0;

    virtual void Scroll(float scrollValue) = 0;
};