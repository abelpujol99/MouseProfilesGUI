#pragma once
#include "Input/Strategy/IInputCommandStrategy.h"

#include <functional>

#include "Input/Key/KeyInputCommand.h"
#include "State/Key/IKeyState.h"


class KeyInputStrategy : public IInputCommandStrategy
{
public:

    KeyInputStrategy(std::vector<std::unique_ptr<KeyInputCommand const>>&& buttonInputCommands, CommandDelay&& commandDelay);

    void ChangeProfile(uint8_t profileIndex) override;

    void ChangeState(std::unique_ptr<IKeyState>&& keyState);

    void RegisterValue(DeviceId deviceId, int value) const;

    void Press(DeviceId deviceId);

    void Hold(DeviceId deviceId);

    void Release(DeviceId deviceId);

    [[nodiscard]] bool IsHolding() const;

private:

    void FirstHoldDelay(DeviceId deviceId);

    void HoldDelay(DeviceId deviceId);

    std::unique_ptr<IKeyState> _keyState;

    bool _isPressed {false};

    std::vector<std::unique_ptr<KeyInputCommand const>> _keyInputCommands;

    const KeyInputCommand* _currentKeyInputCommand {nullptr};

    const CommandDelay _commandDelay;

    Duration _timeElapsed;

    TimePoint _previousTimePoint;

    std::weak_ptr<std::function<void()>> _subscriptionToTriggerHoldCommand;
};