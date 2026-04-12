#include "Frontend/Factory/ScreenFactory.h"

#include <filesystem>

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/Managers/View/WindowManager.h"
#include "Frontend/UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"
#include "Frontend/ColorDefines.h"

std::unique_ptr<Screen> ScreenFactory::CreateProfileScreen(ImVec2&& position, bool isHidden)
{
    std::filesystem::path resourceDir = RESOURCE_DIR;

    std::unique_ptr<Screen> profileScreen {DrawableFactory::CreateScreen(std::move(position),
        WindowManager::GetInstance().GetSize(), isHidden)};

    WindowManager& windowManager {WindowManager::GetInstance()};

    std::unique_ptr<RectDrawable> rectDrawable1 {DrawableFactory::CreateRectDrawable({50, 50},{700, 700}, isHidden)};

    std::unique_ptr<Text> title {DrawableFactory::CreateText(TextData{"peripheralName",
        TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        35.f, WHITE}, isHidden)};

    std::unique_ptr<RectDrawable> rectDrawable2 {DrawableFactory::CreateRectDrawable({0, 0},{300, 100}, isHidden)};

    auto catPath {resourceDir / "images/cat.jpg"};

    std::unique_ptr<Texture> texture {DrawableFactory::CreateTexture(catPath.c_str(), isHidden)};

    std::unique_ptr<Rectangle> rectangle {DrawableFactory::CreateRectangle(RectangleData{WHITE, 0, 10}, isHidden)};

    std::unique_ptr<TextBox<char, ApplyKey>> profileName {DrawableFactory::CreateTextBox(RectangleData{WHITE, 0, 10, isHidden},
        TextData{"Holi", TextHorizontalAlignments::RIGHT, TextVerticalAlignments::BOTTOM, FontFamilyTypes::ROBOTO_REGULAR, 20.f, RED},
        isHidden)};

    rectDrawable2->AddDrawableComponent(std::move(texture));

    rectDrawable1->AddRectDrawable(std::move(rectDrawable2));

    rectDrawable1->AddDrawableComponent(std::move(title));

    profileScreen->AddRectDrawable(std::move(rectDrawable1));

    return profileScreen;
}