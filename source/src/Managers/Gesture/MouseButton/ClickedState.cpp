#include "Managers/Gesture/MouseButton/ClickedState.h"

#include "Factories/ImGui/ImGuiFactory.h"
#include "Managers/Gesture/GestureManager.h"

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