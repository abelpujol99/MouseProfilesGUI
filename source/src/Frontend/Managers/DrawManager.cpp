#include "Frontend/Managers/DrawManager.h"

#include <iostream>

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/UI/Structs/DrawablePosition.h"
#include "Frontend/UI/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"

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

    std::unique_ptr<TextBox> textBox {std::move(DrawableFactory::CreateTextBox(DrawablePosition{_rootPosition, 100, 100}, RectangleData{{300, 190}, {255, 0, 0, 255}, 0, 1, true},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, {0, 0, 255, 255}}))};

    _textBox = std::move(textBox);

    AddDrawable(_textBox.get());

    std::unique_ptr<Button> button {std::move(DrawableFactory::CreateButton(DrawablePosition{_rootPosition, 800, 100}, RectangleData{{300, 190}, {255, 0, 0, 255}, 0, 1, false},
        TextData{"Button", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, {0, 0, 255, 255}}, []() {
            std::cout << "Button" << std::endl;
        }))};

    _button = std::move(button);

    AddDrawable(_button.get());
}