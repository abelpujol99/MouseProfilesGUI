#pragma once
#include "BaseView.h"

#include "MVP/Presenter/Profile/ProfilePresenter.h"
#include "Strategies/TextStrategy/ApplyKey.h"
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

    void OnTitleUpdate();

    void OnSubProfileScrollUpdate();

    void OnInputScrollUpdate();

    std::unique_ptr<ProfilePresenter> _presenter;

    std::unique_ptr<Text> _title;

    std::unique_ptr<Button> _backButton;

    std::unique_ptr<TextBox<char, ApplyKey>> _profileNameTextBox;

    std::unique_ptr<Button> _profileLoadUnloadButton;

    std::unique_ptr<Button> _profileLinkButton;

    std::unique_ptr<Text> _subProfileTitle;

    std::unique_ptr<RecycleView> _subProfileRecycleView;

    std::unique_ptr<Text> _inputTitle;

    std::unique_ptr<Button> _inputRecordButton;

    std::unique_ptr<Button> _inputDeleteButton;

    std::unique_ptr<RecycleView> _inputRecycleView;

    std::unique_ptr<Text> _outputTitle;

    std::unique_ptr<Rectangle> _templateContainerRectangle;

    std::unique_ptr<Button> _templateSubProfileEditButton;

    std::unique_ptr<Button> _templateSubProfileDeleteButton;

    std::unique_ptr<Button> _templateInputEditButton;

    std::unique_ptr<Button> _templateInputDeleteButton;

    std::vector<std::unique_ptr<Rectangle>> _containerRectangles{};

    std::vector<std::unique_ptr<Button>> _subProfileEditButtons{};

    std::vector<std::unique_ptr<Button>> _subProfileDeleteButtons{};

    std::vector<std::unique_ptr<Button>> _inputEditButtons{};

    std::vector<std::unique_ptr<Button>> _inputDeleteButtons{};
};
