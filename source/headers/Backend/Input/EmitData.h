#pragma once

#include "Backend/Input/InputDevices.h"
#include "Backend/Input/InputEvent.h"

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