#include "Frontend/UI/Elements/Advanced/Button.h"

#include "Frontend/Managers/Gesture/GestureManager.h"
#include "Frontend/Managers/Gesture/MouseButton/MouseButtons.h"

Button::Button(std::function<void()>&& action, bool isHidden) :
        DrawableComponent(isHidden), _action(action)
{
    _onLeftMouseButtonReleasedWeakAction = GestureManager::GetInstance().SubscribeToMouseButtonReleaseEvent(MouseButtons::LEFT,
            [&](bool value) {
                _hasLeftMouseButtonReleased = value;
        });
}

void Button::SetRectangle(std::unique_ptr<Rectangle>&& rectangle)
{
    _rectangle = std::move(rectangle);
}

void Button::SetText(std::unique_ptr<Text>&& text)
{
    _text = std::move(text);
}

void Button::SetParentTransform(ImVec2* parentPosition, ImVec2* parentBottomRightPosition, ImVec2* parentSize)
{
    DrawableComponent::SetParentTransform(parentPosition, parentBottomRightPosition, parentSize);

    _rectangle->SetParentTransform(parentPosition, parentBottomRightPosition, parentSize);

    _text->SetParentTransform(parentPosition, parentBottomRightPosition, parentSize);
}

void Button::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    _rectangle->Draw(drawList);

    _text->Draw(drawList);

    if (!_hasLeftMouseButtonReleased)
    {
        return;
    }

    _hasLeftMouseButtonReleased = false;

    _action();
}
