#pragma once
#include <memory>
#include <vector>

#include "imgui.h"

class Text;
class Drawable;
struct ImDrawList;

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

    ImVec2 _rootPosition {0, 0};

    std::unique_ptr<Drawable> _texture;

    std::unique_ptr<Drawable> _text;

    std::unique_ptr<Drawable> _textBox1;

    std::unique_ptr<Drawable> _textBox2;

    std::vector<Drawable*> _drawables;
};
