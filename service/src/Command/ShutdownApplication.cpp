#include "Command/ShutdownApplication.h"

#include <iostream>
#include "Managers/ApplicationManager.h"

void ShutdownApplication::Execute() const
{
    std::cout << "Shutdown" << std::endl;
    ApplicationManager::GetInstance().SwitchShouldRun();
}