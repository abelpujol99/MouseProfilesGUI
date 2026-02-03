#include "UI/Drawable.h"

Drawable::Drawable(const ImVec2& parentPosition, float relativePositionX, float relativePositionY, bool isHidden = false) :
    _parentPosition(parentPosition), _relativePosition(relativePositionX, relativePositionY),
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
    const ImVec2& relativePosition {GetRelativePosition()};

    _finalPosition = {_parentPosition.x + relativePosition.x, _parentPosition.y + relativePosition.y};
}
