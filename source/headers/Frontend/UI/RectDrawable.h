#pragma once
#include "Drawable.h"

class RectDrawable : public Drawable
{
public:

    ~RectDrawable() override = default;

    void UpdatePosition() override;

    [[nodiscard]] const ImVec2& GetSize() const;

protected:

    RectDrawable(DrawablePosition&& drawablePosition, bool isHidden);

    void SetSize(const ImVec2& size);

    ImVec2 _size;
    ImVec2 _bottomRightPosition;
};