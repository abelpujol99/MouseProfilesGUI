#include "Input/Strategy/KeyInputStrategy.h"

#include <iostream>

#include "Managers/DevicesManager.h"
#include "State/Key/PressKeyState.h"

KeyInputStrategy::KeyInputStrategy(std::vector<std::unique_ptr<KeyInputCommands const>>&& buttonInputCommands) :
    _keyState(std::make_unique<PressKeyState>(this)), _keyInputCommands(std::move(buttonInputCommands))
{}

KeyInputStrategy::~KeyInputStrategy()
{
    DevicesManager::GetInstance().UnsubscribeToTriggerKeyHoldCommand(std::move(_subscriptionToTriggerHoldCommand));
}

void KeyInputStrategy::ChangeProfile(uint8_t profileIndex)
{
    _mutex.lock();
    _currentKeyInputCommand = _keyInputCommands[profileIndex].get();
    _mutex.unlock();
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
        _mutex.lock();
        if (_currentKeyInputCommand->GetHoldCommand() != nullptr)
        {
            FirstHoldDelay(deviceId);
        }
        _mutex.unlock();
    });
}

void KeyInputStrategy::Hold(DeviceId deviceId)
{
    if (_currentKeyInputCommand == nullptr)
    {
        return;
    }

    _currentKeyInputCommand->Hold(deviceId);
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

    if (_currentKeyInputCommand->GetHoldCommand()->GetMillisToStart() > _timeElapsed)
    {
        return;
    }

    Hold(deviceId);

    _timeElapsed = Duration(0);

    DevicesManager::GetInstance().UnsubscribeToTriggerKeyHoldCommand(std::move(_subscriptionToTriggerHoldCommand));

    _subscriptionToTriggerHoldCommand = DevicesManager::GetInstance().SubscribeToTriggerKeyHoldCommand([&, deviceId]()
    {
        _mutex.lock();
        if (_currentKeyInputCommand->GetHoldCommand() != nullptr)
        {
            HoldDelay(deviceId);
        }
        _mutex.unlock();

    });
}

void KeyInputStrategy::HoldDelay(DeviceId deviceId)
{
    TimePoint currentTimePoint {SystemClock::now()};

    Duration difference {currentTimePoint - _previousTimePoint};

    _timeElapsed += difference;

    _previousTimePoint = currentTimePoint;

    if (_currentKeyInputCommand->GetHoldCommand()->GetMillisToRepeat() > _timeElapsed)
    {
        return;
    }

    //std::cout << "Trigger" << std::endl;

    Hold(deviceId);

    _timeElapsed = Duration(0);
}