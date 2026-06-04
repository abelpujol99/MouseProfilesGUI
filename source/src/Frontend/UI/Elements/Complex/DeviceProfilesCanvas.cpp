#include "Frontend/UI/Elements/Complex/DeviceProfilesCanvas.h"

#include "Backend/Managers/ApplicationManager.h"
#include "Frontend/RectangleDefines.h"
#include "Frontend/TextDefines.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/Managers/View/DrawManager.h"
#include "Frontend/UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"

DeviceProfilesCanvas::DeviceProfilesCanvas(bool isHidden) : Canvas(isHidden)
{
    std::unique_ptr<RectDrawable> topBarRect{DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {1, 0.15}},
        PIVOT_MIDDLE_CENTER,{0, 0}, {0, 0}, false)};

    std::unique_ptr<RectDrawable> titleRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_STRETCH,
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _title = DrawableFactory::CreateText(TextData{"", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE_SIZE, WHITE});

    titleRect->AddDrawableComponent(_title.get());
    topBarRect->AddRectDrawable(std::move(titleRect));

    std::unique_ptr<RectDrawable> backButtonRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_LEFT,
        PIVOT_MIDDLE_LEFT, {50, 0}, {50, 50}, false)};

    _backButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Back", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE}, [&](){Back();}, false);

    backButtonRect->AddDrawableComponent(_backButton.get());
    topBarRect->AddRectDrawable(std::move(backButtonRect));

    std::unique_ptr<RectDrawable> currentProfileRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.15}, {1, 0.35}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    std::unique_ptr<RectDrawable> currentProfileTitleRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {1, 0.4}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _currentProfileTitle = DrawableFactory::CreateText(TextData{"Current Profile", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE});

    currentProfileTitleRect->AddDrawableComponent(_currentProfileTitle.get());

    std::unique_ptr<RectDrawable> currentProfileNameRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.4}, {1, 0.7}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _currentProfileName = DrawableFactory::CreateText(TextData{"Name", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, SUB_TITLE_SIZE, WHITE});

    currentProfileNameRect->AddDrawableComponent(_currentProfileName.get());

    std::unique_ptr<RectDrawable> currentProfileButtonsRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.7}, {1, 1}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    std::unique_ptr<RectDrawable> currentProfileEditButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.45, 0.5}, {0.45, 0.5}},
        PIVOT_MIDDLE_RIGHT, {0, 0}, {50, 50}, false)};

    _editCurrentProfileButton = DrawableFactory::CreateButton(RectangleData{BLUE, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Edit", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        SUB_TITLE_SIZE, WHITE}, [&](){Edit();}, false);

    currentProfileEditButtonRect->AddDrawableComponent(_editCurrentProfileButton.get());

    std::unique_ptr<RectDrawable> currentProfileUnloadButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.55, 0.5}, {0.55, 0.5}},
        PIVOT_MIDDLE_LEFT, {0, 0}, {50, 50}, false)};

    _unloadCurrentProfileButton = DrawableFactory::CreateButton(RectangleData{BLUE, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Unload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        SUB_TITLE_SIZE, WHITE}, [&](){Unload();}, false);

    currentProfileUnloadButtonRect->AddDrawableComponent(_unloadCurrentProfileButton.get());

    currentProfileButtonsRect->AddRectDrawable(std::move(currentProfileEditButtonRect));
    currentProfileButtonsRect->AddRectDrawable(std::move(currentProfileUnloadButtonRect));

    currentProfileRect->AddRectDrawable(std::move(currentProfileTitleRect));
    currentProfileRect->AddRectDrawable(std::move(currentProfileNameRect));
    currentProfileRect->AddRectDrawable(std::move(currentProfileButtonsRect));

    std::unique_ptr<RectDrawable> profileRecycleViewRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.35}, {1, 1}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _profilesRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(4, {0.1, 0.1},{0, 150}, 2,
        [](Button& button){button.Subscribe();},
        [](Button& button){button.Unsubscribe();},
        false);

    profileRecycleViewRect->AddDrawableComponent(_profilesRecycleView.get());

    AddRectDrawable(std::move(topBarRect));
    AddRectDrawable(std::move(currentProfileRect));
    AddRectDrawable(std::move(profileRecycleViewRect));
}

void DeviceProfilesCanvas::SetTitle(std::string title)
{
    _title->SetText(title);

    ApplicationManager& applicationManager {ApplicationManager::GetInstance()};

    applicationManager.SetEditingDeviceProfiles(_title->GetText());

    std::unordered_map<std::string, Profile> deviceProfiles {applicationManager.GetDeviceProfiles(_title->GetText())};

    for (auto [profileName, profile] : deviceProfiles)
    {
        _profilesRecycleView->AddDrawableComponent(DrawableFactory::CreateButton(RectangleData{WHITE, LOW_ROUNDING, THIN_BORDER, false},
            TextData{profileName, TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE},
            [profileName, profile]()
            {
                //TODO PASS TO DEVICE PROFILE CANVAS
            }, false));
    }
}

void DeviceProfilesCanvas::Enable()
{
    *_mustBeHidden = false;

    _backButton->Subscribe();

    _editCurrentProfileButton->Subscribe();

    _unloadCurrentProfileButton->Subscribe();

    _profilesRecycleView->Enable();
}

void DeviceProfilesCanvas::Disable()
{
    *_mustBeHidden = true;

    _backButton->Unsubscribe();

    _editCurrentProfileButton->Unsubscribe();

    _unloadCurrentProfileButton->Unsubscribe();

    _profilesRecycleView->Disable();
}

void DeviceProfilesCanvas::Back() const
{
    DrawManager::GetInstance().EnableDevicesCanvas();
}

#include <iostream>

void DeviceProfilesCanvas::Edit() const
{
    std::cout << "Edit" << std::endl;
}

void DeviceProfilesCanvas::Unload() const
{
    std::cout << "Unload" << std::endl;
}
