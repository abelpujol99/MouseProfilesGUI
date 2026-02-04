#pragma once

#include <InputDevices.h>
#include <InputEvent.h>

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
