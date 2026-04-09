#include "Frontend/UI/Drawable.h"

#include "Frontend/UI/Structs/DrawablePosition.h"

Drawable::Drawable(DrawablePosition&& drawablePosition, bool isHidden) : _parentPosition(drawablePosition.parentPosition),
    _relativePosition(drawablePosition.positionX, drawablePosition.positionY),
    _finalPosition(_parentPosition.x + _relativePosition.x, _parentPosition.y + _relativePosition.y), _isHidden(isHidden)
{}

void Drawable::SetIsHidden(bool isHidden)
{
    _isHidden = isHidden;
}

const ImVec2& Drawable::GetParentPosition() const
{
    return _parentPosition;
}

const ImVec2& Drawable::GetRelativePosition() const
{
    return _relativePosition;
}

const ImVec2& Drawable::GetFinalPosition() const
{
    return _finalPosition;
}

void Drawable::UpdatePosition()
{
    _finalPosition = {_parentPosition.x + _relativePosition.x, _parentPosition.y + _relativePosition.y};
}
