#include "Managers/Input/MouseButton/ReleasedState.h"

#include "Factory/ImGuiFactory.h"
#include "Managers/Input/InputManager.h"

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