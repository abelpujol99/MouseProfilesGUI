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
    auto itEnd {_drawables.cend()};

    for (auto it {_drawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
        (*it)->UpdatePosition();
    }

    _rootPosition->x += 0.1f;
}

void DrawManager::Start()
{
    _texture = DrawableFactory::CreateTexture(DrawablePosition{*_rootPosition, 300, 300}, "images/cat.jpg");

    _textBox = DrawableFactory::CreateTextBox(DrawablePosition{*_rootPosition, 100, 100}, RectangleData{{300, 190}, {255, 0, 0, 255}, 0, 1, true},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, {0, 0, 255, 255}});

    _textBox2 = DrawableFactory::CreateDisplayTextBox(DrawablePosition{*_rootPosition, 800, 100}, RectangleData{{300, 190}, {255, 0, 0, 255}, 0, 1, true},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, {0, 0, 255, 255}});

    _button = DrawableFactory::CreateButton(DrawablePosition{*_rootPosition, 800, 100}, RectangleData{{300, 190}, {255, 0, 0, 255}, 0, 1, false},
        TextData{"Button", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, {0, 0, 255, 255}}, []() {
            std::cout << "Button" << std::endl;
        });

    AddDrawable(_texture.get());
    AddDrawable(_textBox.get());
    AddDrawable(_textBox2.get());
}