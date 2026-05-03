#pragma once
#include "Canvas.h"

#include "Frontend/UI/Elements/Advanced/Button.h"
#include "Frontend/UI/Elements/Advanced/RecycleView.h"
#include "Frontend/UI/Strategies/RecycleViewStrategy/NotResizableRow.h"

class DevicesCanvas : public Canvas
{
public:

    DevicesCanvas(bool isHidden);

    ~DevicesCanvas() override = default;

private:

    void Reload();

    std::unique_ptr<Button> _reloadButton;

    std::unique_ptr<Text> _title;

    std::unique_ptr<RecycleView<Button, NotResizableRow>> _devicesRecycleView;

};