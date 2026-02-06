#include "backend/Command/SwitchToProfileCommand.h"

#include <iostream>

#include "backend/Managers/ProfileManager.h"

SwitchToProfileCommand::SwitchToProfileCommand(int profileIndex) : _profileIndex(profileIndex)
{}

void SwitchToProfileCommand::Execute()
{
    std::cout << "Profile: " << _profileIndex << std::endl;
    ProfileManager::GetInstance().ChangeCurrentProfile(_profileIndex);
}
