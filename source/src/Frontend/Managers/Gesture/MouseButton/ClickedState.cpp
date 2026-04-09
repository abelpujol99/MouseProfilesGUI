#include "Frontend/Managers/Gesture/MouseButton/ClickedState.h"

#include "Frontend/Factory/ImGuiFactory.h"
#include "Frontend/Managers/Gesture/GestureManager.h"

ClickedState::ClickedState(MouseButtons mouseButton) : BaseMouseButtonState(mouseButton)
{}

void ClickedState::CheckState()
{
    bool state {ImGuiFactory::IsMouseButtonReleased(_mouseButton)};
    
    if (!state)
    {
        return;
    }

    GestureManager::GetInstance().OnReleaseButton(_mouseButton);
}