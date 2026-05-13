#include "Frontend/UI/Elements/Complex/DevicesCanvas.h"

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
    /*std::unique_ptr<RectDrawable> topBarRect{DrawableFactory::CreateRectDrawable(ANCHORS_TOP_STRETCH, PIVOT_TOP_CENTER,
        {0, 0}, {0, 100}, false)};

    _reloadButton = std::make_unique<Button>([&](){Reload();}, false);

    _reloadButton->SetRectangle(DrawableFactory::CreateRectangle(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, true}));

    _reloadButton->SetText(DrawableFactory::CreateText(TextData{"Reload", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE}));

    std::unique_ptr<RectDrawable> reloadButtonRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_LEFT,
        PIVOT_MIDDLE_LEFT, {50, 0}, {50, 50}, false)};

    reloadButtonRect->AddDrawableComponent(_reloadButton.get());

    topBarRect->AddRectDrawable(std::move(reloadButtonRect));

    _title = DrawableFactory::CreateText(TextData{"Devices", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE_SIZE, WHITE});

    std::unique_ptr<RectDrawable> titleRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_STRETCH,
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    titleRect->AddDrawableComponent(_title.get());

    topBarRect->AddRectDrawable(std::move(titleRect));

    AddRectDrawable(std::move(topBarRect));

    std::unique_ptr<RectDrawable> recycleViewRect {DrawableFactory::CreateRectDrawable(Anchors{{0.1, 0.2}, {0.9, 1}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _devicesRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(4, {0.05, 0.05}, {0, 150}, 2,
        false);

    recycleViewRect->AddDrawableComponent(_devicesRecycleView.get());

    AddRectDrawable(std::move(recycleViewRect));

    _reloadButton->Click();*/

    std::unique_ptr<RectDrawable> test1Rect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.5}, {1, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, false)};

    _testRect1 = DrawableFactory::CreateRectangle(RectangleData{WHITE, 0, 0, false}, false);

    test1Rect->AddDrawableComponent(_testRect1.get());

    std::unique_ptr<RectDrawable> test2Rect {DrawableFactory::CreateRectDrawable(Anchors{{0.1, 0.1}, {0.9, 0.9}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, false)};

    _testRect2 = DrawableFactory::CreateRectangle(RectangleData{PURPLE, 0, 0, false}, false);

    test2Rect->AddDrawableComponent(_testRect2.get());

    std::unique_ptr<RectDrawable> test3Rect {DrawableFactory::CreateRectDrawable(Anchors{{0.1, 0.1}, {0.9, 0.9}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, false)};

    _testRect3 = DrawableFactory::CreateRectangle(RectangleData{BROWN, 0, 0, false}, false);

    test3Rect->AddDrawableComponent(_testRect3.get());

    std::unique_ptr<RectDrawable> test4Rect {DrawableFactory::CreateRectDrawable(Anchors{{0.1, 0.1}, {0.9, 0.9}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, false)};

    _testRect4 = DrawableFactory::CreateRectangle(RectangleData{RED, 0, 0, false}, false);

    test4Rect->AddDrawableComponent(_testRect4.get());

    test3Rect->AddRectDrawable(std::move(test4Rect));

    test2Rect->SetIsHidden(true);

    test2Rect->AddRectDrawable(std::move(test3Rect));

    test1Rect->AddRectDrawable(std::move(test2Rect));

    AddRectDrawable(std::move(test1Rect));
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