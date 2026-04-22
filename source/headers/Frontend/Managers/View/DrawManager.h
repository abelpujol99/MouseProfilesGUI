#pragma once

#include <vector>

#include "Frontend/UI/Elements/Complex/Canvas.h"

class DrawManager
{
public:

    ~DrawManager() noexcept;

    DrawManager(const DrawManager& other) = delete;
    DrawManager& operator=(const DrawManager& other) = delete;
    DrawManager(DrawManager&& other) = delete;
    DrawManager& operator=(DrawManager&& other) = delete;

    static DrawManager& GetInstance();

    void AddScreen(Canvas* screen);

    void DrawElements(ImDrawList* drawList);

    void Start();


private:

    DrawManager() = default;

    static DrawManager* _drawManagerInstance;

    std::unique_ptr<Canvas> _currentScreen;

    std::vector<Canvas*> _screens;
};
