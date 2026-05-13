#include "Backend/Command/SwitchToSubProfileCommand.h"

#include <iostream>

#include "Backend/Managers/ProfileManager.h"

SwitchToSubProfileCommand::SwitchToSubProfileCommand(int profileIndex) : _profileIndex(profileIndex)
{}

void SwitchToSubProfileCommand::Execute()
{
    std::cout << "Profile: " << _profileIndex << std::endl;
    ProfileManager::GetInstance().ChangeCurrentProfile(_profileIndex);
}
