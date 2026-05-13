#include "Frontend/UI/Elements/Intermediate/Rectangle.h"

#include "Frontend/Strategies/DrawStrategy/Rectangle/DrawEmptyRectangle.h"
#include "Frontend/Strategies/DrawStrategy/Rectangle/DrawFilledRectangle.h"
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
    if (IsHidden())
    {
        return;
    }

    _drawRectangleStrategy->DrawRectangle(drawList, GetParentPosition(), GetParentBottomRightPosition(), _color, _rounding, _thickness);
}