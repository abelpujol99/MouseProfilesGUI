#include "Frontend/Managers/View/ResolutionManager.h"

ResolutionManager ResolutionManager::_resolutionManagerInstance {};

ResolutionManager::ResolutionManager()
{

}

ResolutionManager& ResolutionManager::GetInstance()
{
    return _resolutionManagerInstance;
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