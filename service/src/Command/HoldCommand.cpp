#include "Command/HoldCommand.h"

#include "Command/ICommand.h"

HoldCommand::HoldCommand(std::unique_ptr<ICommand>&& command, Duration&& millisToStart, Duration&& millisToRepeat) :
    _command(std::move(command)), _millisToStart(millisToStart), _millisToRepeatCommand(millisToRepeat)
{}

const Duration& HoldCommand::GetMillisToStart() const
{
    return _millisToStart;
}

const Duration& HoldCommand::GetMillisToRepeat() const
{
    return _millisToRepeatCommand;
}

void HoldCommand::ExecuteCommand(DeviceId deviceId) const
{
    _command->Execute(deviceId);
}
