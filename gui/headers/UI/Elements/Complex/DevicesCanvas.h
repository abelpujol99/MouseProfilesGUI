#pragma once
#include "Canvas.h"
#include "Strategies/ReadDevicesStrategy/IReadDevicesStrategy.h"

#include "UI/Elements/Advanced/Button.h"
#include "UI/Elements/Advanced/RecycleView.h"
#include "Strategies/RecycleViewStrategy/NotResizableRow.h"

class DevicesCanvas : public Canvas
{
public:

    DevicesCanvas(bool isHidden);

    ~DevicesCanvas() override = default;

    void Enable() override;

    void Disable() override;

private:

    void Reload() const;

    std::unique_ptr<Text> _title;

    std::unique_ptr<IReadDevicesStrategy> _readDevices;

    std::unique_ptr<Button> _reloadButton;

    std::unique_ptr<RecycleView<Button, NotResizableRow>> _devicesRecycleView;

};