#include "Frontend/Managers/View/DrawManager.h"

#include "Frontend/Factory/ScreenFactory.h"

DrawManager DrawManager::_drawManagerInstance{};

DrawManager& DrawManager::GetInstance()
{
    return _drawManagerInstance;
}

void DrawManager::AddScreen(Screen* screen)
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

void DrawManager::Start()
{
    _currentScreen = ScreenFactory::CreateProfileScreen({0, 0}, false);

    AddScreen(_currentScreen.get());
}