#pragma once

#include <map>

#include "Frontend/UI/Elements/Complex/Screen.h"

class DrawManager
{
public:

    ~DrawManager() = default;

    DrawManager(const DrawManager& other) = delete;
    DrawManager& operator=(const DrawManager& other) = delete;
    DrawManager(DrawManager&& other) = delete;
    DrawManager& operator=(DrawManager&& other) = delete;

    static DrawManager& GetInstance();

    void Start();

    void AddScreen(Screen* screen);

    void AddDrawable(IDrawable* drawable, uint8_t layer, uint8_t order);

    void RemoveDrawable(uint8_t layer, uint8_t order);

    void DrawElements(ImDrawList* drawList);

private:

    DrawManager() = default;

    void DrawLayer(uint8_t layer, ImDrawList* drawList);

    void DrawOrderLayer(uint8_t layer, ImDrawList* drawList);

    static DrawManager _drawManagerInstance;

    std::map<uint8_t, std::map<uint8_t, IDrawable*>> _drawablesLayerAndOrder;

    std::unique_ptr<Screen> _currentScreen;

    std::vector<Screen*> _screens;
};
