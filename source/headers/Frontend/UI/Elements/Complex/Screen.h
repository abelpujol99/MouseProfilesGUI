#pragma once
#include <functional>

#include "Frontend/UI/Elements/Complex/Screen.h"

#include "Frontend/UI/Elements/Base/RectDrawable.h"

class Screen : public BaseDisplay
{
public:

    Screen(bool isHidden);

    ~Screen() override = default;

    void AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable);

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    [[nodiscard]] ImVec2 GetParentSize() const override;

    void Draw(ImDrawList* drawList) override;

private:

    void UpdateRectDrawables() const;

    std::unique_ptr<ImVec2> _position;

    std::unique_ptr<ImVec2> _bottomRightPosition;

    std::weak_ptr<std::function<void(ImVec2)>> _onSizeChangeWeakAction;

    std::unique_ptr<ImVec2> _size;

    std::forward_list<std::unique_ptr<RectDrawable>> _rectDrawables;
};