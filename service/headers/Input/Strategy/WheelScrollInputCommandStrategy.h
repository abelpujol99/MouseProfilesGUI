#pragma once
#include "Input/Strategy/IInputCommandStrategy.h"

#include <vector>

#include "../Relative/RelativeInputCommand.h"

class WheelScrollInputCommandStrategy : public IInputCommandStrategy
{
public:

    WheelScrollInputCommandStrategy(std::vector<std::unique_ptr<RelativeInputCommand>>&& wheelNegativeInputCommands,
        std::vector<std::unique_ptr<RelativeInputCommand>>&& wheelPositiveInputCommands);

    void ChangeProfile(int profileIndex) override;

    void RegisterValue(int value) override;

private:

    std::vector<std::unique_ptr<RelativeInputCommand>> _wheelNegativeInputCommands;
    std::vector<std::unique_ptr<RelativeInputCommand>> _wheelPositiveInputCommands;

    RelativeInputCommand* _currentWheelNegativeInputCommand {nullptr};
    RelativeInputCommand* _currentWheelPositiveInputCommand {nullptr};

};
