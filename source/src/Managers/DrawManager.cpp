#include "Managers/DrawManager.h"

#include <iostream>

#include "Factories/DrawableFactory.h"
#include "Factories/Font/FontFactory.h"
#include "Factories/ImGui/ImGuiFactory.h"
#include "UI/Drawable.h"
#include "UI/Texture.h"
#include "UI/Text/Text.h"
#include "UI/Text/TextBox.h"

DrawManager DrawManager::_drawManagerInstance{};

DrawManager& DrawManager::GetInstance()
{
    return _drawManagerInstance;
}

void DrawManager::AddDrawable(Drawable* drawable)
{
    _drawables.push_back(drawable);
}

void DrawManager::DrawElements(ImDrawList* drawList)
{
    for (auto drawable : _drawables)
    {
        drawable->Draw(drawList);
        drawable->UpdatePosition();
    }

    _rootPosition.x += 0.01f;
}

void DrawManager::Start()
{
    _texture = DrawableFactory::CreateTexture(_rootPosition, 300, 300, "images/cat.jpg");

    AddDrawable(_texture.get());

    /*_text = DrawableFactory::CreateText(_rootPosition, 1200, 300, "Test 2", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP,
        FontFactory::GetInstance().GetFontFamily(FontFamilyTypes::ROBOTO_REGULAR), 20.f, {255, 255, 0, 255});

    AddDrawable(_text.get());*/

    _textBox = DrawableFactory::CreateTextBox(_rootPosition, 100, 100, 300, 190, 10, 10, {255, 0, 0, 255}, 0, 1,
        TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, {0, 0, 255, 255});

    AddDrawable(_textBox.get());
}