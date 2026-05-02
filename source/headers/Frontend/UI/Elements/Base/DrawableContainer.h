#pragma once
#include "BaseDrawable.h"
#include "DrawableTransform.h"

#include <forward_list>

#include "Frontend/Utilities/Anchors.h"
#include "Frontend/Utilities/Concepts/Pointer.h"
#include "Frontend/Managers/View/ResolutionManager.h"
#include "Frontend/Utilities/Math.h"
#include "Frontend/Utilities/Pivot.h"

class DrawableComponent;

template<Pointer TDrawableComponentPointer>
class DrawableContainer : public BaseDrawable, public DrawableTransform
{
public:

    DrawableContainer(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden);

    ~DrawableContainer() override = default;

    void SetParentTransform(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer) override;

    void SetAnchors(Anchors&& anchors);

    void SetPivot(Pivot&& pivot);

    void SetRelativePosition(ImVec2&& relativePosition);

    [[nodiscard]] ImVec2 GetRelativePosition() const;

    void SetDesiredSize(ImVec2&& desiredSize);

    [[nodiscard]] ImVec2 GetSize() const;

    void UpdateAttributes();

    virtual void RemoveDrawableComponent(DrawableComponent* drawableComponent) = 0;

    void ClearDrawableComponents();

protected:

    void UpdatePosition() const;

    void UpdateSize() const;

    float CalculatePositionLeft() const;

    float CalculatePositionTop() const;

    float CalculatePositionRight() const;

    float CalculatePositionBottom() const;

    static float CalculateStartPoint(float parentPosition, float parentSize, float multiplier);

    static float CalculateRelativePoint(float relativePosition, float size);

    static float CalculateSize(float desiredSize, float parentSize, float maxAnchor, float minAnchor);

    Anchors _anchors;

    Pivot _pivot;

    ImVec2 _relativePosition;

    ImVec2 _desiredSize;

    std::forward_list<TDrawableComponentPointer> _drawableComponents;

private:

    virtual void OnUpdateParentTransformImplementation() = 0;

    virtual void OnUpdateAnchorsImplementation() = 0;

    virtual void OnUpdatePivotImplementation() = 0;

    virtual void OnUpdateRelativePositionImplementation() = 0;

    virtual void OnUpdateDesiredSizeImplementation() = 0;

    virtual void OnUpdateAttributesImplementation() = 0;
};

template<Pointer TDrawableComponentPointer>
DrawableContainer<TDrawableComponentPointer>::DrawableContainer(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize,
    bool isHidden):
        BaseDrawable(isHidden), _anchors(anchors), _pivot(pivot),
        _relativePosition(ResolutionManager::GetInstance().AdaptWidth(relativePosition.x),
        ResolutionManager::GetInstance().AdaptHeight(relativePosition.y)), _desiredSize(desiredSize)
{}

template<Pointer TDrawableComponentPointer>
void DrawableContainer<TDrawableComponentPointer>::SetParentTransform(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer)
{
    BaseDrawable::SetParentTransform(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer);

    UpdatePosition();

    UpdateSize();

    OnUpdateParentTransformImplementation();
}

template<Pointer TDrawableComponentPointer>
void DrawableContainer<TDrawableComponentPointer>::SetAnchors(Anchors&& anchors)
{
    _anchors = anchors;

    UpdatePosition();

    UpdateSize();

    OnUpdateAnchorsImplementation();
}

template<Pointer TDrawableComponentPointer>
void DrawableContainer<TDrawableComponentPointer>::SetPivot(Pivot&& pivot)
{
    _pivot = pivot;

    UpdatePosition();

    OnUpdatePivotImplementation();
}

template<Pointer TDrawableComponentPointer>
void DrawableContainer<TDrawableComponentPointer>::SetRelativePosition(ImVec2&& relativePosition)
{
    _relativePosition = relativePosition;

    UpdatePosition();

    OnUpdateRelativePositionImplementation();
}

template<Pointer TDrawableComponentPointer>
ImVec2 DrawableContainer<TDrawableComponentPointer>::GetRelativePosition() const
{
    return _relativePosition;
}

template<Pointer TDrawableComponentPointer>
void DrawableContainer<TDrawableComponentPointer>::SetDesiredSize(ImVec2&& desiredSize)
{
    _desiredSize = desiredSize;

    UpdatePosition();

    UpdateSize();

    OnUpdateDesiredSizeImplementation();
}

template<Pointer TDrawableComponentPointer>
ImVec2 DrawableContainer<TDrawableComponentPointer>::GetSize() const
{
    return *_size;
}

template<Pointer TDrawableComponentPointer>
void DrawableContainer<TDrawableComponentPointer>::UpdateAttributes()
{
    UpdatePosition();

    UpdateSize();

    OnUpdateAttributesImplementation();
}

template<Pointer TDrawableComponentPointer>
void DrawableContainer<TDrawableComponentPointer>::ClearDrawableComponents()
{
    _drawableComponents.clear();
}

template<Pointer TDrawableComponentPointer>
void DrawableContainer<TDrawableComponentPointer>::UpdatePosition() const
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

template<Pointer TDrawableComponentPointer>
void DrawableContainer<TDrawableComponentPointer>::UpdateSize() const
{
    *_size = {_bottomRightPosition->x - _position->x, _bottomRightPosition->y - _position->y};

    auto itEnd {_drawableComponents.cend()};

    for (auto it {_drawableComponents.begin()}; it != itEnd; ++it)
    {
        (*it)->OnParentSizeUpdated();
    }
}

template<Pointer TDrawableComponentPointer>
float DrawableContainer<TDrawableComponentPointer>::CalculatePositionLeft() const
{
    float parentSizeX {GetParentSize().x};

    float startPoint {CalculateStartPoint(GetParentPosition().x, parentSizeX, _anchors._min.x)};

    float halfSize {CalculateSize(_desiredSize.x, parentSizeX, _anchors._max.x, _anchors._min.x) / 2};

    float relativePoint {CalculateRelativePoint(_relativePosition.x,
        -(_desiredSize.x / 2) * Utilities::Math::Absolute(_anchors._max.x - _anchors._min.x - 1))};

    relativePoint += halfSize + halfSize * -(_pivot.GetXPivot() * 2);

    return startPoint + relativePoint;
}

template<Pointer TDrawableComponentPointer>
float DrawableContainer<TDrawableComponentPointer>::CalculatePositionTop() const
{
    float parentSizeY {GetParentSize().y};

    float startPoint {CalculateStartPoint(GetParentPosition().y, parentSizeY, _anchors._min.y)};

    float relativePoint {CalculateRelativePoint(_relativePosition.y,
        -(_desiredSize.y / 2)  * Utilities::Math::Absolute(_anchors._max.y - _anchors._min.y - 1))};

    float halfSize {CalculateSize(_desiredSize.y, parentSizeY, _anchors._max.y, _anchors._min.y) / 2};

    relativePoint += halfSize + halfSize * -(_pivot.GetYPivot() * 2);

    return startPoint + relativePoint;
}

template<Pointer TDrawableComponentPointer>
float DrawableContainer<TDrawableComponentPointer>::CalculatePositionRight() const
{
    float parentSizeX {GetParentSize().x};

    float startPoint {CalculateStartPoint(GetParentBottomRightPosition().x, -parentSizeX, 1 - _anchors._max.x)};

    float relativePoint {CalculateRelativePoint(_relativePosition.x,
        (_desiredSize.x / 2) * Utilities::Math::Absolute(_anchors._max.x - _anchors._min.x - 1))};

    float halfSize {CalculateSize(_desiredSize.x, parentSizeX, _anchors._max.x, _anchors._min.x) / 2};

    relativePoint += halfSize + halfSize * -(_pivot.GetXPivot() * 2);

    return startPoint + relativePoint;
}

template<Pointer TDrawableComponentPointer>
float DrawableContainer<TDrawableComponentPointer>::CalculatePositionBottom() const
{
    float parentSizeY {GetParentSize().y};

    float startPoint {CalculateStartPoint(GetParentBottomRightPosition().y, -parentSizeY, 1 - _anchors._max.y)};

    float relativePoint {CalculateRelativePoint(_relativePosition.y,
        (_desiredSize.y / 2) * Utilities::Math::Absolute(_anchors._max.y - _anchors._min.y - 1))};

    float halfSize {CalculateSize(_desiredSize.y, parentSizeY, _anchors._max.y, _anchors._min.y) / 2};

    relativePoint += halfSize + halfSize * -(_pivot.GetYPivot() * 2);

    return startPoint + relativePoint;
}

template<Pointer TDrawableComponentPointer>
float DrawableContainer<TDrawableComponentPointer>::CalculateStartPoint(float parentPosition, float parentSize, float multiplier)
{
    return parentPosition + parentSize * multiplier;
}

template<Pointer TDrawableComponentPointer>
float DrawableContainer<TDrawableComponentPointer>::CalculateRelativePoint(float relativePosition, float size)
{
    return relativePosition + size;
}

template<Pointer TDrawableComponentPointer>
float DrawableContainer<TDrawableComponentPointer>::CalculateSize(float desiredSize, float parentSize, float maxAnchor, float minAnchor)
{
    float multiplier {maxAnchor - minAnchor};

    return desiredSize * Utilities::Math::Absolute(multiplier - 1) + parentSize * multiplier;
}