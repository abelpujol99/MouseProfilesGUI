#include "Frontend/Managers/Input/MouseButton/ReleasedState.h"

#include "Frontend/Factory/ImGuiFactory.h"
#include "Frontend/Managers/Input/InputManager.h"

ReleasedState::ReleasedState(MouseButtons mouseButton) : BaseMouseButtonState(mouseButton)
{}

void ReleasedState::CheckState()
{
    bool state {ImGuiFactory::IsMouseButtonPressed(_mouseButton)};
    
    if (!state)
    {
        return;
    }

    InputManager::GetInstance().OnPressButton(_mouseButton);
}