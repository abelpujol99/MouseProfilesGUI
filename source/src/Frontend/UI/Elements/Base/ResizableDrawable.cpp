#include "Frontend/UI/Elements/Base/ResizableDrawable.h"

#include "Frontend/Managers/View/ResolutionManager.h"
#include "Frontend/UI/Elements/Base/DrawableComponent.h"

ResizableDrawable::ResizableDrawable(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize,
    bool isHidden) :
        DrawableContainer(std::move(anchors), std::move(pivot), {ResolutionManager::GetInstance().AdaptWidth(relativePosition.x),
        ResolutionManager::GetInstance().AdaptHeight(relativePosition.y)}, std::move(desiredSize), isHidden)
{}

void ResizableDrawable::OnUpdateParentTransformImplementation()
{
    UpdateResizableDrawables();
}

void ResizableDrawable::OnUpdateAnchorsImplementation()
{
    UpdateResizableDrawables();
}

void ResizableDrawable::OnUpdatePivotImplementation()
{
    UpdateResizableDrawablePosition();
}

void ResizableDrawable::OnUpdateRelativePositionImplementation()
{
    UpdateResizableDrawables();
}

void ResizableDrawable::OnUpdateDesiredSizeImplementation()
{
    UpdateResizableDrawables();
}

void ResizableDrawable::OnUpdateAttributesImplementation()
{
    UpdateResizableDrawables();
}

void ResizableDrawable::UpdateResizableDrawables()
{
    auto itEnd {_resizableDrawables.cend()};

    for (auto it {_resizableDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdatePosition();

        (*it)->UpdateSize();

        (*it)->UpdateResizableDrawables();
    }
}

void ResizableDrawable::UpdateResizableDrawablePosition()
{
    auto itEnd {_resizableDrawables.cend()};

    for (auto it {_resizableDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdatePosition();

        (*it)->UpdateResizableDrawablePosition();
    }
}

void ResizableDrawable::AddResizableDrawable(std::unique_ptr<ResizableDrawable>&& resizableDrawable)
{
    if (resizableDrawable.get() == this)
    {
        return;
    }

    resizableDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    _resizableDrawables.push_front(std::move(resizableDrawable));
}

void ResizableDrawable::RemoveResizableDrawable(ResizableDrawable* resizableDrawable)
{
    auto itEnd {_resizableDrawables.cend()};

    auto itPrevious {_resizableDrawables.before_begin()};

    for (auto it{_resizableDrawables.begin()}; it != itEnd; ++it)
    {
        if (it->get() != resizableDrawable)
        {
            continue;
        }

        _resizableDrawables.erase_after(itPrevious);
        return;
    }
}

void ResizableDrawable::AddDrawableComponent(DrawableComponent* drawableComponent)
{
    drawableComponent->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    drawableComponent->SetIsHidden(false);

    _drawableComponents.push_front(drawableComponent);
}

void ResizableDrawable::RemoveDrawableComponent(DrawableComponent* drawableComponent)
{
    drawableComponent->SetIsHidden(true);

    auto itEnd {_drawableComponents.cend()};

    auto itPrevious {_drawableComponents.before_begin()};

    for (auto it {_drawableComponents.begin()}; it != itEnd; ++it)
    {
        if (*it != drawableComponent)
        {
            itPrevious = it;
            continue;
        }

        _drawableComponents.erase_after(itPrevious);

        return;
    }
}

void ResizableDrawable::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    DrawDrawables(_drawableComponents, drawList);

    DrawDrawables(_resizableDrawables, drawList);
}