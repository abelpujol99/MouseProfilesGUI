#pragma once
#include "Frontend/UI/Elements/Base/DrawableComponent.h"

#include <memory>

#include "Frontend/UI/Strategies/DrawStrategy/Rectangle/IDrawRectangleStrategy.h"

struct RectangleData;

class Rectangle : public DrawableComponent
{
public:

    Rectangle(RectangleData&& rectangleData, bool isHidden);

    ~Rectangle() override = default;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<IDrawRectangleStrategy> _drawRectangleStrategy;

    ImColor _color;

    float _rounding;

    float _thickness;
};
