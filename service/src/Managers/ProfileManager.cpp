#include "Managers/ProfileManager.h"

#include "Managers/ApplicationManager.h"
#include "Managers/ThreadsManager.h"
#include "Managers/VirtualDeviceManager.h"
#include "Factory/CommandFactory.h"
#include "Input/Strategy/ButtonInputCommandStrategy.h"
#include "Input/Strategy/WheelScrollInputCommandStrategy.h"
#include "Input/Strategy/WheelTiltInputCommandStrategy.h"
#include "TimeDefines.h"

std::unique_ptr<ProfileManager> ProfileManager::_profileManagerInstance = nullptr;

ProfileManager::ProfileManager() : _currentSubProfileIndex(0), _shouldMouseInputLoopRun(std::make_shared<bool>(false))
{
    MVPManager::GetInstance().SubscribeToShouldRunObserver([&](bool value) {
        *_shouldMouseInputLoopRun = value;
    });
}

ProfileManager& ProfileManager::GetInstance()
{
    if (!_profileManagerInstance)
    {
        _profileManagerInstance.reset(new ProfileManager());
    }

    return *_profileManagerInstance;
}

void ProfileManager::OnChangeApplicationFocus()
{
    _allSubProfilesCodes.clear();

    //TODO PROCESS PARAMETER DATA

    std::forward_list<Code> codes;

    //codes.emplace_front(8); //SCROLL
    codes.emplace_front(32); //LEFT TILT
    codes.emplace_front(64); //RIGHT TILT
    codes.emplace_front(80); //HIDDEN BUTTON
    codes.emplace_front(81); //TASK BUTTON
    codes.emplace_front(82); //BACK BUTTON
    codes.emplace_front(84); //FORWARD BUTTON
    codes.emplace_front(275); //SIDE BUTTON
    codes.emplace_front(276); //EXTRA BUTTON

    _allSubProfilesCodes.try_emplace(0, codes);

    codes.clear();

    codes.emplace_front(272); //LEFT BUTTON
    codes.emplace_front(273); //RIGHT BUTTON
    codes.emplace_front(275); //SIDE BUTTON

    _allSubProfilesCodes.try_emplace(1, codes);

    CreateProfile();
}

void ProfileManager::CreateProfile()
{
#define SUB_PROFILES 2

    std::unordered_map<Code, std::unique_ptr<IInputCommandStrategy>> profile;

    std::vector<std::unique_ptr<ButtonInputCommand>> buttonLeftInputCommands;
    buttonLeftInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonLeftPressEmits;
    buttonLeftPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonLeftPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_V, 1}));
    buttonLeftPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_V, 0}));
    buttonLeftPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    std::vector<EmitData> buttonLeftHoldEmits;
    buttonLeftHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonLeftHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_V, 1}));
    buttonLeftHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_V, 0}));
    buttonLeftHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    buttonLeftInputCommands.emplace_back(nullptr);

    buttonLeftInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonLeftPressEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(buttonLeftHoldEmits)),
                nullptr, Duration(500), Duration(20)));

    std::vector<std::unique_ptr<ButtonInputCommand>> buttonRightInputCommands;
    buttonRightInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonRightPressEmits;
    buttonRightPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonRightPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_C, 1}));
    buttonRightPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_C, 0}));
    buttonRightPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    std::vector<EmitData> buttonRightHoldEmits;
    buttonRightHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonRightHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_C, 1}));
    buttonRightHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_C, 0}));
    buttonRightHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    buttonRightInputCommands.emplace_back(nullptr);

    buttonRightInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonRightPressEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(buttonRightHoldEmits)),
                nullptr, Duration(500), Duration(20)));

    std::vector<std::unique_ptr<ButtonInputCommand>> buttonBackInputCommands;
    buttonBackInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonBackPressEmits;
    buttonBackPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonBackPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 1}));
    buttonBackPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 0}));
    buttonBackPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    std::vector<EmitData> buttonBackHoldEmits;
    buttonBackHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonBackHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 1}));
    buttonBackHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 0}));
    buttonBackHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    buttonBackInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonBackPressEmits)), CommandFactory::CreateEmitInputEventCommand(std::move(buttonBackHoldEmits)),
            nullptr, Duration(500), Duration(20)));

    buttonBackInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<ButtonInputCommand>> buttonForwardInputCommands;
    buttonForwardInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonForwardPressEmits;
    buttonForwardPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonForwardPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_W, 1}));

    std::vector<EmitData> buttonForwardHoldEmits;
    buttonForwardHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_W, 2}));

    std::vector<EmitData> buttonForwardReleaseEmits;
    buttonForwardReleaseEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_W, 0}));
    buttonForwardReleaseEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    buttonForwardInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonForwardPressEmits)), CommandFactory::CreateEmitInputEventCommand(std::move(buttonForwardHoldEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(buttonForwardReleaseEmits)), Duration(500), Duration(20)));

    buttonForwardInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<ButtonInputCommand>> buttonSideInputCommands;
    buttonSideInputCommands.reserve(SUB_PROFILES);

    buttonSideInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateSwitchToProfileCommand(1), nullptr, nullptr, Duration(500), Duration(20)));

    buttonSideInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        nullptr, nullptr, CommandFactory::CreateSwitchToMainProfileCommand(), Duration(500), Duration(20)));

    std::vector<std::unique_ptr<ButtonInputCommand>> buttonExtraInputCommands;
    buttonExtraInputCommands.reserve(SUB_PROFILES);

    buttonExtraInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateShutdownApplicationCommand(), nullptr, nullptr, Duration(500), Duration(20)));

    buttonExtraInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<ButtonInputCommand>> buttonTaskInputCommands;
    buttonTaskInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonTaskPressEmits;
    buttonTaskPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 1}));
    buttonTaskPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 0}));

    std::vector<EmitData> buttonTaskHoldEmits;
    buttonTaskHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_K, 1}));
    buttonTaskHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_K, 0}));

    std::vector<EmitData> buttonTaskReleaseEmits;
    buttonTaskReleaseEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_L, 1}));
    buttonTaskReleaseEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_L, 0}));

    buttonTaskInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonTaskPressEmits)), CommandFactory::CreateEmitInputEventCommand(std::move(buttonTaskHoldEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(buttonTaskReleaseEmits)), Duration(500), Duration(1000)));

    buttonTaskInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<ButtonInputCommand>> buttonHiddenInputCommands;
    buttonHiddenInputCommands.reserve(SUB_PROFILES);

    buttonHiddenInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateShutdownApplicationCommand(), nullptr, nullptr, Duration(500), Duration(20)));

    buttonHiddenInputCommands.emplace_back(nullptr);

    profile.try_emplace(80, std::make_unique<ButtonInputCommandStrategy>(std::move(buttonHiddenInputCommands)));
    profile.try_emplace(81, std::make_unique<ButtonInputCommandStrategy>(std::move(buttonTaskInputCommands)));
    profile.try_emplace(82, std::make_unique<ButtonInputCommandStrategy>(std::move(buttonBackInputCommands)));
    profile.try_emplace(84, std::make_unique<ButtonInputCommandStrategy>(std::move(buttonForwardInputCommands)));
    profile.try_emplace(272, std::make_unique<ButtonInputCommandStrategy>(std::move(buttonLeftInputCommands)));
    profile.try_emplace(273, std::make_unique<ButtonInputCommandStrategy>(std::move(buttonRightInputCommands)));
    profile.try_emplace(275, std::make_unique<ButtonInputCommandStrategy>(std::move(buttonSideInputCommands)));
    profile.try_emplace(276, std::make_unique<ButtonInputCommandStrategy>(std::move(buttonExtraInputCommands)));

    std::vector<std::unique_ptr<ButtonInputCommand>> wheelNegativeTiltInputCommands;
    buttonHiddenInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> wheelNegativeTiltPressEmits;
    wheelNegativeTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 1}));
    wheelNegativeTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFT, 1}));
    wheelNegativeTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFT, 0}));
    wheelNegativeTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 0}));

    std::vector<EmitData> wheelNegativeTiltHoldEmits;
    wheelNegativeTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 1}));
    wheelNegativeTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFT, 1}));
    wheelNegativeTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFT, 0}));
    wheelNegativeTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 0}));

    wheelNegativeTiltInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(wheelNegativeTiltPressEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(wheelNegativeTiltHoldEmits)),
                nullptr, Duration(500), Duration(100)));

    wheelNegativeTiltInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<ButtonInputCommand>> wheelPositiveTiltInputCommands;
    wheelPositiveTiltInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> wheelPositiveTiltPressEmits;
    wheelPositiveTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 1}));
    wheelPositiveTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_RIGHT, 1}));
    wheelPositiveTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_RIGHT, 0}));
    wheelPositiveTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 0}));

    std::vector<EmitData> wheelPositiveTiltHoldEmits;
    wheelPositiveTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 1}));
    wheelPositiveTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_RIGHT, 1}));
    wheelPositiveTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_RIGHT, 0}));
    wheelPositiveTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 0}));

    wheelPositiveTiltInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(wheelPositiveTiltPressEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(wheelPositiveTiltHoldEmits)),
                nullptr, Duration(500), Duration(100)));

    wheelPositiveTiltInputCommands.emplace_back(nullptr);

    profile.try_emplace(32, std::make_unique<ButtonInputCommandStrategy>(std::move(wheelNegativeTiltInputCommands)));
    profile.try_emplace(64, std::make_unique<ButtonInputCommandStrategy>(std::move(wheelPositiveTiltInputCommands)));

    std::unordered_map<unsigned long, std::unordered_set<int>> mouseCapableInputs;

    std::unordered_set<int> inputEvs;

    inputEvs.emplace(0);
    inputEvs.emplace(1);

    mouseCapableInputs.try_emplace(UI_SET_EVBIT, std::move(inputEvs));

    std::unordered_set<int> inputEvKeys;

    inputEvKeys.emplace(17);
    inputEvKeys.emplace(19);
    inputEvKeys.emplace(29);
    inputEvKeys.emplace(36);
    inputEvKeys.emplace(37);
    inputEvKeys.emplace(38);
    inputEvKeys.emplace(46);
    inputEvKeys.emplace(47);
    inputEvKeys.emplace(56);
    inputEvKeys.emplace(105);
    inputEvKeys.emplace(106);

    uinput_setup usetup {};
    snprintf(usetup.name, UINPUT_MAX_NAME_SIZE, "Virtual Keyboard");
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1b1c;
    usetup.id.product = 0x1b2d;

    mouseCapableInputs.try_emplace(UI_SET_KEYBIT, std::move(inputEvKeys));

    VirtualDeviceManager::GetInstance().CreateVirtualDevice(KEYBOARD, mouseCapableInputs, usetup);

    SetProfile(std::move(profile));
}

void ProfileManager::SetProfile(std::unordered_map<Code, std::unique_ptr<IInputCommandStrategy>>&& profile)
{
    _profile = std::move(profile);

    UpdateCodesBindings();
}

void ProfileManager::ChangeCurrentSubProfile(uint8_t subProfileIndex)
{
    for (const auto& action : _actionsOnChangeProfile)
    {
        (*action)();
    }

    _actionsOnChangeProfile.clear();
    _currentSubProfileCodes.clear();

    _currentSubProfileIndex = subProfileIndex;

    UpdateCodesBindings();
}

void ProfileManager::ChangeMouseInputState(IMouseInputState* mouseInputState)
{
    _mouseInputState = mouseInputState;
    *_shouldMouseInputLoopRun = false;
    _shouldMouseInputLoopRun = std::make_shared<bool>(true);
    ThreadsManager::GetInstance().SetProfileAction([&](){MouseInputStateLoop(_shouldMouseInputLoopRun);});
}

bool ProfileManager::IsCodeInUse(Code code) const
{
    return _currentSubProfileCodes.contains(code);
}

void ProfileManager::UpdateCodesBindings()
{
    std::forward_list<Code>& codes {_allSubProfilesCodes.at(_currentSubProfileIndex)};

    for (auto& code : codes)
    {
        _currentSubProfileCodes.emplace(code);

        _profile.at(code)->ChangeProfile(_currentSubProfileIndex);
    }
}

void ProfileManager::MouseInputStateLoop(std::shared_ptr<bool> shouldKeepRun)
{
    const Duration& firstTimeDelay {_mouseInputState->GetFirstTimeDelay()};

    Duration timeElapsed {0};

    TimePoint start {SystemClock::now()};

    Duration defaultThreadSleepMillis {Duration(DEFAULT_THREAD_SLEEP_MILLIS)};

    do {

        Duration difference {SystemClock::now() - start};
        timeElapsed += difference;
        start = SystemClock::now();
        std::this_thread::sleep_for(defaultThreadSleepMillis);

    } while (*shouldKeepRun && _mouseInputState && _mouseInputState->IsHolding() && timeElapsed < firstTimeDelay);

    const Duration& millisToRepeatInput {_mouseInputState->GetMillisToRepeatInput()};

    while (*shouldKeepRun && _mouseInputState && _mouseInputState->IsHolding())
    {
        _mouseInputState->Hold();

        timeElapsed = Duration(0);

        do {

            Duration difference {SystemClock::now() - start};
            timeElapsed += difference;
            start = SystemClock::now();
            std::this_thread::sleep_for(defaultThreadSleepMillis);

        } while (*shouldKeepRun && _mouseInputState && _mouseInputState->IsHolding() && timeElapsed < millisToRepeatInput);
    }

    if (!_mouseInputState)
    {
        return;
    }

    _mouseInputState->Release();
    _mouseInputState = nullptr;
}

void ProfileManager::RegisterInput(Code code, int value) const
{
    _mutex.lock();
    _profile.at(code)->RegisterValue(value);
    _mutex.unlock();
}

void ProfileManager::UnsubscribeToActionsOnChangeProfile(const std::weak_ptr<std::function<void()>>& weakActionOnChangeProfile)
{
    if (const auto actionOnChangeProfile {weakActionOnChangeProfile.lock()})
    {
        auto itEnd {_actionsOnChangeProfile.cend()};

        for (auto it {_actionsOnChangeProfile.begin()}; it != itEnd; ++it)
        {
            if (it->get() != actionOnChangeProfile.get())
            {
                continue;
            }

            _actionsOnChangeProfile.erase(it);

            return;
        }
    }
}