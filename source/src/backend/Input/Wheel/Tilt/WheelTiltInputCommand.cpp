#include <WheelTiltInputCommand.h>

#include <ICommand.h>

WheelTiltInputCommand::WheelTiltInputCommand(std::unique_ptr<ICommand>&& commandOnPress,
    std::unique_ptr<ICommand>&& commandOnHold, std::unique_ptr<ICommand>&& commandOnRelease, Duration&& firstDelayInMillis,
        Duration&& millisToRepeatInput, Duration&& millisUntilInputStops) : InputCommand(std::move(firstDelayInMillis), std::move(millisToRepeatInput)),
            _commandOnPress(std::move(commandOnPress)), _commandOnHold(std::move(commandOnHold)),
                _commandOnRelease(std::move(commandOnRelease)), _millisUntilInputStops(std::move(millisUntilInputStops))
{}

void WheelTiltInputCommand::UpdateLastPressRegister()
{
    _lastPressRegisterTime = std::chrono::system_clock::now();
}

const Duration& WheelTiltInputCommand::GetMillisUntilInputStops() const
{
    return _millisUntilInputStops;
}

void WheelTiltInputCommand::Press() const
{
    if (!_commandOnPress)
    {
        return;
    }

    _commandOnPress->Execute();
}

void WheelTiltInputCommand::Hold() const
{
    if (!_commandOnHold)
    {
        return;
    }

    _commandOnHold->Execute();
}

void WheelTiltInputCommand::Release() const
{
    if (!_commandOnRelease)
    {
        return;
    }

    _commandOnRelease->Execute();
}

bool WheelTiltInputCommand::IsHolding() const
{
    return _millisUntilInputStops < SystemClock::now() - _lastPressRegisterTime;
}