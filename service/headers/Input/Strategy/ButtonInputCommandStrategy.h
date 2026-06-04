#pragma once
#include "Input/Strategy/IInputCommandStrategy.h"
#include "Input/Strategy/IMouseInputState.h"


#include "Input/Button/ButtonInputCommand.h"
#include "State/Button/IButtonInputStateAction.h"


class ButtonInputCommandStrategy : public IInputCommandStrategy, public IMouseInputState
{
public:

    ButtonInputCommandStrategy(std::vector<std::unique_ptr<ButtonInputCommand>>&& buttonInputCommands);

    void ChangeProfile(int profileIndex) override;

    void ChangeState(std::unique_ptr<IButtonInputStateAction>&& buttonInputState);

    void RegisterValue(int value) override;

    void Press();

    void Hold() override;

    void Release() override;

    void DelegateHoldCommand();

    void StopHoldCommand();

    void SwitchToOffState();

    [[nodiscard]] const Duration& GetFirstTimeDelay() const override;

    [[nodiscard]] const Duration& GetMillisToRepeatInput() const override;

    [[nodiscard]] bool IsHolding() const override;

private:

    std::unique_ptr<IButtonInputStateAction> _buttonInputState;

    unsigned char _state {0};

    std::vector<std::unique_ptr<ButtonInputCommand>> _buttonInputCommands;

    ButtonInputCommand* _currentButtonInputCommand {nullptr};
};