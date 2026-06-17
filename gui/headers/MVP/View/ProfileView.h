#pragma once
#include "BaseView.h"

#include "MVP/Presenter/Profile/ProfilePresenter.h"
#include "Strategies/DrawStrategy/Rectangle/DrawEmptyRectangle.h"
#include "Strategies/TextStrategy/ApplyKey.h"
#include "Strategies/TextStrategy/DisplayKey.h"
#include "UI/Elements/Advanced/Button.h"
#include "UI/Elements/Advanced/RecycleView/RecycleView.h"
#include "UI/Elements/Advanced/Text/TextBox.h"
#include "UI/Elements/Intermediate/Text.h"

class ProfileView : public BaseView
{
public:

    ProfileView(bool isHidden);

    ~ProfileView() override = default;

    void SetDeviceName(std::string deviceName);

    void SetProfileIndex(uint8_t profileIndex);

    void Enable() override;

    void Disable() override;

private:

    void OnTitleUpdate() const;

    void OnSubProfileScrollUpdate() const;

    void OnInputScrollUpdate() const;

    std::unique_ptr<ProfilePresenter> _presenter;

    std::unique_ptr<Text> _title;

    std::unique_ptr<Button> _backButton;

    std::unique_ptr<TextBox<ApplyKey>> _profileNameTextBox;

    std::unique_ptr<Button> _profileLoadUnloadButton;

    std::unique_ptr<Button> _profileLinkButton;

    std::unique_ptr<Text> _subProfileTitle;

    std::unique_ptr<RecycleView> _subProfileRecycleView;

    std::unique_ptr<Text> _inputTitle;

    std::unique_ptr<Button> _inputRecordButton;

    std::unique_ptr<Button> _inputDeleteButton;

    std::unique_ptr<RecycleView> _inputRecycleView;

    std::unique_ptr<Text> _outputTitle;

    std::unique_ptr<Button> _emitInputEventCommandButton;

    std::unique_ptr<Button> _macroCommandButton;

    std::unique_ptr<Button> _switchToSubProfileCommandButton;

    std::unique_ptr<Button> _shutdownApplicationCommandButton;

    std::unique_ptr<TextBox<ApplyKey>> _inputTextBox;

    std::unique_ptr<TextBox<DisplayKey>> _inputDisplayTextBox;

    std::unique_ptr<RecycleView> _switchToSubProfileRecycleView;


    std::unique_ptr<Rectangle<DrawEmptyRectangle>> _templateContainerRectangle;

    std::unique_ptr<Button> _templateSubProfileEditButton;

    std::unique_ptr<Button> _templateSubProfileDeleteButton;

    std::unique_ptr<Button> _templateInputEditButton;

    std::unique_ptr<Button> _templateInputDeleteButton;

    std::unique_ptr<Button> _templateSwitchToSubProfileButton;

    std::vector<std::unique_ptr<Rectangle<DrawEmptyRectangle>>> _containerRectangles{};

    std::vector<std::unique_ptr<Button>> _subProfileEditButtons{};

    std::vector<std::unique_ptr<Button>> _subProfileDeleteButtons{};

    std::vector<std::unique_ptr<Button>> _inputEditButtons{};

    std::vector<std::unique_ptr<Button>> _inputDeleteButtons{};

    std::vector<std::unique_ptr<Button>> _switchToSubProfileListButtons{};
};
