#include "Frontend/Factory/ScreenFactory.h"

#include <filesystem>
#include <iostream>

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/Managers/View/WindowManager.h"
#include "Frontend/UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"
#include "Frontend/ColorDefines.h"
#include "Frontend/AnchorsDefines.h"
#include "Frontend/PivotDefines.h"
#include "Frontend/TextDefines.h"
#include "Frontend/RectangleDefines.h"

std::unique_ptr<Screen> ScreenFactory::CreateProfileScreen(ImVec2&& position, bool isHidden)
{
    std::filesystem::path resourceDir = RESOURCE_DIR;

    WindowManager& windowManager {WindowManager::GetInstance()};

    std::unique_ptr<Screen> profileScreen {DrawableFactory::CreateScreen(std::move(position),
        windowManager.GetSize(), isHidden)};

#pragma region Profile Name

    std::unique_ptr<Text> profileNameText {DrawableFactory::CreateText(TextData{"Profile name", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE}, isHidden)};

    std::unique_ptr<RectDrawable> profileNameTextRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {0.5, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    profileNameTextRect->AddDrawableComponent(std::move(profileNameText));

    std::unique_ptr<Button> button {DrawableFactory::CreateButton(RectangleData{RED, NO_ROUNDING, THIN_BORDER, true}, TextData{"", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, 10, WHITE}, []() {
        std::cout << "Click" << std::endl;
    }, false)};

    std::unique_ptr<TextBox<char, ApplyKey>> profileNameTextBox {DrawableFactory::CreateTextBox(RectangleData{GREY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE})};

    std::unique_ptr<RectDrawable> profileNameTextBoxRect {DrawableFactory::CreateRectDrawable(Anchors{{0.5, 0}, {1, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    //profileNameTextBoxRect->AddDrawableComponent(std::move(profileNameTextBox));
    profileNameTextBoxRect->AddDrawableComponent(std::move(button));

    std::unique_ptr<RectDrawable> profileNameRect {DrawableFactory::CreateRectDrawable(Anchors{{0.4, 0.1}, {0.6, 0.1}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    profileNameRect->AddRectDrawable(std::move(profileNameTextRect));
    profileNameRect->AddRectDrawable(std::move(profileNameTextBoxRect));

#pragma endregion

    //ShowLinesX(rectDrawable1.get());

    profileScreen->AddRectDrawable(std::move(profileNameRect));

    return profileScreen;
}

void ScreenFactory::ShowLinesX(void* rect)
{
    for (float i = 0; i < 10; i += 0.5f)
    {
        std::unique_ptr<Rectangle> rectangle {DrawableFactory::CreateRectangle(RectangleData{PURPLE, 0, 1, false}, false)};

        std::unique_ptr<RectDrawable> rectDrawable {DrawableFactory::CreateRectDrawable({{static_cast<float>(i / 10), 0}, {static_cast<float>(i / 10), 1}}, PIVOT_MIDDLE_CENTER,
            {0, 0},{0, 100}, false)};

        rectDrawable->AddDrawableComponent(std::move(rectangle));

        static_cast<RectDrawable*>(rect)->AddRectDrawable(std::move(rectDrawable));
    }
}
