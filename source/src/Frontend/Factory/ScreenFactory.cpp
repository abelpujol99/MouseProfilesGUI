#include "Frontend/Factory/ScreenFactory.h"

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/Managers/View/ResolutionManager.h"
#include "Frontend/Managers/View/WindowManager.h"
#include "Frontend/UI/Screen.h"
#include "Frontend/UI/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Structs/DrawablePosition.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"
#include "Frontend/ColorDefines.h"

std::unique_ptr<Drawable> ScreenFactory::CreateProfileScreen(DrawablePosition&& screenDrawablePosition, std::string peripheralName)
{
    std::unique_ptr<Screen> profileScreen {new Screen(std::move(screenDrawablePosition), false)};

    WindowManager& windowManager {WindowManager::GetInstance()};

    ResolutionManager& resolutionManager {ResolutionManager::GetInstance()};

    std::unique_ptr<Text> title {DrawableFactory::CreateText(DrawablePosition{*profileScreen->GetPosition(), 0, 0},
        TextData{peripheralName, TextHorizontalAlignments::RIGHT, TextVerticalAlignments::BOTTOM, FontFamilyTypes::ROBOTO_REGULAR,
        35.f, WHITE},
        false)};

    profileScreen->AddDrawable(std::move(title));

    std::unique_ptr<TextBox<char, ApplyKey>> profileName {DrawableFactory::CreateTextBox(DrawablePosition{*profileScreen->GetPosition(),
        static_cast<float>(windowManager.GetWidth() / 2), static_cast<float>(100)}, RectangleData{ImVec2{200, 100}, WHITE, 0, 10, false},
        TextData{"Holi", TextHorizontalAlignments::RIGHT, TextVerticalAlignments::BOTTOM, FontFamilyTypes::ROBOTO_REGULAR, 20.f, RED},
        false)};

    profileScreen->AddDrawable(std::move(profileName));

    return profileScreen;
}
