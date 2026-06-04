#pragma once

#include "Input/InputDevices.h"
#include "Input/InputEvent.h"

class EmitData
{
public:

    EmitData(InputDevices inputDevice, InputEvent&& inputEvent);

    ~EmitData() = default;

    [[nodiscard]] InputDevices GetInputDevice() const;

    [[nodiscard]] InputEvent GetInputEvent() const;

private:
    InputDevices _inputDevice;

    InputEvent _inputEvent;

};