#pragma once

class ISelectable
{
public:

    virtual ~ISelectable() = default;

    virtual bool CanBeSelected() = 0;

    virtual void OnSelect() = 0;

    virtual void OnUnselect() = 0;
};