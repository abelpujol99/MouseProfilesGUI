#include "UI/RectDrawable.h"

RectDrawable::RectDrawable(const ImVec2& parentPosition, float positionX, float positionY, bool isHidden = false) :
    Drawable(parentPosition, positionX, positionY, isHidden)
{}

void RectDrawable::SetSize(int width, int height)
{
    _size.x = width;
    _size.y = height;

    _bottomRightPosition.x = _relativePosition.x + _size.x;
    _bottomRightPosition.y = _relativePosition.y + _size.y;
}
