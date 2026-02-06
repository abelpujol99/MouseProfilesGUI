#include "backend/Command/SwitchScrollModeCommand.h"

#include <fstream>

#include "backend/Managers/ApplicationManager.h"

SwitchScrollModeCommand::SwitchScrollModeCommand()
{
    _filePath = ApplicationManager::GetInstance().GetPathToSwitchScrollMode();

    //_isInFreeMode = IsInFreeMode();
}

bool SwitchScrollModeCommand::IsInFreeMode()
{
    std::ifstream file(_filePath);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open " + _filePath);
    }

    int mode;
    file >> mode;
    file.close();

    return mode == 1;
}

void SwitchScrollModeCommand::Execute()
{
    _isInFreeMode = !IsInFreeMode();

    int newMode {_isInFreeMode};
    std::ofstream file(_filePath);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open " + _filePath);
    }

    file << newMode;
    file.close();
}