#include "Input/EmitData.h"

#include <algorithm>

EmitData::EmitData(InputDevices inputDevice, InputEvent&& inputEvent) : _inputDevice(inputDevice), _inputEvent(std::move(inputEvent))
{}

InputDevices EmitData::GetInputDevice() const
{
    return _inputDevice;
}

InputEvent EmitData::GetInputEvent() const
{
    return _inputEvent;
}
