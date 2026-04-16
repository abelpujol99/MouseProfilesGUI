#include "Frontend/UI/Elements/Advanced/Button.h"

#include "Frontend/Managers/Gesture/GestureManager.h"
#include "Frontend/Managers/Gesture/MouseButton/MouseButtons.h"
#include "Frontend/Managers/Input/ClickableManager.h"

Button::Button(std::function<void()>&& action, bool isHidden) :
        DrawableComponent(isHidden), _action(action)
{
    ClickableManager::GetInstance().AddClickable(this);
}

Button::~Button() noexcept
{
    ClickableManager::GetInstance().RemoveClickable(this);
}

void Button::SetRectangle(std::unique_ptr<Rectangle>&& rectangle)
{
    _rectangle = std::move(rectangle);
}

void Button::SetText(std::unique_ptr<Text>&& text)
{
    _text = std::move(text);
}

void Button::SetParentAttributes(ImVec2* parentPosition, ImVec2* parentBottomRightPosition, ImVec2* parentSize,
        bool* isParentHidden)
{
    DrawableComponent::SetParentAttributes(parentPosition, parentBottomRightPosition, parentSize, isParentHidden);

    _rectangle->SetParentAttributes(parentPosition, parentBottomRightPosition, parentSize, isParentHidden);

    _text->SetParentAttributes(parentPosition, parentBottomRightPosition, parentSize, isParentHidden);
}

ImVec2 Button::GetParentPosition() const
{
    return DrawableComponent::GetParentPosition();
}

ImVec2 Button::GetParentBottomRightPosition() const
{
    return DrawableComponent::GetParentBottomRightPosition();
}

bool Button::CanBeClicked() const
{
    return !_isHidden;
}

void Button::Click()
{
    _action();
}

void Button::Draw(ImDrawList* drawList)
{
    if (MustBeHidden())
    {
        return;
    }

    _rectangle->Draw(drawList);

    _text->Draw(drawList);
}
