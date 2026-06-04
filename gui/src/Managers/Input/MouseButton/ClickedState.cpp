#include "Managers/Input/MouseButton/ClickedState.h"

#include "Factory/ImGuiFactory.h"
#include "Managers/Input/InputManager.h"

ClickedState::ClickedState(MouseButtons mouseButton) : BaseMouseButtonState(mouseButton)
{}

void ClickedState::CheckState()
{
    bool state {ImGuiFactory::IsMouseButtonReleased(_mouseButton)};
    
    if (!state)
    {
        return;
    }

    InputManager::GetInstance().OnReleaseButton(_mouseButton);
}