#pragma once
#include "UI/Elements/Base/DrawableComponent.h"

#include <memory>

#include "Strategies/DrawStrategy/Rectangle/IDrawRectangleStrategy.h"

struct RectangleData;

class Rectangle : public DrawableComponent
{
public:

    Rectangle(RectangleData&& rectangleData, bool isHidden);

    ~Rectangle() override = default;

    void Enable() override;

    void Disable() override;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<IDrawRectangleStrategy> _drawRectangleStrategy;

    ImColor _color;

    ImColor _currentColor;

    float _rounding;

    float _thickness;
};
