#include "UI/RectDrawable.h"

#include <algorithm>

RectDrawable::RectDrawable(DrawablePosition&& drawablePosition, bool isHidden) : Drawable(std::move(drawablePosition), isHidden)
{}

void RectDrawable::SetSize(const ImVec2& size)
{
    _size.x = size.x;
    _size.y = size.y;

    _bottomRightPosition.x = _relativePosition.x + _size.x;
    _bottomRightPosition.y = _relativePosition.y + _size.y;
}

void RectDrawable::UpdatePosition()
{
    Drawable::UpdatePosition();

    _bottomRightPosition = {_finalPosition.x + _size.x, _finalPosition.y + _size.y};
}

const ImVec2& RectDrawable::GetSize() const
{
    return _size;
}