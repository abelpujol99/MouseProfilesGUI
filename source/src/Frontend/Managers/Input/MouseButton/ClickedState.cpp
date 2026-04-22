#include "Frontend/Managers/Input/MouseButton/ClickedState.h"

#include "Frontend/Factory/ImGuiFactory.h"
#include "Frontend/Managers/Input/InputManager.h"

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