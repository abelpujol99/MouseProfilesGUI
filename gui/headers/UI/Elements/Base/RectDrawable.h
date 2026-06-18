#pragma once
#include "UI/Elements/Base/DrawableTransform.h"

#include <set>

#include "UI/Elements/Base/DrawableComponent.h"
#include "UI/Structs/RectDrawableData.h"
#include "Utilities/UI/Anchors.h"
#include "Utilities/UI/Pivot.h"
#include "Utilities/Concepts/Pointer.h"

class RectDrawable : public BaseDrawable, public DrawableTransform
{
public:

    RectDrawable(RectDrawableData&& rectDrawableData, bool isHidden);

    ~RectDrawable() override = default;

    void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer,
        bool* isParentHiddenPointer) override;

    void SetAnchors(Anchors&& anchors);

    void SetPivot(Pivot&& pivot);

    void SetRelativePosition(ImVec2&& relativePosition);

    [[nodiscard]] ImVec2 GetRelativePosition() const;

    void SetDesiredSize(ImVec2&& desiredSize);

    [[nodiscard]] ImVec2 GetSize() const;

    void UpdatePosition() const;

    void UpdateSize() const;

    void UpdateAttributes();

    void AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable);

    void RemoveRectDrawable(RectDrawable* rectDrawable);

    void ClearRectDrawables();

    void AddDrawableComponent(DrawableComponent* drawableComponent);

    void RemoveDrawableComponent(DrawableComponent* drawableComponent);

    void UpdateRectDrawablesPosition();

    void UpdateRectDrawables();

    void ClearDrawableComponents();

    void Enable() override;

    void Disable() override;

    void Draw(ImDrawList* drawList) override;

private:

    float CalculatePositionLeft() const;

    float CalculatePositionTop() const;

    float CalculatePositionRight() const;

    float CalculatePositionBottom() const;

    static float CalculateStartPoint(float parentPosition, float parentSize, float multiplier);

    static float CalculateRelativePoint(float relativePosition, float size);

    static float CalculateSize(float desiredSize, float parentSize, float maxAnchor, float minAnchor);

    template<Pointer TDrawablePointer>
    static void EnableDrawables(const std::set<TDrawablePointer>& drawables);

    template<Pointer TDrawablePointer>
    static void DisableDrawables(const std::set<TDrawablePointer>& drawables);

    template<Pointer TDrawablePointer>
    static void DrawDrawables(const std::set<TDrawablePointer>& drawables, ImDrawList* drawList);

    Anchors _anchors;

    Pivot _pivot;

    ImVec2 _relativePosition;

    ImVec2 _desiredSize;

    std::set<DrawableComponent*> _drawableComponents;

    std::set<std::unique_ptr<RectDrawable>> _rectDrawables;
};

template <Pointer TDrawablePointer>
void RectDrawable::EnableDrawables(const std::set<TDrawablePointer>& drawables)
{
    auto itEnd {drawables.cend()};

    for (auto it {drawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Enable();
    }
}

template <Pointer TDrawablePointer>
void RectDrawable::DisableDrawables(const std::set<TDrawablePointer>& drawables)
{
    auto itEnd {drawables.cend()};

    for (auto it {drawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Disable();
    }
}

template<Pointer TDrawablePointer>
void RectDrawable::DrawDrawables(const std::set<TDrawablePointer>& drawables, ImDrawList* drawList)
{
    auto itEnd {drawables.cend()};

    for (auto it {drawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}
