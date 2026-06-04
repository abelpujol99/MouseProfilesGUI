#include "Command/SwitchToSubProfileCommand.h"

#include <iostream>

#include "Managers/ProfileManager.h"

SwitchToSubProfileCommand::SwitchToSubProfileCommand(uint8_t subProfileIndex) : _subProfileIndex(subProfileIndex)
{}

void SwitchToSubProfileCommand::Execute()
{
    std::cout << "Profile: " << _subProfileIndex << std::endl;
    ProfileManager::GetInstance().ChangeCurrentSubProfile(_subProfileIndex);
}