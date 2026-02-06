#include "backend/Command/ShutdownApplicationCommand.h"

#include <iostream>
#include "backend/Managers/ApplicationManager.h"

void ShutdownApplicationCommand::Execute()
{
    std::cout << "Shutdown" << std::endl;
    ApplicationManager::GetInstance().SwitchShouldRun();
}