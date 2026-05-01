#include "Frontend/UI/Elements/Base/RectDrawable.h"

#include "Frontend/Managers/View/ResolutionManager.h"

RectDrawable::RectDrawable(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden) :
        DrawableContainer(std::move(anchors), std::move(pivot), {ResolutionManager::GetInstance().AdaptWidth(relativePosition.x),
        ResolutionManager::GetInstance().AdaptHeight(relativePosition.y)}, std::move(desiredSize), isHidden)
{}

void RectDrawable::OnUpdateParentTransformImplementation()
{
    UpdateRectDrawables();
}

void RectDrawable::OnUpdateAnchorsImplementation()
{
    UpdateRectDrawables();
}

void RectDrawable::OnUpdatePivotImplementation()
{
    UpdateRectDrawablesPosition();
}

void RectDrawable::OnUpdateRelativePositionImplementation()
{
    UpdateRectDrawables();
}

void RectDrawable::OnUpdateDesiredSizeImplementation()
{
    UpdateRectDrawables();
}

void RectDrawable::OnUpdateAttributesImplementation()
{
    UpdateRectDrawables();
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

void RectDrawable::RemoveRectDrawable(RectDrawable* rectDrawable)
{
    auto itEnd {_rectDrawables.cend()};

    auto itPrevious {_rectDrawables.before_begin()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        if (it->get() != rectDrawable)
        {
            itPrevious = it;
            continue;
        }

        _rectDrawables.erase_after(itPrevious);

        return;
    }
}

void RectDrawable::UpdateRectDrawablesPosition()
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdatePosition();

        (*it)->UpdateRectDrawablesPosition();
    }
}

void RectDrawable::UpdateRectDrawables()
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdatePosition();

        (*it)->UpdateSize();

        (*it)->UpdateRectDrawables();
    }
}

void RectDrawable::AddRectDrawables(std::unique_ptr<RectDrawable>&& rectDrawable)
{
    if (rectDrawable.get() == this)
    {
        return;
    }

    rectDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    _rectDrawables.push_front(std::move(rectDrawable));
}

void RectDrawable::RemoveRectDrawables(RectDrawable* rectDrawable)
{
    auto itEnd {_rectDrawables.cend()};

    auto itPrevious {_rectDrawables.before_begin()};

    for (auto it{_rectDrawables.begin()}; it != itEnd; ++it)
    {
        if (it->get() != rectDrawable)
        {
            continue;
        }

        _rectDrawables.erase_after(itPrevious);
        return;
    }
}

void RectDrawable::AddDrawableComponent(std::unique_ptr<DrawableComponent>&& componentDrawable)
{
    componentDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    _drawableComponents.push_front(std::move(componentDrawable));
}

void RectDrawable::RemoveDrawableComponent(DrawableComponent* drawableComponent)
{
    auto itEnd {_drawableComponents.cend()};

    auto itPrevious {_drawableComponents.before_begin()};

    for (auto it {_drawableComponents.begin()}; it != itEnd; ++it)
    {
        if (it->get() != drawableComponent)
        {
            itPrevious = it;
            continue;
        }

        _drawableComponents.erase_after(itPrevious);

        return;
    }
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