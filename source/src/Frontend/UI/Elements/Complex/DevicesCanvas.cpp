#include "Frontend/UI/Elements/Complex/DevicesCanvas.h"

#include <iostream>

#include "Frontend/ColorDefines.h"
#include "Frontend/RectangleDefines.h"
#include "Frontend/TextDefines.h"
#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/Strategies/ReadDevicesStrategy/ReadLinuxDevices.h"
#include "Frontend/UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"

DevicesCanvas::DevicesCanvas(bool isHidden) : Canvas(isHidden), _readDevices(std::make_unique<ReadLinuxDevices>())
{
    std::unique_ptr<RectDrawable> topBarRect{DrawableFactory::CreateRectDrawable(ANCHORS_TOP_STRETCH, PIVOT_TOP_CENTER,
        {0, 0}, {0, 100}, isHidden)};

    _reloadButton = std::make_unique<Button>([&](){Reload();}, isHidden);

    _reloadButton->SetRectangle(DrawableFactory::CreateRectangle(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, true}));

    _reloadButton->SetText(DrawableFactory::CreateText(TextData{"Reload", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE}));

    std::unique_ptr<RectDrawable> reloadButtonRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_LEFT,
        PIVOT_MIDDLE_LEFT, {50, 0}, {50, 50}, isHidden)};

    reloadButtonRect->AddDrawableComponent(_reloadButton.get());

    topBarRect->AddRectDrawable(std::move(reloadButtonRect));

    _title = DrawableFactory::CreateText(TextData{"Devices", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE_SIZE, WHITE});

    std::unique_ptr<RectDrawable> titleRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_STRETCH,
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, isHidden)};

    titleRect->AddDrawableComponent(_title.get());

    topBarRect->AddRectDrawable(std::move(titleRect));

    AddRectDrawable(std::move(topBarRect));

    std::unique_ptr<RectDrawable> recycleViewRect {DrawableFactory::CreateRectDrawable(Anchors{{0.1, 0.2}, {0.9, 1}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, isHidden)};

    _devicesRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(4, {0.05, 0.05}, {0, 150}, 2,
        isHidden);

    recycleViewRect->AddDrawableComponent(_devicesRecycleView.get());

    AddRectDrawable(std::move(recycleViewRect));

    _reloadButton->Click();
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
            TITLE_SIZE, WHITE},
            [name, path]() {
                //TODO OPEN DEVICE PROFILES WINDOW
            }, false));
    }
}