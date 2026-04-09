#pragma once
#include "IPosition.h"

struct ImVec2;

class ISelectable : public IPosition
{
    public:

    ~ISelectable() override = default;

    virtual bool CanBeSelected() = 0;

    virtual const ImVec2& GetBottomRightPosition() = 0;

    virtual void OnSelect() = 0;

    virtual void OnUnselect() = 0;
};