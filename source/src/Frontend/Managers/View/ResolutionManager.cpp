#include "Frontend/Managers/View/ResolutionManager.h"

ResolutionManager ResolutionManager::_resolutionManagerInstance {};

ResolutionManager::ResolutionManager()
{

}

ResolutionManager& ResolutionManager::GetInstance()
{
    return _resolutionManagerInstance;
}

float ResolutionManager::AdaptWidth(float width)
{
    return width;
}

float ResolutionManager::AdaptHeight(float height)
{
    return height;
}