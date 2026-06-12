#pragma once
#include "MVP/View/BaseView.h"
#include "MVP/Presenter/Devices/DevicesPresenter.h"

#include "UI/Elements/Advanced/Button.h"
#include "UI/Elements/Advanced/RecycleView/RecycleView.h"

class DevicesView : public BaseView
{
public:

    DevicesView(bool isHidden);

    ~DevicesView() override = default;

    void Enable() override;

    void Disable() override;

private:

    void OnScrollUpdate();

    void OnDevicesRead();

    std::unique_ptr<DevicesPresenter> _presenter;

    std::unique_ptr<Text> _title;

    std::unique_ptr<Button> _reloadButton;

    std::unique_ptr<RecycleView> _devicesRecycleView;

    std::unique_ptr<Button> _templateDeviceButton;

    std::vector<std::unique_ptr<Button>> _devicesButtons;

};