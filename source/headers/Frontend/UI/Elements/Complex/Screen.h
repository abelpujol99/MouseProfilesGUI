#pragma once
#include "Frontend/UI/Elements/Complex/Screen.h"

#include "Frontend/UI/Elements/Base/RectDrawable.h"

class Screen : public BaseDisplay
{
public:

    Screen(ImVec2&& position, ImVec2&& size, bool isHidden);

    ~Screen() override = default;

    void AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable);

    [[nodiscard]] ImVec2 GetPosition() const override;

    [[nodiscard]] ImVec2 GetBottomRightPosition() const override;

    [[nodiscard]] ImVec2 GetSize() const override;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<ImVec2> _position;

    std::unique_ptr<ImVec2> _size;

    std::forward_list<std::unique_ptr<RectDrawable>> _rectDrawables;
};