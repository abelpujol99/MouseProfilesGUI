#pragma once
#include "Input/Strategy/IInputTypeStrategy.h"

#include <functional>
#include <mutex>

#include "Input/Key/KeyInputCommands.h"
#include "State/Key/IKeyState.h"


class KeyInputStrategy : public IInputTypeStrategy
{
public:

    KeyInputStrategy(std::vector<std::unique_ptr<KeyInputCommands const>>&& buttonInputCommands);

    ~KeyInputStrategy() override;

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

    std::vector<std::unique_ptr<KeyInputCommands const>> _keyInputCommands;

    const KeyInputCommands* _currentKeyInputCommand {nullptr};

    Duration _timeElapsed {0};

    TimePoint _previousTimePoint;

    std::weak_ptr<std::function<void()>> _subscriptionToTriggerHoldCommand;

    std::mutex _mutex;
};