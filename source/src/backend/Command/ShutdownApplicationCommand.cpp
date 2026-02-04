#include <ShutdownApplicationCommand.h>

#include <ApplicationManager.h>
#include <iostream>

void ShutdownApplicationCommand::Execute()
{
    std::cout << "Shutdown" << std::endl;
    ApplicationManager::GetInstance().SwitchShouldRun();
}