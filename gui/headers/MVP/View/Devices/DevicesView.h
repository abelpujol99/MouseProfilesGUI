#pragma once
#include "MVP/View/BaseView.h"
#include "MVP/Presenter/Devices/DevicesPresenter.h"

#include "Strategies/ReadDevicesStrategy/IReadDevicesStrategy.h"
#include "UI/Elements/Advanced/Button.h"
#include "UI/Elements/Advanced/RecycleView.h"
#include "Strategies/RecycleViewStrategy/NotResizableRow.h"

class DevicesView : public BaseView<DevicesPresenter>
{
public:

    DevicesView(bool isHidden);

    ~DevicesView() override = default;

    void Enable() override;

    void Disable() override;

private:

    void OnScrollUpdate();

    void OnDevicesRead();

    void Reload() const;

    std::unique_ptr<Text> _title;

    std::unique_ptr<IReadDevicesStrategy> _readDevices;

    std::unique_ptr<Button> _reloadButton;

    std::unique_ptr<RecycleView<Button, NotResizableRow>> _devicesRecycleView;

    std::weak_ptr<std::function<void()>> _actionOnDevicesRead;

};