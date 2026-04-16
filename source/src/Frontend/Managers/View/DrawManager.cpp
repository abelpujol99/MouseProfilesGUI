#include "Frontend/Managers/View/DrawManager.h"

#include "Frontend/Factory/ScreenFactory.h"

DrawManager DrawManager::_drawManagerInstance{};

DrawManager& DrawManager::GetInstance()
{
    return _drawManagerInstance;
}

void DrawManager::Start()
{
    _currentScreen = ScreenFactory::CreateProfileScreen(false);

    AddScreen(_currentScreen.get());
}

void DrawManager::AddScreen(Screen* screen)
{
    _screens.push_back(screen);
}

void DrawManager::AddDrawable(IDrawable* drawable, uint8_t layer, uint8_t order)
{
    if (!_drawablesLayerAndOrder.contains(layer))
    {
        _drawablesLayerAndOrder.emplace(layer, std::map<uint8_t, IDrawable*>{});
    }

    assert(!_drawablesLayerAndOrder.at(layer).contains(order) && "Order is occupied");

    _drawablesLayerAndOrder.at(layer).emplace(order, drawable);
}

void DrawManager::RemoveDrawable(uint8_t layer, uint8_t order)
{
    _drawablesLayerAndOrder.at(layer).erase(order);
}

void DrawManager::DrawElements(ImDrawList* drawList)
{
    /*auto itEnd {_screens.cend()};

    for (auto it {_screens.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }*/

    for (const auto&[key, value] : _drawablesLayerAndOrder)
    {
        DrawLayer(key, drawList);
    }
}

void DrawManager::DrawLayer(uint8_t layer, ImDrawList* drawList)
{
    for (const auto&[key, drawable] : _drawablesLayerAndOrder.at(layer))
    {
        drawable->Draw(drawList);
    }
}