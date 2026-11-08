#include "Input/Relative/RelativeInputCommand.h"

RelativeInputCommand::RelativeInputCommand(std::unique_ptr<ICommand const>&& command) : _command(std::move(command))
{}

void RelativeInputCommand::ExecuteCommand() const
{
    if (_command == nullptr)
    {
        return;
    }

    _command->Execute();
}
