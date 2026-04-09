#pragma once
#include <memory>
#include <vector>
#include "imgui.h"

#include "Frontend/UI/Drawable.h"


class DrawManager
{
public:

    ~DrawManager() = default;

    DrawManager(const DrawManager& other) = delete;
    DrawManager& operator=(const DrawManager& other) = delete;
    DrawManager(DrawManager&& other) = delete;
    DrawManager& operator=(DrawManager&& other) = delete;

    static DrawManager& GetInstance();

    void AddDrawable(Drawable* drawable);

    void DrawElements(ImDrawList* drawList);

    void Start();


private:

    DrawManager() = default;

    static DrawManager _drawManagerInstance;

    std::unique_ptr<ImVec2> _rootPosition {std::make_unique<ImVec2>(0, 0)};

    std::unique_ptr<Drawable> _texture;

    std::unique_ptr<Drawable> _textBox;

    std::unique_ptr<Drawable> _textBox2;

    std::unique_ptr<Drawable> _button;

    std::vector<Drawable*> _drawables;
};
