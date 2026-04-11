#pragma once

class ResolutionManager
{
public:    

    ~ResolutionManager() = default;

    ResolutionManager(const ResolutionManager& other) = delete;
    ResolutionManager& operator=(const ResolutionManager& other) = delete;
    ResolutionManager(ResolutionManager&& other) = delete;
    ResolutionManager& operator=(ResolutionManager&& other) = delete;

    static ResolutionManager& GetInstance();

    float AdaptWidth(float width);

    float AdaptHeight(float height);

private:

    ResolutionManager();

    static ResolutionManager _resolutionManagerInstance;
    
};