#include "backend/Input/Wheel/Scroll/WheelScrollInputCommand.h"

#include "backend/Command/ICommand.h"

WheelScrollInputCommand::WheelScrollInputCommand(std::unique_ptr<ICommand>&& command) : _command(std::move(command))
{}

void WheelScrollInputCommand::ExecuteCommand() const
{
    if (!_command)
    {
        return;
    }

    _command->Execute();
}
