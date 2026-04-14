#include "Frontend/UI/Elements/Base/RectDrawable.h"

#include "Frontend/Managers/View/ResolutionManager.h"

RectDrawable::RectDrawable(Anchors&& anchors, ImVec2&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden) :
        BaseDrawable(isHidden), _anchors(anchors), _pivot(pivot),
        _relativePosition(ResolutionManager::GetInstance().AdaptWidth(relativePosition.x),
        ResolutionManager::GetInstance().AdaptHeight(relativePosition.y)), _desiredSize(desiredSize)
{}

void RectDrawable::SetDesiredSize(ImVec2&& desiredSize)
{
    _desiredSize = desiredSize;

    UpdatePosition();

    UpdateSize();

    UpdateRectDrawables();
}

void RectDrawable::UpdateSize() const
{
    *_size = {_bottomRightPosition->x - _position->x, _bottomRightPosition->y - _position->y};
}

void RectDrawable::SetRelativePosition(ImVec2&& relativePosition)
{
    _relativePosition = relativePosition;

    UpdatePosition();

    UpdateRectDrawables();
}

void RectDrawable::UpdatePosition() const
{
    const ImVec2& parentPosition {GetParentPosition()};
    const ImVec2& parentBottomRightPosition {GetParentBottomRightPosition()};
    const ImVec2& parentSize {GetParentSize()};

    *_position = {_anchors.CalculatePositionLeft(parentPosition.x, parentSize.x, _relativePosition.x, _desiredSize.x, _pivot.x),
        _anchors.CalculatePositionTop(parentPosition.y, parentSize.y, _relativePosition.y, _desiredSize.y, _pivot.y)};

    *_bottomRightPosition = {_anchors.CalculatePositionRight(parentBottomRightPosition.x, parentSize.x, _relativePosition.x, _desiredSize.x, _pivot.x),
        _anchors.CalculatePositionBottom(parentBottomRightPosition.y, parentSize.y, _relativePosition.y, _desiredSize.y, _pivot.y)};
}

void RectDrawable::UpdateRectDrawables() const
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdatePosition();

        (*it)->UpdateSize();
    }
}

void RectDrawable::AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable)
{
    if (rectDrawable.get() == this)
    {
        return;
    }

    rectDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    _rectDrawables.push_front(std::move(rectDrawable));
}

void RectDrawable::AddDrawableComponent(std::unique_ptr<DrawableComponent>&& componentDrawable)
{
    componentDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    _drawableComponents.push_front(std::move(componentDrawable));
}

void RectDrawable::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    DrawDrawables(_drawableComponents, drawList);

    DrawDrawables(_rectDrawables, drawList);
}