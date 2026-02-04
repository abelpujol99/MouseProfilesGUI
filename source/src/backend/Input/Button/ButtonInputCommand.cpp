#include <ButtonInputCommand.h>

#include <ICommand.h>

#include <ButtonPressStateAction.h>

ButtonInputCommand::ButtonInputCommand(std::unique_ptr<ICommand>&& commandOnPress,
    std::unique_ptr<ICommand>&& commandOnHold, std::unique_ptr<ICommand>&& commandOnRelease, Duration&& firstDelayInMillis,
        Duration&& millisToRepeatInput) : InputCommand(std::move(firstDelayInMillis), std::move(millisToRepeatInput)),
            _commandOnPress(std::move(commandOnPress)), _commandOnHold(std::move(commandOnHold)), _commandOnRelease(std::move(commandOnRelease))
{}

void ButtonInputCommand::Press() const
{
    if (!_commandOnPress)
    {
        return;
    }

    _commandOnPress->Execute();
}

void ButtonInputCommand::Hold() const
{
    if (!_commandOnHold)
    {
        return;
    }

    _commandOnHold->Execute();
}

void ButtonInputCommand::Release() const
{
    if (!_commandOnRelease)
    {
        return;
    }

    _commandOnRelease->Execute();
}

bool ButtonInputCommand::HasHoldCommand() const
{
    return _commandOnHold != nullptr;
}