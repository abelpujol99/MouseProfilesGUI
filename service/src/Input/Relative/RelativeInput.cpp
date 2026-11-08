#include "Input/Relative/RelativeInput.h"

#include <utility>

RelativeInput::RelativeInput(std::unique_ptr<RelativeInputStrategy> negativeInput,
    std::unique_ptr<RelativeInputStrategy> positiveInput) : _negativeInput(std::move(negativeInput)),
    _positiveInput(std::move(positiveInput))
{}

void RelativeInput::ChangeProfile(uint8_t profileIndex)
{
    _negativeInput->ChangeProfile(profileIndex);
    _positiveInput->ChangeProfile(profileIndex);
}

bool RelativeInput::HasNegativeInput() const
{
    return _negativeInput != nullptr;
}

bool RelativeInput::HasPositiveInput() const
{
    return _positiveInput != nullptr;
}

void RelativeInput::TriggerNegativeInput() const
{
    _negativeInput->Trigger();
}

void RelativeInput::TriggerPositiveInput() const
{
    _positiveInput->Trigger();
}