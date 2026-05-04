#include "Frontend/UI/Elements/Base/RectDrawable.h"

#include "Frontend/Managers/View/ResolutionManager.h"
#include "Frontend/Utilities/Math.h"

RectDrawable::RectDrawable(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden) :
        BaseDrawable(isHidden), _anchors(std::move(anchors)), _pivot(std::move(pivot)),
        _relativePosition({ResolutionManager::GetInstance().AdaptWidth(relativePosition.x),
        ResolutionManager::GetInstance().AdaptHeight(relativePosition.y)}), _desiredSize(std::move(desiredSize))
{}

void RectDrawable::SetParentTransform(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer)
{
    BaseDrawable::SetParentTransform(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer);

    UpdatePosition();

    UpdateSize();

    UpdateRectDrawables();
}

void RectDrawable::SetAnchors(Anchors&& anchors)
{
    _anchors = anchors;

    UpdatePosition();

    UpdateSize();

    UpdateRectDrawables();
}

void RectDrawable::SetPivot(Pivot&& pivot)
{
    _pivot = pivot;

    UpdatePosition();

    UpdateRectDrawablesPosition();
}

void RectDrawable::SetRelativePosition(ImVec2&& relativePosition)
{
    _relativePosition = relativePosition;

    UpdatePosition();

    UpdateRectDrawables();
}

ImVec2 RectDrawable::GetRelativePosition() const
{
    return _relativePosition;
}

void RectDrawable::SetDesiredSize(ImVec2&& desiredSize)
{
    _desiredSize = desiredSize;

    UpdatePosition();

    UpdateSize();

    UpdateRectDrawables();
}

ImVec2 RectDrawable::GetSize() const
{
    return *_size;
}

void RectDrawable::UpdatePosition() const
{
    *_position = {CalculatePositionLeft(), CalculatePositionTop()};

    *_bottomRightPosition = {CalculatePositionRight(), CalculatePositionBottom()};

    auto itEnd {_drawableComponents.cend()};

    for (auto it {_drawableComponents.begin()}; it != itEnd; ++it)
    {
        (*it)->OnParentPositionUpdated();

        (*it)->OnParentBottomRightPositionUpdated();
    }
}

void RectDrawable::UpdateSize() const
{
    *_size = {_bottomRightPosition->x - _position->x, _bottomRightPosition->y - _position->y};

    auto itEnd {_drawableComponents.cend()};

    for (auto it {_drawableComponents.begin()}; it != itEnd; ++it)
    {
        (*it)->OnParentSizeUpdated();
    }
}

void RectDrawable::UpdateAttributes()
{
    UpdatePosition();

    UpdateSize();

    UpdateRectDrawables();
}

void RectDrawable::AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable)
{
    if (rectDrawable.get() == this)
    {
        return;
    }

    rectDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    rectDrawable->SetIsHidden(false);

    _rectDrawables.push_front(std::move(rectDrawable));
}

void RectDrawable::RemoveRectDrawable(RectDrawable* rectDrawable)
{
    rectDrawable->SetIsHidden(true);

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

void RectDrawable::AddDrawableComponent(DrawableComponent* drawableComponent)
{
    drawableComponent->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    drawableComponent->SetIsHidden(false);

    _drawableComponents.push_front(std::move(drawableComponent));
}

void RectDrawable::RemoveDrawableComponent(DrawableComponent* drawableComponent)
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

void RectDrawable::ClearDrawableComponents()
{
    _drawableComponents.clear();

    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->ClearDrawableComponents();
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

float RectDrawable::CalculatePositionLeft() const
{
    float parentSizeX {GetParentSize().x};

    float startPoint {CalculateStartPoint(GetParentPosition().x, parentSizeX, _anchors._min.x)};

    float halfSize {CalculateSize(_desiredSize.x, parentSizeX, _anchors._max.x, _anchors._min.x) / 2};

    float relativePoint {CalculateRelativePoint(_relativePosition.x,
        -(_desiredSize.x / 2) * Utilities::Math::Absolute(_anchors._max.x - _anchors._min.x - 1))};

    relativePoint += halfSize + halfSize * -(_pivot.GetXPivot() * 2);

    return startPoint + relativePoint;
}

float RectDrawable::CalculatePositionTop() const
{
    float parentSizeY {GetParentSize().y};

    float startPoint {CalculateStartPoint(GetParentPosition().y, parentSizeY, _anchors._min.y)};

    float relativePoint {CalculateRelativePoint(_relativePosition.y,
        -(_desiredSize.y / 2)  * Utilities::Math::Absolute(_anchors._max.y - _anchors._min.y - 1))};

    float halfSize {CalculateSize(_desiredSize.y, parentSizeY, _anchors._max.y, _anchors._min.y) / 2};

    relativePoint += halfSize + halfSize * -(_pivot.GetYPivot() * 2);

    return startPoint + relativePoint;
}

float RectDrawable::CalculatePositionRight() const
{
    float parentSizeX {GetParentSize().x};

    float startPoint {CalculateStartPoint(GetParentBottomRightPosition().x, -parentSizeX, 1 - _anchors._max.x)};

    float relativePoint {CalculateRelativePoint(_relativePosition.x,
        (_desiredSize.x / 2) * Utilities::Math::Absolute(_anchors._max.x - _anchors._min.x - 1))};

    float halfSize {CalculateSize(_desiredSize.x, parentSizeX, _anchors._max.x, _anchors._min.x) / 2};

    relativePoint += halfSize + halfSize * -(_pivot.GetXPivot() * 2);

    return startPoint + relativePoint;
}

float RectDrawable::CalculatePositionBottom() const
{
    float parentSizeY {GetParentSize().y};

    float startPoint {CalculateStartPoint(GetParentBottomRightPosition().y, -parentSizeY, 1 - _anchors._max.y)};

    float relativePoint {CalculateRelativePoint(_relativePosition.y,
        (_desiredSize.y / 2) * Utilities::Math::Absolute(_anchors._max.y - _anchors._min.y - 1))};

    float halfSize {CalculateSize(_desiredSize.y, parentSizeY, _anchors._max.y, _anchors._min.y) / 2};

    relativePoint += halfSize + halfSize * -(_pivot.GetYPivot() * 2);

    return startPoint + relativePoint;
}

float RectDrawable::CalculateStartPoint(float parentPosition, float parentSize, float multiplier)
{
    return parentPosition + parentSize * multiplier;
}

float RectDrawable::CalculateRelativePoint(float relativePosition, float size)
{
    return relativePosition + size;
}

float RectDrawable::CalculateSize(float desiredSize, float parentSize, float maxAnchor, float minAnchor)
{
    float multiplier {maxAnchor - minAnchor};

    return desiredSize * Utilities::Math::Absolute(multiplier - 1) + parentSize * multiplier;
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
