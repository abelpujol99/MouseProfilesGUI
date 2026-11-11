#include "Device/VirtualDeviceData.h"

VirtualDeviceData::VirtualDeviceData(InputType inputType,
    std::unordered_map<unsigned long, std::unordered_set<int>>&& capableInputs, DeviceData deviceData) : _inputType(inputType),
    _capableInputs(std::move(capableInputs)), _deviceData(deviceData)
{}

InputType VirtualDeviceData::GetInputType() const
{
    return _inputType;
}

std::unordered_map<unsigned long, std::unordered_set<int>> VirtualDeviceData::GetCapableInputs() const
{
    return _capableInputs;
}

DeviceData VirtualDeviceData::GetDeviceData() const
{
    return _deviceData;
}