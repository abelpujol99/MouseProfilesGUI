#include "Input/Strategy/KeyInputStrategy.h"

#include "Managers/ProfileManager.h"
#include "State/Key/PressKeyState.h"

KeyInputStrategy::KeyInputStrategy(std::vector<std::unique_ptr<KeyInputCommand const>>&& buttonInputCommands,
                                   CommandDelay&& commandDelay) :
    _keyState(std::make_unique<PressKeyState>(this)), _keyInputCommands(std::move(buttonInputCommands)),
    _commandDelay(std::move(commandDelay))
{}

void KeyInputStrategy::ChangeProfile(uint8_t profileIndex)
{
    _currentKeyInputCommand = _keyInputCommands[profileIndex].get();
}

void KeyInputStrategy::ChangeState(std::unique_ptr<IKeyState>&& buttonInputState)
{
    _keyState = std::move(buttonInputState);
}

void KeyInputStrategy::RegisterValue(int value)
{
    if (value == _isPressed)
    {
        return;
    }

    _keyState->OnInput();
}

void KeyInputStrategy::Press()
{
    _isPressed = true;
    _currentKeyInputCommand->Press();

    _previousTimePoint = SystemClock::now();

    //TODO SUBSCRIBE FIRST_HOLD_DELAY TO PROFILE MANAGER
}

void KeyInputStrategy::Hold()
{
    _currentKeyInputCommand->Hold();
}

void KeyInputStrategy::Release()
{
    _isPressed = false;

    //TODO UNSUBSCRIBE HOLD_DELAY FROM PROFILE MANAGER

    _currentKeyInputCommand->Release();
}

bool KeyInputStrategy::IsHolding() const
{
    return _isPressed;
}

void KeyInputStrategy::FirstHoldDelay()
{
    TimePoint currentTimePoint {SystemClock::now()};

    Duration difference {currentTimePoint - _previousTimePoint};

    _timeElapsed += difference;

    _previousTimePoint = currentTimePoint;

    if (_commandDelay.GetFirstDelayInMillis() > _timeElapsed)
    {
        return;
    }

    Hold();

    _timeElapsed = Duration(0);

    //TODO UNSUBSCRIBE FIRST_HOLD_DELAY FROM PROFILE MANAGER
    //TODO SUBSCRIBE HOLD_DELAY TO PROFILE MANAGER
}

void KeyInputStrategy::HoldDelay()
{
    TimePoint currentTimePoint {SystemClock::now()};

    Duration difference {currentTimePoint - _previousTimePoint};

    _timeElapsed += difference;

    _previousTimePoint = currentTimePoint;

    if (_commandDelay.GetMillisToRepeatCommand() > _timeElapsed)
    {
        return;
    }

    Hold();

    _timeElapsed = Duration(0);
}