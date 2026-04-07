#pragma once
#include <memory>

#include "UI/RectDrawable.h"
#include "UI/DrawStrategy/Rectangle/IDrawRectangleStrategy.h"
#include "UI/Structs/RectangleData.h"

class Rectangle : public RectDrawable
{
public:

    Rectangle(DrawablePosition&& drawablePositon, RectangleData&& rectangleData, bool isHidden);

    ~Rectangle() override = default;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<IDrawRectangleStrategy> _drawRectangleStrategy;

    ImColor _color;

    float _rounding;

    float _thickness;
};
