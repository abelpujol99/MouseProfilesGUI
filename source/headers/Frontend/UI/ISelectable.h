#pragma once

struct ImVec2;

class ISelectable
{
    public:

    virtual ~ISelectable() = default;

    virtual bool CanBeSelected() = 0;

    virtual const ImVec2& GetPosition() = 0;

    virtual const ImVec2& GetBottomRightPosition() = 0;

    virtual void OnSelect() = 0;

    virtual void OnUnselect() = 0;
};