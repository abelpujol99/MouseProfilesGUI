#include "Command/ShutdownApplicationCommand.h"

#include <iostream>
#include "Managers/ApplicationManager.h"

void ShutdownApplicationCommand::Execute()
{
    std::cout << "Shutdown" << std::endl;
    MVPManager::GetInstance().SwitchShouldRun();
}