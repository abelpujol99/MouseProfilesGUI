#include "Frontend/UI/Elements/Complex/DevicesCanvas.h"

#include "Frontend/ColorDefines.h"
#include "Frontend/RectangleDefines.h"
#include "Frontend/TextDefines.h"
#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/Managers/View/DrawManager.h"
#include "Frontend/Strategies/ReadDevicesStrategy/ReadLinuxDevices.h"
#include "Frontend/UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"

DevicesCanvas::DevicesCanvas(bool isHidden) : Canvas(isHidden), _readDevices(std::make_unique<ReadLinuxDevices>())
{
    std::unique_ptr<RectDrawable> topBarRect{DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {1, 0.15}},
        PIVOT_MIDDLE_CENTER,{0, 0}, {0, 100}, false)};

    std::unique_ptr<RectDrawable> titleRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_STRETCH,
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _title = DrawableFactory::CreateText(TextData{"Devices", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE_SIZE, WHITE});

    titleRect->AddDrawableComponent(_title.get());
    topBarRect->AddRectDrawable(std::move(titleRect));

    std::unique_ptr<RectDrawable> reloadButtonRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_LEFT,
        PIVOT_MIDDLE_LEFT, {50, 0}, {50, 50}, false)};

    _reloadButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Reload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE}, [&](){Reload();}, false);

    reloadButtonRect->AddDrawableComponent(_reloadButton.get());
    topBarRect->AddRectDrawable(std::move(reloadButtonRect));

    std::unique_ptr<RectDrawable> recycleViewRect {DrawableFactory::CreateRectDrawable(Anchors{{0.1, 0.15}, {0.9, 1}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _devicesRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(4, {0.05, 0.05}, {0, 150}, 2,
        [](Button& button){button.Subscribe();},
        [](Button& button){button.Unsubscribe();},
        false);

    recycleViewRect->AddDrawableComponent(_devicesRecycleView.get());

    AddRectDrawable(std::move(topBarRect));
    AddRectDrawable(std::move(recycleViewRect));

    _reloadButton->Click();
}

void DevicesCanvas::Enable()
{
    *_mustBeHidden = false;

    _reloadButton->Subscribe();

    _devicesRecycleView->Enable();
}

void DevicesCanvas::Disable()
{
    *_mustBeHidden = true;

    _reloadButton->Unsubscribe();

    _devicesRecycleView->Disable();
}

void DevicesCanvas::Reload() const
{
    _devicesRecycleView->Clear();

    std::vector<DeviceInfo> devicesInfo {_readDevices->ReturnDevices()};

    auto itEnd {devicesInfo.cend()};

    for (auto it{devicesInfo.begin()}; it != itEnd; ++it)
    {
        std::string name {it->name};
        std::string path {it->path};

        _devicesRecycleView->AddDrawableComponent(DrawableFactory::CreateButton(RectangleData{WHITE, LOW_ROUNDING, THIN_BORDER, false},
            TextData{name, TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE},
            [name, path]() {
                DrawManager::GetInstance().EnableDeviceProfilesCanvas(name);
            }, false));
    }
}