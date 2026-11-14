#pragma once

#include <memory>

#include "Command/ICommand.h"
#include "Command/HoldCommand.h"
#include "Input/Key/KeyStateCommands.h"

class KeyInputCommands
{
public:

    KeyInputCommands(KeyStateCommands&& keyStateCommands);

    ~KeyInputCommands() = default;

    void Press(DeviceId deviceId) const;

    void Hold(DeviceId deviceId) const;

    void Release(DeviceId deviceId) const;

    [[nodiscard]] const HoldCommand* GetHoldCommand() const;

private:

    const std::unique_ptr<ICommand const> _onPressCommand;
    const std::unique_ptr<HoldCommand const> _holdCommand;
    const std::unique_ptr<ICommand const> _onReleaseCommand;
};