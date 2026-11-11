#pragma once
#include <unordered_map>
#include <unordered_set>

#include "DeviceData.h"
#include "Device/InputType.h"

class VirtualDeviceData
{
public:
    VirtualDeviceData(InputType inputType, std::unordered_map<unsigned long, std::unordered_set<int>>&& capableInputs,
        DeviceData deviceData);

    [[nodiscard]] InputType GetInputType() const;
    [[nodiscard]] std::unordered_map<unsigned long, std::unordered_set<int>> GetCapableInputs() const;
    [[nodiscard]] DeviceData GetDeviceData() const;

private:

    InputType _inputType;

    std::unordered_map<unsigned long, std::unordered_set<int>> _capableInputs;

    DeviceData _deviceData;

};
