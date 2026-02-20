#pragma once
#include "backend/Input/Strategy/IInputCommandStrategy.h"

#include <memory>
#include <vector>


class WheelScrollInputCommand;

class WheelScrollInputCommandStrategy : public IInputCommandStrategy
{
public:

    WheelScrollInputCommandStrategy(std::vector<std::unique_ptr<WheelScrollInputCommand>>&& wheelNegativeInputCommands,
        std::vector<std::unique_ptr<WheelScrollInputCommand>>&& wheelPositiveInputCommands);

    void ChangeProfile(int profileIndex) override;

    void RegisterValue(int value) override;

private:

    std::vector<std::unique_ptr<WheelScrollInputCommand>> _wheelNegativeInputCommands;
    std::vector<std::unique_ptr<WheelScrollInputCommand>> _wheelPositiveInputCommands;

    WheelScrollInputCommand* _currentWheelNegativeInputCommand {nullptr};
    WheelScrollInputCommand* _currentWheelPositiveInputCommand {nullptr};

};