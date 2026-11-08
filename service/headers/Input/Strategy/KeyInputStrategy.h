#pragma once
#include "Input/Strategy/IInputCommandStrategy.h"

#include <functional>

#include "Input/Key/KeyInputCommand.h"
#include "State/Button/IKeyState.h"


class KeyInputStrategy : public IInputCommandStrategy
{
public:

    KeyInputStrategy(std::vector<std::unique_ptr<KeyInputCommand const>>&& buttonInputCommands, CommandDelay&& commandDelay);

    void ChangeProfile(uint8_t profileIndex) override;

    void ChangeState(std::unique_ptr<IKeyState>&& buttonInputState);

    void RegisterValue(int value);

    void Press();

    void Hold();

    void Release();

    [[nodiscard]] bool IsHolding() const;

private:

    void FirstHoldDelay();

    void HoldDelay();

    std::unique_ptr<IKeyState> _keyState;

    bool _isPressed {false};

    std::vector<std::unique_ptr<KeyInputCommand const>> _keyInputCommands;

    const KeyInputCommand* _currentKeyInputCommand {nullptr};

    const CommandDelay _commandDelay;

    Duration _timeElapsed;

    TimePoint _previousTimePoint;

    std::weak_ptr<std::function<void()>> _subscriptionToTriggerHoldCommand;
};