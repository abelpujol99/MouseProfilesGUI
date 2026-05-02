#pragma once
#include "Frontend/UI/Elements/Base/DrawableContainer.h"

class ResizableDrawable : public DrawableContainer<DrawableComponent*>
{
public:

    ResizableDrawable(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden);

    ~ResizableDrawable() override = default;

    void UpdateResizableDrawables();

    void UpdateResizableDrawablePosition();

    void AddResizableDrawable(std::unique_ptr<ResizableDrawable>&& resizableDrawable);

    void RemoveResizableDrawable(ResizableDrawable* resizableDrawable);

    void AddDrawableComponent(DrawableComponent* drawableComponent);

    void RemoveDrawableComponent(DrawableComponent* drawableComponent) override;

    void Draw(ImDrawList* drawList) override;

private:

    void OnUpdateParentTransformImplementation() override;

    void OnUpdateAnchorsImplementation() override;

    void OnUpdatePivotImplementation() override;

    void OnUpdateRelativePositionImplementation() override;

    void OnUpdateDesiredSizeImplementation() override;

    void OnUpdateAttributesImplementation() override;

    template<Pointer TDrawableComponentPointer>
    static void DrawDrawables(const std::forward_list<TDrawableComponentPointer>& drawables, ImDrawList* drawList);

    std::forward_list<std::unique_ptr<ResizableDrawable>> _resizableDrawables;
};

template<Pointer TDrawableComponentPointer>
void ResizableDrawable::DrawDrawables(const std::forward_list<TDrawableComponentPointer>& drawables,
    ImDrawList* drawList)
{
    auto itEnd {drawables.cend()};

    for (auto it {drawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}