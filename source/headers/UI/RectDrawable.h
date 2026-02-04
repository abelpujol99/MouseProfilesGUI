#pragma once
#include "Drawable.h"

class RectDrawable : public Drawable
{
public:

    virtual ~RectDrawable() = default;

    void UpdatePosition() override;

protected:

    RectDrawable(const ImVec2& parentPosition, float positionX, float positionY, bool isHidden);

    ImVec2 _size;
    ImVec2 _bottomRightPosition;

    void SetSize(int width, int height);
};