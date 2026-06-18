#include "UI/Elements/Base/RectDrawable.h"

#include "Managers/View/ResolutionManager.h"
#include "Utilities/Math.h"

RectDrawable::RectDrawable(RectDrawableData&& rectDrawableData, bool isHidden) :
        BaseDrawable(isHidden), _anchors(std::move(rectDrawableData.anchors)), _pivot(std::move(rectDrawableData.pivot)),
        _relativePosition({ResolutionManager::GetInstance().AdaptWidth(rectDrawableData.relativePosition.x),
        ResolutionManager::GetInstance().AdaptHeight(rectDrawableData.relativePosition.y)}), _desiredSize(std::move(rectDrawableData.desiredSize))
{}

void RectDrawable::SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    BaseDrawable::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

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

    rectDrawable->SetParentState(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());

    _rectDrawables.insert(std::move(rectDrawable));
}

void RectDrawable::RemoveRectDrawable(RectDrawable* rectDrawable)
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        if (it->get() != rectDrawable)
        {
            continue;
        }

        _rectDrawables.erase(it);

        return;
    }
}

void RectDrawable::ClearRectDrawables()
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->ClearRectDrawables();
    }

    _rectDrawables.clear();
}

void RectDrawable::AddDrawableComponent(DrawableComponent* drawableComponent)
{
    drawableComponent->SetParentState(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());

    _drawableComponents.insert(drawableComponent);
}

void RectDrawable::RemoveDrawableComponent(DrawableComponent* drawableComponent)
{
    _drawableComponents.erase(drawableComponent);
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

void RectDrawable::Enable()
{
    EnableDrawables(_drawableComponents);

    EnableDrawables(_rectDrawables);
}

void RectDrawable::Disable()
{
    DisableDrawables(_drawableComponents);

    DisableDrawables(_rectDrawables);
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
        (*it)->UpdateAttributes();
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
    if (IsHidden())
    {
        return;
    }

    DrawDrawables(_drawableComponents, drawList);

    DrawDrawables(_rectDrawables, drawList);
}