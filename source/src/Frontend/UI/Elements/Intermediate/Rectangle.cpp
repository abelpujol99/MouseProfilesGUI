#include "Frontend/UI/Elements/Intermediate/Rectangle.h"

#include "Frontend/UI/Strategies/DrawStrategy/Rectangle/DrawEmptyRectangle.h"
#include "Frontend/UI/Strategies/DrawStrategy/Rectangle/DrawFilledRectangle.h"
#include "Frontend/UI/Structs/RectangleData.h"

Rectangle::Rectangle(RectangleData&& rectangleData, bool isHidden) :
        DrawableComponent(isHidden), _color(rectangleData.color), _rounding(rectangleData.rounding),
        _thickness(rectangleData.thickness)
{
    if (rectangleData.isFilled)
    {
        _drawRectangleStrategy = std::make_unique<DrawFilledRectangle>();
        return;
    }

    _drawRectangleStrategy = std::make_unique<DrawEmptyRectangle>();
}

void Rectangle::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    _drawRectangleStrategy->DrawRectangle(drawList, GetPosition(), GetBottomRightPosition(), _color, _rounding, _thickness);
}