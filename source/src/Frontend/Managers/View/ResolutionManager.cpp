#include "Frontend/Managers/View/ResolutionManager.h"

ResolutionManager* ResolutionManager::_resolutionManagerInstance {nullptr};

ResolutionManager::ResolutionManager()
{

}

ResolutionManager::~ResolutionManager() noexcept
{
    delete _resolutionManagerInstance;
}

ResolutionManager& ResolutionManager::GetInstance()
{
    if (_resolutionManagerInstance == nullptr)
    {
        _resolutionManagerInstance = new ResolutionManager();
    }

    return *_resolutionManagerInstance;
}

ImVec2 ResolutionManager::AdaptSize(ImVec2&& size)
{
    return {AdaptWidth(size.x), AdaptHeight(size.y)};
}

float ResolutionManager::AdaptWidth(float width)
{
    return width;
}

float ResolutionManager::AdaptHeight(float height)
{
    return height;
}