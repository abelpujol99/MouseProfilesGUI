#include "Command/ShutdownApplication.h"

#include <iostream>
#include "Managers/ApplicationManager.h"

void ShutdownApplication::Execute(DeviceId device_id) const
{
    std::cout << "Shutdown" << std::endl;
    ApplicationManager::Shutdown();
}