#include "Command/SwitchToSubProfile.h"

#include <iostream>

#include "Managers/ProfileManager.h"

SwitchToSubProfile::SwitchToSubProfile(uint8_t subProfileIndex) : _subProfileIndex(subProfileIndex)
{}

void SwitchToSubProfile::Execute() const
{
    std::cout << "Profile: " << _subProfileIndex << std::endl;
    ProfileManager::GetInstance().ChangeCurrentSubProfile(_subProfileIndex);
}