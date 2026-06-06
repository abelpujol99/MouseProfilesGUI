#include "Managers/MVPManager.h"

std::unique_ptr<MVPManager> MVPManager::_applicationManagerInstance {nullptr};

MVPManager::MVPManager()
{}

MVPManager& MVPManager::GetInstance()
{
    if (_applicationManagerInstance == nullptr)
    {
        _applicationManagerInstance.reset(new MVPManager());
    }

    return *_applicationManagerInstance;
}

ServiceModel& MVPManager::GetServiceModel()
{
    return _serviceModel;
}

