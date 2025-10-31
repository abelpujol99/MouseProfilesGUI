#include "DrawManager.h"

#include "Drawable.h"
#include "DrawableFactory.h"

std::unique_ptr<DrawManager> DrawManager::_drawManagerInstance = nullptr;

DrawManager& DrawManager::GetInstance()
{
    if (!_drawManagerInstance)
    {
        _drawManagerInstance.reset(new DrawManager());
    }

    return *_drawManagerInstance;
}

void DrawManager::AddDrawable(Drawable* drawable)
{
    _drawables.push_back(drawable);
}

void DrawManager::DrawElements(ImDrawList* drawList) const
{
    for (auto& drawable : _drawables)
    {
        drawable->Draw(drawList);
    }
}

void DrawManager::Start()
{
    _texture = std::move(DrawableFactory::CreateTexture(300, 300, "resources/cat.jpg"));

    AddDrawable(_texture.get());
}
