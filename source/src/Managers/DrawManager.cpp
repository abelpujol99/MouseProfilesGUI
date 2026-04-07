#include "Managers/DrawManager.h"

#include "Factories/DrawableFactory.h"
#include "Factories/Font/FontFamilyTypes.h"
#include "UI/Basic/Texture.h"
#include "UI/Basic/Text.h"
#include "UI/Advanced/Text/TextBox.h"

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

    _rootPosition.x += 0.1f;
}

void DrawManager::Start()
{
    _texture = DrawableFactory::CreateTexture(DrawablePosition{_rootPosition, 300, 300}, "images/cat.jpg");

    AddDrawable(_texture.get());

    /*_text = DrawableFactory::CreateText(_rootPosition, 1200, 300, "Test 2", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP,
        FontFactory::GetInstance().GetFontFamily(FontFamilyTypes::ROBOTO_REGULAR), 20.f, {255, 255, 0, 255});

    AddDrawable(_text.get());*/

    std::unique_ptr<TextBox> textBox {std::move(DrawableFactory::CreateTextBox(DrawablePosition{_rootPosition, 100, 100}, RectangleData{{300, 190}, {255, 0, 0, 255}, 0, 1, true},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, {0, 0, 255, 255}}))};

    _textBox1 = std::move(textBox);

    AddDrawable(_textBox1.get());

    std::unique_ptr<TextBox> textBox1 {std::move(DrawableFactory::CreateTextBox(DrawablePosition{_rootPosition, 800, 100}, RectangleData{{300, 190}, {255, 0, 0, 255}, 0, 1, false},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, {0, 0, 255, 255}}))};

    _textBox2 = std::move(textBox1);

    AddDrawable(_textBox2.get());
}