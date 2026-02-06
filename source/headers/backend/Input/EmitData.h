#pragma once

#include "backend/Input/InputDevices.h"
#include "backend/Input/InputEvent.h"

class EmitData
{
public:

    EmitData(InputDevices inputDevice, InputEvent&& inputEvent);

    InputDevices GetInputDevice() const;

    InputEvent GetInputEvent() const;

private:
    InputDevices _inputDevice;

    InputEvent _inputEvent;

};