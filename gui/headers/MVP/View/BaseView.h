#pragma once
#include <forward_list>
#include <functional>

#include "UI/Elements/Base/RectDrawable.h"

#include "Managers/View/WindowManager.h"

class BaseView : public BaseDisplay, public DrawableTransform
{
public:

    BaseView(bool isHidden);

    ~BaseView() override = default;

    void AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable);

    void RemoveRectDrawable(RectDrawable* rectDrawable);

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    [[nodiscard]] ImVec2 GetParentSize() const override;

    void Draw(ImDrawList* drawList) override;

private:

    void UpdateRectDrawables() const;

    std::weak_ptr<std::function<void(WindowSize)>> _onSizeChangeWeakAction;

    std::forward_list<std::unique_ptr<RectDrawable>> _rectDrawables;
};

