#pragma once
#include "Backend/Input/Strategy/IInputCommandStrategy.h"
#include "Backend/Input/Strategy/IMouseInputState.h"

#include <vector>

#include "Backend/Input/Wheel/Tilt/WheelTiltInputCommand.h"
#include "Backend/State/Wheel/IWheelTiltInputStateAction.h"


class WheelTiltInputCommandStrategy : public IInputCommandStrategy, public IMouseInputState
{
public:

    WheelTiltInputCommandStrategy(std::vector<std::unique_ptr<WheelTiltInputCommand>>&& wheelNegativeInputCommands,
        std::vector<std::unique_ptr<WheelTiltInputCommand>>&& wheelPositiveInputCommands);

    void ChangeProfile(int profileIndex) override;

    void ChangeState(std::unique_ptr<IWheelTiltInputStateAction>&& wheelTiltInputState);

    void RegisterValue(int value) override;

    void Press() const;

    void Hold() override;

    void Release() override;

    void DelegateHoldCommand();

    void StopHoldCommand();

    void UpdateWheelTiltInputCommandPressRegister() const;

    [[nodiscard]] const Duration& GetMillisUntilInputStops() const;

    [[nodiscard]] const Duration& GetFirstTimeDelay() const override;

    [[nodiscard]] const Duration& GetMillisToRepeatInput() const override;

    [[nodiscard]] bool IsHolding() const override;

private:

    std::unique_ptr<IWheelTiltInputStateAction> _wheelNegativeTiltInputState;
    std::unique_ptr<IWheelTiltInputStateAction> _wheelPositiveTiltInputState;

    std::vector<std::unique_ptr<WheelTiltInputCommand>> _wheelNegativeInputCommands;
    std::vector<std::unique_ptr<WheelTiltInputCommand>> _wheelPositiveInputCommands;

    WheelTiltInputCommand* _currentWheelNegativeInputCommand {nullptr};
    WheelTiltInputCommand* _currentWheelPositiveInputCommand {nullptr};

    WheelTiltInputCommand* _currentWheelInputCommand {nullptr};

};
