#pragma once
#include "Frontend/UI/Elements/Base/DrawableContainer.h"

#include <memory>

#include "Frontend/UI/Elements/Base/DrawableComponent.h"
#include "Frontend/Utilities/Anchors.h"

class RectDrawable : public DrawableContainer<std::unique_ptr<DrawableComponent>>
{
public:

    RectDrawable(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden);

    ~RectDrawable() override = default;

    void OnUpdateParentTransformImplementation() override;

    void OnUpdateAnchorsImplementation() override;

    void OnUpdatePivotImplementation() override;

    void OnUpdateRelativePositionImplementation() override;

    void OnUpdateDesiredSizeImplementation() override;

    void OnUpdateAttributesImplementation() override;

    void AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable);

    void RemoveRectDrawable(RectDrawable* rectDrawable);

    void AddDrawableComponent(std::unique_ptr<DrawableComponent>&& drawableComponent);

    void RemoveDrawableComponent(DrawableComponent* drawableComponent) override;

    void UpdateRectDrawablesPosition();

    void UpdateRectDrawables();

    void Draw(ImDrawList* drawList) override;

private:

    template<Pointer TDrawablePointer>
    static void DrawDrawables(const std::forward_list<TDrawablePointer>& drawables, ImDrawList* drawList);

    std::forward_list<std::unique_ptr<RectDrawable>> _rectDrawables;
};

template<Pointer TDrawablePointer>
void RectDrawable::DrawDrawables(const std::forward_list<TDrawablePointer>& drawables, ImDrawList* drawList)
{
    auto itEnd {drawables.cend()};

    for (auto it {drawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}