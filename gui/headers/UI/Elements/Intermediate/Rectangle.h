#pragma once
#include "ColorDefines.h"
#include "UI/Elements/Base/DrawableComponent.h"

#include "Utilities/Concepts/DerivedFromDrawRectangleStrategy.h"
#include "UI/Structs/RectangleData.h"

template<DerivedFromDrawRectangleStrategy TDrawRectangleStrategy>
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

    std::unique_ptr<TDrawRectangleStrategy> _drawRectangleStrategy;

    ImColor _color;

    ImColor _currentColor;

    float _rounding;

    float _thickness;
};

template <DerivedFromDrawRectangleStrategy TDrawRectangleStrategy>
Rectangle<TDrawRectangleStrategy>::Rectangle(RectangleData&& rectangleData, bool isHidden) :
    DrawableComponent(isHidden), _drawRectangleStrategy(std::make_unique<TDrawRectangleStrategy>()), _color(rectangleData.color),
    _currentColor(_color), _rounding(rectangleData.rounding), _thickness(rectangleData.thickness)
{}

template <DerivedFromDrawRectangleStrategy TDrawRectangleStrategy>
Rectangle<TDrawRectangleStrategy>::Rectangle(const Rectangle& other) :
    DrawableComponent(true),
    _drawRectangleStrategy(std::make_unique<TDrawRectangleStrategy>()),
    _color(other._color),
    _currentColor(other._currentColor),
    _rounding(other._rounding),
    _thickness(other._thickness)
{}

template <DerivedFromDrawRectangleStrategy TDrawRectangleStrategy>
void Rectangle<TDrawRectangleStrategy>::Enable()
{
    _currentColor = _color;
}

template <DerivedFromDrawRectangleStrategy TDrawRectangleStrategy>
void Rectangle<TDrawRectangleStrategy>::Disable()
{
    _currentColor = GRAY;
}

template <DerivedFromDrawRectangleStrategy TDrawRectangleStrategy>
std::unique_ptr<Rectangle<TDrawRectangleStrategy>> Rectangle<TDrawRectangleStrategy>::Clone() const
{
    return std::make_unique<Rectangle>(*this);
}

template <DerivedFromDrawRectangleStrategy TDrawRectangleStrategy>
void Rectangle<TDrawRectangleStrategy>::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    _drawRectangleStrategy->DrawRectangle(drawList, GetParentPosition(), GetParentBottomRightPosition(), _currentColor, _rounding, _thickness);
}