#include "Input/Strategy/WheelTiltInputCommandStrategy.h"

#include "Managers/ProfileManager.h"
#include "State/Wheel/WheelTiltPressStateAction.h"

WheelTiltInputCommandStrategy::WheelTiltInputCommandStrategy(std::vector<std::unique_ptr<WheelTiltInputCommand>>&& wheelNegativeInputCommands,
    std::vector<std::unique_ptr<WheelTiltInputCommand>>&& wheelPositiveInputCommands) :
        _wheelNegativeTiltInputState(std::make_unique<WheelTiltPressStateAction>(this)),
        _wheelPositiveTiltInputState(std::make_unique<WheelTiltPressStateAction>(this)),
        _wheelNegativeInputCommands(std::move(wheelNegativeInputCommands)),
        _wheelPositiveInputCommands(std::move(wheelPositiveInputCommands))
{}

void WheelTiltInputCommandStrategy::ChangeProfile(int profileIndex)
{
    _currentWheelNegativeInputCommand = _wheelNegativeInputCommands[profileIndex].get();
    _currentWheelPositiveInputCommand = _wheelPositiveInputCommands[profileIndex].get();
}

void WheelTiltInputCommandStrategy::ChangeState(std::unique_ptr<IWheelTiltInputStateAction>&& wheelTiltInputState)
{
    _wheelNegativeTiltInputState = std::move(wheelTiltInputState);
}

void WheelTiltInputCommandStrategy::RegisterValue(int value)
{
    if (value < 0)
    {
        _currentWheelInputCommand = _currentWheelNegativeInputCommand;
        _wheelNegativeTiltInputState->OnReceiveInputEvent();
    }
    else if (value > 0)
    {
        _currentWheelInputCommand = _currentWheelPositiveInputCommand;
        _wheelPositiveTiltInputState->OnReceiveInputEvent();
    }
}

void WheelTiltInputCommandStrategy::Press() const
{
    UpdateWheelTiltInputCommandPressRegister();
    _currentWheelInputCommand->Press();
}

void WheelTiltInputCommandStrategy::Hold()
{
    _currentWheelInputCommand->Hold();
}

void WheelTiltInputCommandStrategy::Release()
{
    ChangeState(std::make_unique<WheelTiltPressStateAction>(this));
    _currentWheelInputCommand->Release();
}

void WheelTiltInputCommandStrategy::DelegateHoldCommand()
{
    ProfileManager::GetInstance().ChangeMouseInputState(this);
}

void WheelTiltInputCommandStrategy::StopHoldCommand()
{

}

void WheelTiltInputCommandStrategy::UpdateWheelTiltInputCommandPressRegister() const
{
    _currentWheelInputCommand->UpdateLastPressRegister();
}

const Duration& WheelTiltInputCommandStrategy::GetMillisUntilInputStops() const
{
    return _currentWheelInputCommand->GetMillisUntilInputStops();
}

const Duration & WheelTiltInputCommandStrategy::GetFirstTimeDelay() const
{
    return _currentWheelInputCommand->GetFirstDelayInMillis();
}

const Duration & WheelTiltInputCommandStrategy::GetMillisToRepeatInput() const
{
    return _currentWheelInputCommand->GetMillisUntilInputStops();
}

bool WheelTiltInputCommandStrategy::IsHolding() const
{
    return _currentWheelInputCommand->IsHolding();
}
