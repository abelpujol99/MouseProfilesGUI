#pragma once
#include "Frontend/UI/Elements/Base/BaseDrawable.h"
#include "Frontend/UI/Elements/Base/DrawableTransform.h"

#include <forward_list>
#include <memory>

#include "Frontend/UI/Elements/Base/DrawableComponent.h"
#include "Frontend/Utilities/Anchors.h"
#include "Frontend/Utilities/Concepts/DerivedFromBaseDrawable.h"

class RectDrawable : public BaseDrawable, public DrawableTransform
{
public:

    RectDrawable(Anchors&& anchors, ImVec2&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden);

    ~RectDrawable() override = default;

    void SetParentTransform(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer) override;

    void SetAnchors(Anchors&& anchors);

    void SetPivot(ImVec2&& pivot);

    void SetRelativePosition(ImVec2&& relativePosition);

    [[nodiscard]] ImVec2 GetRelativePosition() const;

    void SetDesiredSize(ImVec2&& desiredSize);

    void UpdateAttributes();

    void AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable);

    void RemoveRectDrawable(RectDrawable* rectDrawable);

    void AddDrawableComponent(std::unique_ptr<DrawableComponent>&& baseDrawable);

    void Draw(ImDrawList* drawList) override;

private:

    void UpdatePosition() const;

    void UpdateSize() const;

    void UpdateRectDrawablesPosition();

    void UpdateRectDrawables();

    float CalculatePositionLeft() const;

    float CalculatePositionTop() const;

    float CalculatePositionRight() const;

    float CalculatePositionBottom() const;

    static float CalculateStartPoint(float parentPosition, float parentSize, float multiplier);

    static float CalculateRelativePoint(float relativePosition, float size);

    static float CalculateSize(float desiredSize, float parentSize, float maxAnchor, float minAnchor);

    template<DerivedFromBaseDrawable TDrawable>
    static void DrawDrawables(const std::forward_list<std::unique_ptr<TDrawable>>& drawables, ImDrawList* drawList);

    Anchors _anchors;

    ImVec2 _pivot;

    ImVec2 _relativePosition;

    ImVec2 _desiredSize;

    std::forward_list<std::unique_ptr<RectDrawable>> _rectDrawables;

    std::forward_list<std::unique_ptr<DrawableComponent>> _drawableComponents;
};

template<DerivedFromBaseDrawable TDrawable>
void RectDrawable::DrawDrawables(const std::forward_list<std::unique_ptr<TDrawable>>& drawables,
    ImDrawList* drawList)
{
    auto itEnd {drawables.cend()};

    for (auto it {drawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}
