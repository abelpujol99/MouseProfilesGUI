#pragma once

#include "Frontend/UI/Elements/Intermediate/Rectangle.h"
#include "Frontend/UI/Elements/Intermediate/Text.h"

class Button : public DrawableComponent
{

public:

    Button(std::function<void()>&& action, bool isHidden);

    ~Button() override = default;

    void SetRectangle(std::unique_ptr<Rectangle>&& rectangle);

    void SetText(std::unique_ptr<Text>&& text);

    void SetParentTransform(ImVec2 *parentPosition, ImVec2 *parentSize) override;

    void SetBottomRightPositionPointer(ImVec2 *bottomRightPositionPointer) override;

    void Draw(ImDrawList *drawList) override;

private:

    std::unique_ptr<Rectangle> _rectangle;

    std::unique_ptr<Text> _text;

    std::weak_ptr<std::function<void(bool)>> _onLeftMouseButtonReleasedWeakAction;

    bool _hasLeftMouseButtonReleased;

    std::function<void()> _action;
};