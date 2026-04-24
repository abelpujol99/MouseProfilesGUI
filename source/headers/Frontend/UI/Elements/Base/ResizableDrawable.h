#pragma once
#include "DrawableContainer.h"

class ResizableDrawable : public DrawableContainer<DrawableComponent*>
{
public:

    ResizableDrawable(Anchors&& anchors, ImVec2&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden);

    ~ResizableDrawable() override = default;

    void AddResizableDrawable(std::unique_ptr<ResizableDrawable>&& resizableDrawable);

    void RemoveResizableDrawable(ResizableDrawable* resizableDrawable);

    void AddDrawableComponent(DrawableComponent* drawableComponent);

    void RemoveDrawableComponent(DrawableComponent* drawableComponent) override;

    void Draw(ImDrawList* drawList) override;

private:

    void OnUpdateParentTransform() override;

    void OnUpdateAnchorsImplementation() override;

    void OnUpdatePivotImplementation() override;

    void OnUpdateRelativePositionImplementation() override;

    void OnUpdateDesiredSizeImplementation() override;

    void OnUpdateAttributesImplementation() override;

    std::forward_list<std::unique_ptr<ResizableDrawable>> _resizableDrawables;
};
