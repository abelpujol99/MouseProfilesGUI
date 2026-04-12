#include "Frontend/UI/Elements/Base/RectDrawable.h"

#include "Frontend/Managers/View/ResolutionManager.h"

RectDrawable::RectDrawable(ImVec2&& relativePosition, ImVec2&& size, bool isHidden) :
        BaseDrawable(isHidden), _relativePosition(ResolutionManager::GetInstance().AdaptWidth(relativePosition.x),
        ResolutionManager::GetInstance().AdaptHeight(relativePosition.y))
{
    *_size = size;
}

void RectDrawable::SetRelativePosition(ImVec2&& relativePosition)
{
    _relativePosition = relativePosition;

    UpdatePosition();
}

void RectDrawable::UpdatePosition() const
{
    *_position = {GetPosition().x + _relativePosition.x, GetPosition().y + _relativePosition.y};

    UpdateBottomRightPosition();
}

void RectDrawable::SetSize(ImVec2&& size)
{
    //TODO ANCHORS
}

void RectDrawable::UpdateSize() const
{
    //*_size = BaseDrawable::GetSize();

    UpdateBottomRightPosition();
}

ImVec2 RectDrawable::GetSize() const
{
    return *_size;
}

void RectDrawable::UpdateBottomRightPosition() const
{
    *_bottomRightPosition = {_position->x + _size->x, _position->y + _size->y};

    UpdateRectDrawables();
}

ImVec2 RectDrawable::GetBottomRightPosition() const
{
    return *_bottomRightPosition;
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

    rectDrawable->SetParentTransform(_position.get(), _size.get());

    _rectDrawables.push_front(std::move(rectDrawable));
}

void RectDrawable::AddDrawableComponent(std::unique_ptr<DrawableComponent>&& componentDrawable)
{
    componentDrawable->SetParentTransform(_position.get(), _size.get());

    componentDrawable->SetBottomRightPositionPointer(_bottomRightPosition.get());

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