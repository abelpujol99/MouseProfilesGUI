#pragma once

#include <vector>

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

    void AddScreen(Screen* screen);

    void DrawElements(ImDrawList* drawList);

    void Start();


private:

    DrawManager() = default;

    static DrawManager _drawManagerInstance;

    std::unique_ptr<Screen> _currentScreen;

    std::unique_ptr<BaseDrawable> _texture;

    std::unique_ptr<BaseDrawable> _textBox;

    std::unique_ptr<BaseDrawable> _textBox2;

    std::unique_ptr<BaseDrawable> _button;

    std::vector<Screen*> _screens;
};
