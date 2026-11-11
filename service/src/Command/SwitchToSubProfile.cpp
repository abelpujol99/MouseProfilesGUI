#include "Command/SwitchToSubProfile.h"

#include <iostream>

#include "Managers/DevicesManager.h"

SwitchToSubProfile::SwitchToSubProfile(uint8_t subProfileIndex) : _subProfileIndex(subProfileIndex)
{}

void SwitchToSubProfile::Execute(DeviceId deviceId) const
{
    std::cout << "Profile: " << _subProfileIndex << std::endl;
    DevicesManager::GetInstance().ChangeDeviceCurrentSubProfile(deviceId, _subProfileIndex);
}