#include "Input/Strategy/KeyInputStrategy.h"

#include "Managers/DevicesManager.h"
#include "State/Key/PressKeyState.h"

KeyInputStrategy::KeyInputStrategy(std::vector<std::unique_ptr<KeyInputCommand const>>&& buttonInputCommands,
    CommandDelay&& commandDelay) : _keyState(std::make_unique<PressKeyState>(this)), _keyInputCommands(std::move(buttonInputCommands)),
    _commandDelay(std::move(commandDelay))
{}

void KeyInputStrategy::ChangeProfile(uint8_t profileIndex)
{
    _currentKeyInputCommand = _keyInputCommands[profileIndex].get();
}

void KeyInputStrategy::ChangeState(std::unique_ptr<IKeyState>&& keyState)
{
    _keyState = std::move(keyState);
}

void KeyInputStrategy::RegisterValue(DeviceId deviceId, int value) const
{
    if (value == _isPressed)
    {
        return;
    }

    _keyState->OnInput(deviceId);
}

void KeyInputStrategy::Press(DeviceId deviceId)
{
    _isPressed = true;

    if (_currentKeyInputCommand != nullptr)
    {
        _currentKeyInputCommand->Press(deviceId);
    }

    _previousTimePoint = SystemClock::now();

    _subscriptionToTriggerHoldCommand = DevicesManager::GetInstance().SubscribeToTriggerKeyHoldCommand([&, deviceId]()
    {
        FirstHoldDelay(deviceId);
    });
}

void KeyInputStrategy::Hold(DeviceId deviceId)
{
    if (_currentKeyInputCommand != nullptr)
    {
        _currentKeyInputCommand->Hold(deviceId);
    }
}

void KeyInputStrategy::Release(DeviceId deviceId)
{
    _isPressed = false;

    DevicesManager::GetInstance().UnsubscribeToTriggerKeyHoldCommand(std::move(_subscriptionToTriggerHoldCommand));

    if (_currentKeyInputCommand == nullptr)
    {
        return;
    }

    _currentKeyInputCommand->Release(deviceId);
}

bool KeyInputStrategy::IsHolding() const
{
    return _isPressed;
}

void KeyInputStrategy::FirstHoldDelay(DeviceId deviceId)
{
    TimePoint currentTimePoint {SystemClock::now()};

    Duration difference {currentTimePoint - _previousTimePoint};

    _timeElapsed += difference;

    _previousTimePoint = currentTimePoint;

    if (_commandDelay.GetFirstDelayInMillis() > _timeElapsed)
    {
        return;
    }

    Hold(deviceId);

    _timeElapsed = Duration(0);

    DevicesManager::GetInstance().UnsubscribeToTriggerKeyHoldCommand(std::move(_subscriptionToTriggerHoldCommand));

    _subscriptionToTriggerHoldCommand = DevicesManager::GetInstance().SubscribeToTriggerKeyHoldCommand([&, deviceId]()
    {
        HoldDelay(deviceId);
    });
}

void KeyInputStrategy::HoldDelay(DeviceId deviceId)
{
    TimePoint currentTimePoint {SystemClock::now()};

    Duration difference {currentTimePoint - _previousTimePoint};

    _timeElapsed += difference;

    _previousTimePoint = currentTimePoint;

    if (_commandDelay.GetMillisToRepeatCommand() > _timeElapsed)
    {
        return;
    }

    Hold(deviceId);

    _timeElapsed = Duration(0);
}