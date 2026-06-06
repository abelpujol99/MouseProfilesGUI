#include "UI/Elements/Advanced/Button.h"

#include "Managers/Gestures/ClickableManager.h"

Button::Button(std::function<void()>&& action, bool isHidden) :
        DrawableComponent(isHidden), _action(action)
{
    Subscribe();
}

Button::~Button() noexcept
{
    Unsubscribe();
}

void Button::SetIsHidden(bool isHidden)
{
    DrawableComponent::SetIsHidden(isHidden);

    _rectangle->SetIsHidden(isHidden);

    _text->SetIsHidden(isHidden);
}

void Button::SetRectangle(std::unique_ptr<Rectangle>&& rectangle)
{
    _rectangle = std::move(rectangle);
}

void Button::SetTextComponent(std::unique_ptr<Text>&& text)
{
    _text = std::move(text);
}

void Button::SetText(std::string&& text)
{
    _text->SetText(text);
}

void Button::SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    BaseDrawable::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    _rectangle->SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    _text->SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);
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
    return !IsHidden();
}

void Button::SetAction(std::function<void()>&& action)
{
    _action = action;
}

void Button::Click()
{
    _action();
}

void Button::Subscribe()
{
    ClickableManager::GetInstance().AddClickable(this);
}

void Button::Unsubscribe()
{
    ClickableManager::GetInstance().RemoveClickable(this);
}

void Button::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    _rectangle->Draw(drawList);

    _text->Draw(drawList);
}
