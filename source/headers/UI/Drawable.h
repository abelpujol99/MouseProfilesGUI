#pragma once

#include "imgui.h"

class DrawablePosition;
struct ImDrawList;

class Drawable
{
public:

    virtual ~Drawable() = default;

    void SetIsHidden(bool isHidden);

    [[nodiscard]] const ImVec2& GetParentPosition() const;

    [[nodiscard]] virtual const ImVec2& GetRelativePosition() const;

    [[nodiscard]] const ImVec2& GetFinalPosition() const;

    virtual void UpdatePosition();

    virtual void Draw(ImDrawList* drawList) = 0;

protected:

    Drawable(DrawablePosition&& drawablePosition, bool isHidden);

    const ImVec2& _parentPosition;
    ImVec2 _relativePosition;
    ImVec2 _finalPosition;

    bool _isHidden;
};
