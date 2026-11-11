#pragma once
#include "Input/Strategy/IInputCommandStrategy.h"

#include <vector>

#include "Input/Relative/RelativeInputCommand.h"

class RelativeInputStrategy : public IInputCommandStrategy
{
public:

    RelativeInputStrategy(std::vector<std::unique_ptr<RelativeInputCommand const>>&& relativeInputCommands);

    void ChangeProfile(uint8_t profileIndex) override;

    void Trigger(DeviceId deviceId) const;

private:

    std::vector<std::unique_ptr<RelativeInputCommand const>> _relativeInputCommands;

    const RelativeInputCommand* _currentRelativeInputCommand {nullptr};

};