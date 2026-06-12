#include "UI/Elements/Intermediate/Rectangle.h"

#include "ColorDefines.h"
#include "Factory/DrawableFactory.h"
#include "Strategies/DrawStrategy/Rectangle/DrawEmptyRectangle.h"
#include "Strategies/DrawStrategy/Rectangle/DrawFilledRectangle.h"
#include "UI/Structs/RectangleData.h"

Rectangle::Rectangle(RectangleData&& rectangleData, bool isHidden) :
        DrawableComponent(isHidden), _color(rectangleData.color), _currentColor(_color), _rounding(rectangleData.rounding),
        _thickness(rectangleData.thickness), _rectangleData(rectangleData)
{
    if (rectangleData.isFilled)
    {
        _drawRectangleStrategy = std::make_unique<DrawFilledRectangle>();
        return;
    }

    _drawRectangleStrategy = std::make_unique<DrawEmptyRectangle>();
}

Rectangle::Rectangle(const Rectangle& other) :
    DrawableComponent(true),
    _color(other._color),
    _currentColor(other._currentColor),
    _rounding(other._rounding),
    _thickness(other._thickness),
    _rectangleData(other._rectangleData)
{
    if (other._rectangleData.isFilled)
    {
        _drawRectangleStrategy = std::make_unique<DrawFilledRectangle>();
        return;
    }

    _drawRectangleStrategy = std::make_unique<DrawEmptyRectangle>();
}

void Rectangle::Enable()
{
    _currentColor = _color;
}

void Rectangle::Disable()
{
    _currentColor = GRAY;
}

std::unique_ptr<Rectangle> Rectangle::Clone() const
{
    return std::make_unique<Rectangle>(*this);
}

void Rectangle::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    _drawRectangleStrategy->DrawRectangle(drawList, GetParentPosition(), GetParentBottomRightPosition(), _currentColor, _rounding, _thickness);
}
