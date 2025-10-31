#pragma once

#include <memory>
#include <vector>

class Drawable;
struct ImDrawList;

class DrawManager
{
private:

    static std::unique_ptr<DrawManager> _drawManagerInstance;

    std::unique_ptr<Drawable> _texture;

    std::vector<Drawable*> _drawables;

    DrawManager() = default;

public:

    ~DrawManager() = default;

    DrawManager(const DrawManager& other) = delete;
    DrawManager& operator=(const DrawManager& other) = delete;
    DrawManager(DrawManager&& other) = delete;
    DrawManager& operator=(DrawManager&& other) = delete;

    static DrawManager& GetInstance();

    void AddDrawable(Drawable* drawable);

    void DrawElements(ImDrawList* drawList) const;

    void Start();
};
