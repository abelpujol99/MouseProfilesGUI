#include "Frontend/Managers/View/DrawManager.h"

#include <iostream>

#include "Frontend/ColorDefines.h"
#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Factory/ScreenFactory.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/Managers/View/WindowManager.h"
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
    _currentScreen = ScreenFactory::CreateProfileScreen(DrawablePosition{*_rootPosition, 0, 0}, "Razer");

    _texture = DrawableFactory::CreateTexture(DrawablePosition{*_rootPosition, 300, 300}, "images/cat.jpg");

    _textBox = DrawableFactory::CreateTextBox(DrawablePosition{*_rootPosition, 100, 100}, RectangleData{{300, 190}, RED, 0, 1, true},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, BLUE});

    _textBox2 = DrawableFactory::CreateTextBox(DrawablePosition{*_rootPosition,
        static_cast<float>(WindowManager::GetInstance().GetWidth() / 2), static_cast<float>(200)}, RectangleData{ImVec2{200, 200}, WHITE, 1, 100, true},
        TextData{"Holi", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, 20.f, WHITE},
        false);

    _button = DrawableFactory::CreateButton(DrawablePosition{*_rootPosition, 800, 100}, RectangleData{{300, 190}, RED, 0, 1, false},
        TextData{"Button", TextHorizontalAlignments::LEFT, TextVerticalAlignments::TOP, FontFamilyTypes::ROBOTO_REGULAR, 20.f, BLUE}, []() {
            std::cout << "Button" << std::endl;
        });

    AddDrawable(_currentScreen.get());
    /*AddDrawable(_texture.get());
    AddDrawable(_textBox.get());
    AddDrawable(_textBox2.get());*/
}