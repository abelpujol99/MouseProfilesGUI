#pragma once

#include "Input/EmitData.h"
#include "Input/Button/ButtonInputCommand.h"
#include "Input/Wheel/Scroll/WheelScrollInputCommand.h"
#include "Input/Wheel/Tilt/WheelTiltInputCommand.h"

class CommandFactory
{

public:

    CommandFactory() = delete;
    CommandFactory(const CommandFactory& other) = delete;
    CommandFactory& operator=(const CommandFactory& other) = delete;
    CommandFactory(CommandFactory&& other) = delete;
    CommandFactory&& operator=(CommandFactory&& other) = delete;

    [[nodiscard]] static std::unique_ptr<ICommand> CreateSwitchToProfileCommand(uint8_t profileIndex);

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