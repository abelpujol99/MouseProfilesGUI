#include "Backend/Command/ShutdownApplicationCommand.h"

#include <iostream>
#include "Backend/Managers/ApplicationManager.h"

void ShutdownApplicationCommand::Execute()
{
    std::cout << "Shutdown" << std::endl;
    ApplicationManager::GetInstance().SwitchShouldRun();
}