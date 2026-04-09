#include "Frontend/Managers/Gesture/MouseButton/ReleasedState.h"

#include "Frontend/Factory/ImGuiFactory.h"
#include "Frontend/Managers/Gesture/GestureManager.h"

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