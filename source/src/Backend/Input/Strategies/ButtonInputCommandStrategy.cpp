#include "Backend/Input/Strategy/ButtonInputCommandStrategy.h"

#include "Backend/Managers/ProfileManager.h"
#include "Backend/State/Button/ButtonPressStateAction.h"

ButtonInputCommandStrategy::ButtonInputCommandStrategy(std::vector<std::unique_ptr<ButtonInputCommand>>&& buttonInputCommands) :
    _buttonInputState(std::make_unique<ButtonPressStateAction>(this)), _buttonInputCommands(std::move(buttonInputCommands))
{}

void ButtonInputCommandStrategy::ChangeProfile(int profileIndex)
{
    _currentButtonInputCommand = _buttonInputCommands[profileIndex].get();
}

void ButtonInputCommandStrategy::ChangeState(std::unique_ptr<IButtonInputStateAction>&& buttonInputState)
{
    _buttonInputState = std::move(buttonInputState);
}

void ButtonInputCommandStrategy::RegisterValue(int value)
{
    if (value == _state)
    {
        return;
    }

    _buttonInputState->OnReceiveInputEvent();
}

void ButtonInputCommandStrategy::Press()
{
    _state = 1;
    _currentButtonInputCommand->Press();
}

void ButtonInputCommandStrategy::Hold()
{
    _currentButtonInputCommand->Hold();
}

void ButtonInputCommandStrategy::Release()
{
    _currentButtonInputCommand->Release();
}

void ButtonInputCommandStrategy::DelegateHoldCommand()
{
    if (!_currentButtonInputCommand->HasHoldCommand())
    {
        return;
    }

    ProfileManager::GetInstance().ChangeMouseInputState(this);
}

void ButtonInputCommandStrategy::StopHoldCommand()
{

}

void ButtonInputCommandStrategy::SwitchToOffState()
{
    _state = 0;

    if (_currentButtonInputCommand->HasHoldCommand())
    {
        return;
    }

    Release();
}

const Duration& ButtonInputCommandStrategy::GetFirstTimeDelay() const
{
    return _currentButtonInputCommand->GetFirstDelayInMillis();
}

const Duration & ButtonInputCommandStrategy::GetMillisToRepeatInput() const
{
    return _currentButtonInputCommand->GetMillisToRepeatInput();
}

bool ButtonInputCommandStrategy::IsHolding() const
{
    return _state == 1;
}
