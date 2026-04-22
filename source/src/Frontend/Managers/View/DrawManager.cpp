#include "Frontend/Managers/View/DrawManager.h"

#include "Frontend/Factory/ScreenFactory.h"

DrawManager* DrawManager::_drawManagerInstance {nullptr};

DrawManager::~DrawManager() noexcept
{
    delete _drawManagerInstance;
}

DrawManager& DrawManager::GetInstance()
{
    if (_drawManagerInstance == nullptr)
    {
        _drawManagerInstance = new DrawManager();
    }

    return *_drawManagerInstance;
}

void DrawManager::Start()
{
    _currentScreen = ScreenFactory::CreateProfileScreen(false);

    AddScreen(_currentScreen.get());
}

void DrawManager::AddScreen(Canvas* screen)
{
    _screens.push_back(screen);
}

void DrawManager::DrawElements(ImDrawList* drawList)
{
    auto itEnd {_screens.cend()};

    for (auto it {_screens.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}