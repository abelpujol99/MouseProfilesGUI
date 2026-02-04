#pragma once

#include <memory>
#include <vector>

#include <EmitData.h>
#include <ButtonInputCommand.h>
#include <WheelTiltInputCommand.h>
#include <WheelScrollInputCommand.h>
#include <TimeUsings.h>

class ICommand;
class WheelTiltInputCommand;
class WheelScrollInputCommand;

class CommandFactory
{

public:

    CommandFactory() = delete;
    CommandFactory(const CommandFactory& other) = delete;
    CommandFactory& operator=(const CommandFactory& other) = delete;
    CommandFactory(CommandFactory&& other) = delete;
    CommandFactory&& operator=(CommandFactory&& other) = delete;

    [[nodiscard]] static std::unique_ptr<ICommand> CreateStringCommand(std::string&& commandLine);

    [[nodiscard]] static std::unique_ptr<ICommand> CreateSwitchScrollModeCommand();

    [[nodiscard]] static std::unique_ptr<ICommand> CreateSwitchToProfileCommand(int profileIndex);

    [[nodiscard]] static std::unique_ptr<ICommand> CreateSwitchToMainProfileCommand();

    [[nodiscard]] static std::unique_ptr<ICommand> CreateShutdownApplicationCommand();

    [[nodiscard]] static std::unique_ptr<ICommand> CreateEmitInputEventCommand(std::vector<EmitData>&& emitsData);

    [[nodiscard]] static std::unique_ptr<ButtonInputCommand> CreateButtonInputCommand(std::unique_ptr<ICommand>&& commandOnPress,
        std::unique_ptr<ICommand>&& commandOnHold, std::unique_ptr<ICommand>&& commandOnRelease, Duration&& firstDelayInMillis,
            Duration&& millisToRepeatInput);

    [[nodiscard]] static std::unique_ptr<WheelTiltInputCommand> CreateWheelTiltInputCommand(std::unique_ptr<ICommand>&& commandOnPress,
        std::unique_ptr<ICommand>&& commandOnHold, std::unique_ptr<ICommand>&& commandOnRelease, Duration&& firstDelayInMillis,
            Duration&& millisToRepeatInput, Duration&& millisUntilInputStops);

    [[nodiscard]] static std::unique_ptr<WheelScrollInputCommand> CreateWheelScrollInputCommand(std::unique_ptr<ICommand>&& command);
};