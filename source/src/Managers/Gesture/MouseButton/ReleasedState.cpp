#include "Managers/Gesture/MouseButton/ReleasedState.h"

#include "Factories/ImGui/ImGuiFactory.h"
#include "Managers/Gesture/GestureManager.h"
#include "Managers/Gesture/MouseButton/ClickedState.h"

ReleasedState::ReleasedState(MouseButtons mouseButton) : BaseMouseButtonState(mouseButton)
{}

void ReleasedState::CheckState()
{
    bool state {ImGuiFactory::IsMouseButtonPressed(_mouseButton)};
    
    if (!state)
    {
        return;
    }

    GestureManager::GetInstance().OnPressButton(_mouseButton);
}