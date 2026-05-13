#pragma once
#include "Canvas.h"
#include "Frontend/Strategies/ReadDevicesStrategy/IReadDevicesStrategy.h"

#include "Frontend/UI/Elements/Advanced/Button.h"
#include "Frontend/UI/Elements/Advanced/RecycleView.h"
#include "Frontend/Strategies/RecycleViewStrategy/NotResizableRow.h"

class DevicesCanvas : public Canvas
{
public:

    DevicesCanvas(bool isHidden);

    ~DevicesCanvas() override = default;

private:

    void Reload() const;

    std::unique_ptr<IReadDevicesStrategy> _readDevices;

    std::unique_ptr<Button> _reloadButton;

    std::unique_ptr<Text> _title;

    std::unique_ptr<RecycleView<Button, NotResizableRow>> _devicesRecycleView;

    std::unique_ptr<Rectangle> _testRect1;
    std::unique_ptr<Rectangle> _testRect2;
    std::unique_ptr<Rectangle> _testRect3;
    std::unique_ptr<Rectangle> _testRect4;

};