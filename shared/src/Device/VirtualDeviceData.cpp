#include "Device/VirtualDeviceData.h"

VirtualDeviceData::VirtualDeviceData(std::unordered_map<unsigned long, std::unordered_set<int>>&& capableInputs,
    const PlatformDeviceData& platformDeviceData) :
        _capableInputs(std::move(capableInputs)), _platformDeviceData(platformDeviceData)
{}

std::unordered_map<unsigned long, std::unordered_set<int>> VirtualDeviceData::GetCapableInputs() const
{
    return _capableInputs;
}

PlatformDeviceData VirtualDeviceData::GetDeviceData() const
{
    return _platformDeviceData;
}