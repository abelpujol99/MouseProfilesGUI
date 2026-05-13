#pragma once
#include "Canvas.h"
#include "Frontend/UI/Elements/Advanced/Button.h"
#include "Frontend/UI/Elements/Advanced/RecycleView.h"
#include "Frontend/UI/Elements/Intermediate/Text.h"

class DeviceProfilesCanvas : public Canvas
{
public:

    DeviceProfilesCanvas(bool isHidden);

    ~DeviceProfilesCanvas() override = default;

    void SetTitle(std::string title);

    void Enable() override;

    void Disable() override;

private:

    void Back() const;

    void Edit() const;

    void Unload() const;

    std::unique_ptr<Text> _title;

    std::unique_ptr<Button> _backButton;

    std::unique_ptr<Text> _currentProfileTitle;

    std::unique_ptr<Text> _currentProfileName;

    std::unique_ptr<Button> _editCurrentProfileButton;

    std::unique_ptr<Button> _unloadCurrentProfileButton;

    std::unique_ptr<RecycleView<Button, NotResizableRow>> _profilesRecycleView;
};
