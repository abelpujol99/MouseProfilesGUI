#include "Frontend/UI/Elements/Base/RectDrawable.h"

#include "Frontend/Managers/View/DrawManager.h"
#include "Frontend/Managers/View/ResolutionManager.h"
#include "Frontend/Utilities/Math.h"

RectDrawable::RectDrawable(uint8_t layer, uint8_t order, Anchors&& anchors, ImVec2&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden) :
        BaseDrawable(isHidden), _layer(layer), _order(order), _anchors(anchors), _pivot(pivot),
        _relativePosition(ResolutionManager::GetInstance().AdaptWidth(relativePosition.x),
        ResolutionManager::GetInstance().AdaptHeight(relativePosition.y)), _desiredSize(desiredSize)
{
    DrawManager::GetInstance().AddDrawable(this, layer, order);
}

RectDrawable::~RectDrawable() noexcept
{
    DrawManager::GetInstance().RemoveDrawable(_layer, _order);
}

void RectDrawable::SetParentAttributes(ImVec2* parentPosition, ImVec2* parentBottomRightPosition, ImVec2* parentSize,
    bool* isParentHidden)
{
    BaseDrawable::SetParentAttributes(parentPosition, parentBottomRightPosition, parentSize, isParentHidden);

    UpdatePosition();

    UpdateSize();

    UpdateRectDrawables();
}

void RectDrawable::SetAnchors(Anchors&& anchors)
{
    _anchors = anchors;

    UpdatePosition();

    UpdateSize();
}

void RectDrawable::SetPivot(ImVec2&& pivot)
{
    _pivot = pivot;

    UpdatePosition();
}

void RectDrawable::SetRelativePosition(ImVec2&& relativePosition)
{
    _relativePosition = relativePosition;

    UpdatePosition();

    UpdateRectDrawablesPosition();
}

void RectDrawable::UpdatePosition() const
{
    *_position = {CalculatePositionLeft(), CalculatePositionTop()};

    *_bottomRightPosition = {CalculatePositionRight(), CalculatePositionBottom()};
}

void RectDrawable::SetDesiredSize(ImVec2&& desiredSize)
{
    _desiredSize = desiredSize;

    UpdatePosition();

    UpdateSize();

    UpdateRectDrawables();
}

void RectDrawable::UpdateAttributes() const
{
    UpdatePosition();

    UpdateSize();

    UpdateRectDrawables();
}

void RectDrawable::UpdateSize() const
{
    *_size = {_bottomRightPosition->x - _position->x, _bottomRightPosition->y - _position->y};
}

void RectDrawable::UpdateVisibility()
{
    BaseDrawable::UpdateVisibility();

    UpdateRectDrawablesVisibility();
}

void RectDrawable::UpdateRectDrawables() const
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdatePosition();

        (*it)->UpdateSize();

        (*it)->UpdateRectDrawables();
    }
}

void RectDrawable::UpdateRectDrawablesPosition() const
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdatePosition();

        (*it)->UpdateRectDrawablesPosition();
    }
}

void RectDrawable::UpdateRectDrawablesSize() const
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateSize();

        (*it)->UpdateRectDrawablesSize();
    }
}

void RectDrawable::UpdateRectDrawablesVisibility() const
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateVisibility();
    }
}

void RectDrawable::AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable)
{
    if (rectDrawable.get() == this)
    {
        return;
    }

    rectDrawable->SetParentAttributes(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());

    _rectDrawables.push_front(std::move(rectDrawable));
}

void RectDrawable::AddDrawableComponent(std::unique_ptr<DrawableComponent>&& componentDrawable)
{
    componentDrawable->SetParentAttributes(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());

    _drawableComponents.push_front(std::move(componentDrawable));
}

void RectDrawable::Draw(ImDrawList* drawList)
{
    if (MustBeHidden())
    {
        return;
    }

    DrawDrawables(_drawableComponents, drawList);
}

float RectDrawable::CalculatePositionLeft() const
{
    float parentSizeX {GetParentSize().x};

    float startPoint {CalculateStartPoint(GetParentPosition().x, parentSizeX, _anchors.min.x)};

    float halfSize {CalculateSize(_desiredSize.x, parentSizeX, _anchors.max.x, _anchors.min.x) / 2};

    float relativePoint {CalculateRelativePoint(_relativePosition.x,
        -(_desiredSize.x / 2) * Utilities::Math::Absolute(_anchors.max.x - _anchors.min.x - 1))};

    relativePoint += halfSize + halfSize * -(_pivot.x * 2);

    return startPoint + relativePoint;
}

float RectDrawable::CalculatePositionTop() const
{
    float parentSizeY {GetParentSize().y};

    float startPoint {CalculateStartPoint(GetParentPosition().y, parentSizeY, _anchors.min.y)};

    float relativePoint {CalculateRelativePoint(_relativePosition.y,
        -(_desiredSize.y / 2)  * Utilities::Math::Absolute(_anchors.max.y - _anchors.min.y - 1))};

    float halfSize {CalculateSize(_desiredSize.y, parentSizeY, _anchors.max.y, _anchors.min.y) / 2};

    relativePoint += halfSize + halfSize * -(_pivot.y * 2);

    return startPoint + relativePoint;
}

float RectDrawable::CalculatePositionRight() const
{
    float parentSizeX {GetParentSize().x};

    float startPoint {CalculateStartPoint(GetParentBottomRightPosition().x, -parentSizeX, 1 - _anchors.max.x)};

    float relativePoint {CalculateRelativePoint(_relativePosition.x,
        (_desiredSize.x / 2) * Utilities::Math::Absolute(_anchors.max.x - _anchors.min.x - 1))};

    float halfSize {CalculateSize(_desiredSize.x, parentSizeX, _anchors.max.x, _anchors.min.x) / 2};

    relativePoint += halfSize + halfSize * -(_pivot.x * 2);

    return startPoint + relativePoint;
}

float RectDrawable::CalculatePositionBottom() const
{
    float parentSizeY {GetParentSize().y};

    float startPoint {CalculateStartPoint(GetParentBottomRightPosition().y, -parentSizeY, 1 - _anchors.max.y)};

    float relativePoint {CalculateRelativePoint(_relativePosition.y,
        (_desiredSize.y / 2) * Utilities::Math::Absolute(_anchors.max.y - _anchors.min.y - 1))};

    float halfSize {CalculateSize(_desiredSize.y, parentSizeY, _anchors.max.y, _anchors.min.y) / 2};

    relativePoint += halfSize + halfSize * -(_pivot.y * 2);

    return startPoint + relativePoint;
}

float RectDrawable::CalculateStartPoint(float parentPosition, float parentSize, float multiplier)
{
    return parentPosition + parentSize * multiplier;
}

float RectDrawable::CalculateRelativePoint(float relativePoint, float size)
{
    return relativePoint + size;
}

float RectDrawable::CalculateSize(float desiredSize, float parentSize, float maxAnchor, float minAnchor)
{
    float multiplier {maxAnchor - minAnchor};

    return desiredSize * Utilities::Math::Absolute(multiplier - 1) + parentSize * multiplier;
}