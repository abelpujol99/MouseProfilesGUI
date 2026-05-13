#pragma once
#include "Frontend/UI/Helpers/IClickable.h"

#include "Frontend/UI/Elements/Intermediate/Rectangle.h"
#include "Frontend/UI/Elements/Intermediate/Text.h"

class Button : public DrawableComponent, public IClickable
{

public:

    Button(std::function<void()>&& action, bool isHidden);

    ~Button() noexcept override;

    void SetRectangle(std::unique_ptr<Rectangle>&& rectangle);

    void SetText(std::unique_ptr<Text>&& text);

    void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer,
        bool* isParentHiddenPointer) override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    [[nodiscard]] bool CanBeClicked() const override;

    void SetAction(std::function<void()>&& action);

    void Click() override;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<Rectangle> _rectangle;

    std::unique_ptr<Text> _text;

    std::function<void()> _action;
};