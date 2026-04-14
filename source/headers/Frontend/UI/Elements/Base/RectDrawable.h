#pragma once
#include "BaseDrawable.h"

#include <forward_list>
#include <memory>

#include "Frontend/UI/Elements/Base/DrawableComponent.h"
#include "Frontend/Utilities/Anchors.h"
#include "Frontend/Utilities/Concepts/DerivedFromBaseDrawable.h"

class RectDrawable : public BaseDrawable
{
public:

    RectDrawable(Anchors&& anchors, ImVec2&& pivot, ImVec2&& relativePosition, ImVec2&& desiredSize, bool isHidden);

    ~RectDrawable() override = default;

    void SetDesiredSize(ImVec2&& desiredSize);

    void UpdateSize() const;

    void SetRelativePosition(ImVec2&& relativePosition);

    void UpdatePosition() const;

    void UpdateRectDrawables() const;

    void AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable);

    void AddDrawableComponent(std::unique_ptr<DrawableComponent>&& baseDrawable);

    void Draw(ImDrawList* drawList) override;

protected:

    template<DerivedFromBaseDrawable TDrawable>
    static void DrawDrawables(const std::forward_list<std::unique_ptr<TDrawable>>& drawables, ImDrawList* drawList);

    Anchors _anchors;

    ImVec2 _pivot;

    ImVec2 _relativePosition;

    ImVec2 _desiredSize;

    std::unique_ptr<ImVec2> _position {std::make_unique<ImVec2>()};

    std::unique_ptr<ImVec2> _bottomRightPosition {std::make_unique<ImVec2>()};

    std::unique_ptr<ImVec2> _size {std::make_unique<ImVec2>()};

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
