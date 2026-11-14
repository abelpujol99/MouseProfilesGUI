#pragma once
#include "Input/Strategy/IInputTypeStrategy.h"

#include <vector>

#include "Input/Relative/RelativeInputCommand.h"

class RelativeInputStrategy : public IInputTypeStrategy
{
public:

    RelativeInputStrategy(std::vector<std::unique_ptr<RelativeInputCommand const>>&& relativeInputCommands);

    ~RelativeInputStrategy() override = default;

    void ChangeProfile(uint8_t profileIndex) override;

    void Trigger(DeviceId deviceId) const;

private:

    std::vector<std::unique_ptr<RelativeInputCommand const>> _relativeInputCommands;

    const RelativeInputCommand* _currentRelativeInputCommand {nullptr};

};