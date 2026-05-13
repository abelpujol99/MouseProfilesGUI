#pragma once
#include <forward_list>
#include <functional>

#include "Frontend/UI/Elements/Base/RectDrawable.h"

class Canvas : public BaseDisplay, public DrawableTransform
{
public:

    Canvas(bool isHidden);

    ~Canvas() override = default;

    void AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable);

    void RemoveRectDrawable(RectDrawable* rectDrawable);

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    [[nodiscard]] ImVec2 GetParentSize() const override;

    virtual void Enable() = 0;

    virtual void Disable() = 0;

    void Draw(ImDrawList* drawList) override;

private:

    void UpdateRectDrawables() const;

    std::weak_ptr<std::function<void(ImVec2)>> _onSizeChangeWeakAction;

    std::forward_list<std::unique_ptr<RectDrawable>> _rectDrawables;
};