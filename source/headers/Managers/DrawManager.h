#pragma once
#include <memory>
#include <vector>

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

    void DrawElements(ImDrawList* drawList) const;

    void Start();


private:

    DrawManager() = default;

    static DrawManager _drawManagerInstance;

    std::unique_ptr<Drawable> _texture;

    std::unique_ptr<Drawable> _text;

    std::vector<Drawable*> _drawables;
};
