#pragma once
#include "DeviceUsings.h"
#include "TimeUsings.h"

class ICommand;

class HoldCommand
{
public:

    HoldCommand(std::unique_ptr<ICommand>&& command, Duration&& millisToStart, Duration&& millisToRepeat);

    [[nodiscard]] const Duration& GetMillisToStart() const;

    [[nodiscard]] const Duration& GetMillisToRepeat() const;

    void ExecuteCommand(DeviceId deviceId) const;

private:

    const std::unique_ptr<ICommand> _command;

    const Duration _millisToStart;

    const Duration _millisToRepeatCommand;
};
