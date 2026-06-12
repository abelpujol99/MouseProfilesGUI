#pragma once
#include "UI/Elements/Base/DrawableComponent.h"

#include "Strategies/DrawStrategy/Rectangle/IDrawRectangleStrategy.h"
#include "UI/Structs/RectangleData.h"

class Rectangle : public DrawableComponent
{
public:

    Rectangle(RectangleData&& rectangleData, bool isHidden);

    Rectangle(const Rectangle& other);

    ~Rectangle() override = default;

    void Enable() override;

    void Disable() override;

    [[nodiscard]] std::unique_ptr<Rectangle> Clone() const;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<IDrawRectangleStrategy> _drawRectangleStrategy;

    ImColor _color;

    ImColor _currentColor;

    float _rounding;

    float _thickness;

    RectangleData _rectangleData;
};