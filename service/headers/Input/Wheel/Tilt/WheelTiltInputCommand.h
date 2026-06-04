#pragma once
#include "Input/InputCommand.h"

#include <memory>

#include "Command/ICommand.h"

class WheelTiltInputCommand : public InputCommand
{
public:

    WheelTiltInputCommand(std::unique_ptr<ICommand>&& commandOnPress, std::unique_ptr<ICommand>&& commandOnHold,
        std::unique_ptr<ICommand>&& commandOnRelease, Duration&& firstDelayInMillis, Duration&& millisToRepeatInput,
            Duration&& millisUntilInputStops);

    ~WheelTiltInputCommand() = default;

    void UpdateLastPressRegister();

    const Duration& GetMillisUntilInputStops() const;

    void Press() const;

    void Hold() const;

    void Release() const;

    bool IsHolding() const;

private:

    TimePoint _lastPressRegisterTime;
    const Duration _millisUntilInputStops;

    std::unique_ptr<ICommand> _commandOnPress;
    std::unique_ptr<ICommand> _commandOnHold;
    std::unique_ptr<ICommand> _commandOnRelease;
};
