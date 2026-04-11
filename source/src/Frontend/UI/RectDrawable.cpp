#include "Frontend/UI/RectDrawable.h"

#include <algorithm>

#include "Frontend/Managers/View/ResolutionManager.h"

RectDrawable::RectDrawable(DrawablePosition&& drawablePosition, bool isHidden) : Drawable(std::move(drawablePosition), isHidden)
{}

void RectDrawable::SetSize(const ImVec2& size)
{
    _size.x = ResolutionManager::GetInstance().AdaptWidth(size.x);
    _size.y = ResolutionManager::GetInstance().AdaptHeight(size.y);

    _bottomRightPosition.x = _relativePosition.x + _size.x;
    _bottomRightPosition.y = _relativePosition.y + _size.y;
}

void RectDrawable::UpdatePosition()
{
    Drawable::UpdatePosition();

    _bottomRightPosition = {_position->x + _size.x, _position->y + _size.y};
}

const ImVec2& RectDrawable::GetSize() const
{
    return _size;
}