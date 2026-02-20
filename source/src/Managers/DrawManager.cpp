#include "Managers/DrawManager.h"

#include "Factory/DrawableFactory.h"
#include "Factory/Font/FontFactory.h"
#include "UI/Drawable.h"

DrawManager DrawManager::_drawManagerInstance{};

DrawManager& DrawManager::GetInstance()
{
    return _drawManagerInstance;
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
    _texture = std::move(DrawableFactory::CreateTexture(300, 300, "images/cat.jpg"));

    AddDrawable(_texture.get());

    _text = std::move(DrawableFactory::CreateText(1200, 300, "Test", FontFactory::GetInstance().GetFontFamily(ROBOTO_REGULAR),
        200.f, {255, 255, 0, 255}));

    AddDrawable(_text.get());
}
