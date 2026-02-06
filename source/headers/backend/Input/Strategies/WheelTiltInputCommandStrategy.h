#pragma once
#include "backend/Input/Strategies/IInputCommandStrategy.h"

#include <memory>
#include <vector>

#include "backend/State/IMouseInputState.h"

class IWheelTiltInputStateAction;
class WheelTiltInputCommand;

class WheelTiltInputCommandStrategy : public IInputCommandStrategy, public IMouseInputState
{
private:

    std::unique_ptr<IWheelTiltInputStateAction> _wheelNegativeTiltInputState;
    std::unique_ptr<IWheelTiltInputStateAction> _wheelPositiveTiltInputState;

    std::vector<std::unique_ptr<WheelTiltInputCommand>> _wheelNegativeInputCommands;
    std::vector<std::unique_ptr<WheelTiltInputCommand>> _wheelPositiveInputCommands;

    WheelTiltInputCommand* _currentWheelNegativeInputCommand {nullptr};
    WheelTiltInputCommand* _currentWheelPositiveInputCommand {nullptr};

    WheelTiltInputCommand* _currentWheelInputCommand {nullptr};

public:

    WheelTiltInputCommandStrategy(std::vector<std::unique_ptr<WheelTiltInputCommand>>&& wheelNegativeInputCommands,
        std::vector<std::unique_ptr<WheelTiltInputCommand>>&& wheelPositiveInputCommands);

    void ChangeProfile(int profileIndex) override;

    void ChangeState(std::unique_ptr<IWheelTiltInputStateAction>&& wheelTiltInputState);

    void RegisterValue(int value) override;

    void Press() const;

    void Hold();

    void Release();

    void DelegateHoldCommand();

    void StopHoldCommand();

    void UpdateWheelTiltInputCommandPressRegister() const;

    const Duration& GetMillisUntilInputStops() const;

    const Duration& GetFirstTimeDelay() const override;

    const Duration& GetMillisToRepeatInput() const override;

    bool IsHolding() const;
};
