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
#include "Frontend/AnchorsDefines.h"
#include "Frontend/PivotDefines.h"

std::unique_ptr<Screen> ScreenFactory::CreateProfileScreen(ImVec2&& position, bool isHidden)
{
    std::filesystem::path resourceDir = RESOURCE_DIR;

    std::unique_ptr<Screen> profileScreen {DrawableFactory::CreateScreen(std::move(position),
        WindowManager::GetInstance().GetSize(), isHidden)};

    WindowManager& windowManager {WindowManager::GetInstance()};

    std::unique_ptr<RectDrawable> rectDrawable1 {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_LEFT, PIVOT_MIDDLE_LEFT,
        {0, 0},{750, 350}, isHidden)};

    std::unique_ptr<Rectangle> rectangle {DrawableFactory::CreateRectangle(RectangleData{WHITE, 0, 1, false}, isHidden)};

    auto catPath {resourceDir / "images/cat.jpg"};

    std::unique_ptr<Rectangle> texture {DrawableFactory::CreateRectangle(RectangleData{RED, 0, 1, false}, isHidden)};

    std::unique_ptr<RectDrawable> rectDrawable2 {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_CENTER, PIVOT_TOP_LEFT,
        {0, 0},{200, 100}, isHidden)};

    std::unique_ptr<Rectangle> texture2 {DrawableFactory::CreateRectangle(RectangleData{PURPLE, 0, 1, false}, isHidden)};

    std::unique_ptr<RectDrawable> rectDrawable3 {DrawableFactory::CreateRectDrawable(ANCHORS_BOTTOM_STRETCH, PIVOT_BOTTOM_CENTER,
        {0, 0},{400, 100}, isHidden)};

    rectDrawable3->AddDrawableComponent(std::move(texture2));

    rectDrawable2->AddDrawableComponent(std::move(texture));

    rectDrawable1->AddRectDrawable(std::move(rectDrawable3));

    rectDrawable1->AddRectDrawable(std::move(rectDrawable2));

    rectDrawable1->AddDrawableComponent(std::move(rectangle));

    profileScreen->AddRectDrawable(std::move(rectDrawable1));

    return profileScreen;
}
