#pragma once

#include "backend/Input/InputDevices.h"
#include "backend/Input/InputEvent.h"

class EmitData
{
private:
    InputDevices _inputDevice;

    InputEvent _inputEvent;

public:

    EmitData(InputDevices inputDevice, InputEvent&& inputEvent);

    InputDevices GetInputDevice() const;

    InputEvent GetInputEvent() const;
};
