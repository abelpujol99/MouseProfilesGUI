#pragma once
#include "backend/Input/Strategy/IInputCommandStrategy.h"
#include "backend/Input/Strategy/IMouseInputState.h"

#include <memory>
#include <vector>

#include "backend/State/Button/IButtonInputStateAction.h"


class ButtonInputCommand;

class ButtonInputCommandStrategy : public IInputCommandStrategy, public IMouseInputState
{
public:

    ButtonInputCommandStrategy(std::vector<std::unique_ptr<ButtonInputCommand>>&& buttonInputCommands);

    void ChangeProfile(int profileIndex) override;

    void ChangeState(std::unique_ptr<IButtonInputStateAction>&& buttonInputState);

    void RegisterValue(int value) override;

    void Press();

    void Hold();

    void Release();

    void DelegateHoldCommand();

    void StopHoldCommand();

    void SwitchToOffState();

    const Duration& GetFirstTimeDelay() const override;

    const Duration& GetMillisToRepeatInput() const override;

    bool IsHolding() const override;

private:

    std::unique_ptr<IButtonInputStateAction> _buttonInputState;

    unsigned char _state {0};

    std::vector<std::unique_ptr<ButtonInputCommand>> _buttonInputCommands;

    ButtonInputCommand* _currentButtonInputCommand {nullptr};
};