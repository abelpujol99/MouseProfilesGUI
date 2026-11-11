#pragma once

#include "Input/Strategy/RelativeInputStrategy.h"

class RelativeInput
{
public:

    RelativeInput(std::unique_ptr<RelativeInputStrategy> negativeInput, std::unique_ptr<RelativeInputStrategy> positiveInput);

    void ChangeProfile(uint8_t profileIndex);

    [[nodiscard]] bool HasNegativeInput() const;
    [[nodiscard]] bool HasPositiveInput() const;

    void TriggerNegativeInput(DeviceId deviceId) const;
    void TriggerPositiveInput(DeviceId deviceId) const;

private:

    const std::unique_ptr<RelativeInputStrategy> _negativeInput;
    const std::unique_ptr<RelativeInputStrategy> _positiveInput;
};
