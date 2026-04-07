#include "UI/Basic/Rectangle.h"

#include "UI/DrawStrategy/Rectangle/DrawEmptyRectangle.h"
#include "UI/DrawStrategy/Rectangle/DrawFilledRectangle.h"
#include "UI/Structs/RectangleData.h"

Rectangle::Rectangle(DrawablePosition &&drawablePositon, RectangleData&& rectangleData, bool isHidden) :
        RectDrawable(std::move(drawablePositon), isHidden), _color(rectangleData.color), _rounding(rectangleData.rounding),
        _thickness(rectangleData.thickness)
{
    SetSize(rectangleData.size);

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

    _drawRectangleStrategy->DrawRectangle(drawList, _finalPosition, _bottomRightPosition, _color, _rounding, _thickness);
}