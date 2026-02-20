#include "backend/Factory/CommandFactory.h"

#include "backend/Command/SwitchToProfileCommand.h"
#include "backend/Command/ShutdownApplicationCommand.h"
#include "backend/Command/EmitInputEventCommand.h"

#define MAIN_PROFILE 0

std::unique_ptr<ICommand> CommandFactory::CreateSwitchToProfileCommand(int profileIndex)
{
    return std::make_unique<SwitchToProfileCommand>(profileIndex);
}

std::unique_ptr<ICommand> CommandFactory::CreateSwitchToMainProfileCommand()
{
    return std::make_unique<SwitchToProfileCommand>(MAIN_PROFILE);
}

std::unique_ptr<ICommand> CommandFactory::CreateShutdownApplicationCommand()
{
    return std::make_unique<ShutdownApplicationCommand>();
}

std::unique_ptr<ICommand> CommandFactory::CreateEmitInputEventCommand(std::vector<EmitData>&& emitsData)
{
    return std::make_unique<EmitInputEventCommand>(std::move(emitsData));
}

std::unique_ptr<ButtonInputCommand> CommandFactory::CreateButtonInputCommand(std::unique_ptr<ICommand>&& commandOnPress,
    std::unique_ptr<ICommand>&& commandOnHold, std::unique_ptr<ICommand>&& commandOnRelease, Duration&& firstDelayInMillis,
        Duration&& millisToRepeatInput)
{
    return std::make_unique<ButtonInputCommand>(std::move(commandOnPress), std::move(commandOnHold), std::move(commandOnRelease),
        std::move(firstDelayInMillis), std::move(millisToRepeatInput));
}

std::unique_ptr<WheelTiltInputCommand> CommandFactory::CreateWheelTiltInputCommand(std::unique_ptr<ICommand>&& commandOnPress,
    std::unique_ptr<ICommand>&& commandOnHold, std::unique_ptr<ICommand>&& commandOnRelease, Duration&& firstDelayInMillis,
        Duration&& millisToRepeatInput, Duration&& millisUntilInputStops)
{
    return std::make_unique<WheelTiltInputCommand>(std::move(commandOnPress), std::move(commandOnHold),
        std::move(commandOnRelease), std::move(firstDelayInMillis), std::move(millisToRepeatInput), std::move(millisUntilInputStops));
}

std::unique_ptr<WheelScrollInputCommand> CommandFactory::CreateWheelScrollInputCommand(std::unique_ptr<ICommand>&& command)
{
    return std::make_unique<WheelScrollInputCommand>(std::move(command));
}
