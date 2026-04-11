#include "Frontend/UI/Drawable.h"

#include "Frontend/Managers/View/ResolutionManager.h"
#include "Frontend/UI/Structs/DrawablePosition.h"

Drawable::Drawable(DrawablePosition&& drawablePosition, bool isHidden) :
        _parentPosition(drawablePosition.parentPosition),
        _relativePosition(ResolutionManager::GetInstance().AdaptWidth(drawablePosition.positionX),
        ResolutionManager::GetInstance().AdaptWidth(drawablePosition.positionY)),
        _position(std::make_unique<ImVec2>(_parentPosition.x + _relativePosition.x, _parentPosition.y + _relativePosition.y)),
        _isHidden(isHidden)
{}

void Drawable::SetIsHidden(bool isHidden)
{
    _isHidden = isHidden;
}

void Drawable::SetParentPosition(const ImVec2& parentPosition) const
{
    _parentPosition = parentPosition;
}

const ImVec2& Drawable::GetParentPosition() const
{
    return _parentPosition;
}

const ImVec2& Drawable::GetRelativePosition() const
{
    return _relativePosition;
}

ImVec2* Drawable::GetPosition() const
{
    return _position.get();
}

void Drawable::UpdatePosition()
{
    *_position = {_parentPosition.x + _relativePosition.x, _parentPosition.y + _relativePosition.y};
}
