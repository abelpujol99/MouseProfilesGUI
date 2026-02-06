#include "backend/State/Wheel/WheelTiltPressStateAction.h"

#include "backend/Input/Strategies/WheelTiltInputCommandStrategy.h"
#include "backend/State/Wheel/WheelTiltHoldStateAction.h"

WheelTiltPressStateAction::WheelTiltPressStateAction(WheelTiltInputCommandStrategy* wheelInputCommandStrategy)
    : _wheelInputCommandStrategy(wheelInputCommandStrategy)
{}

void WheelTiltPressStateAction::OnReceiveInputEvent()
{
    _wheelInputCommandStrategy->Press();
    _wheelInputCommandStrategy->UpdateWheelTiltInputCommandPressRegister();

    _wheelInputCommandStrategy->ChangeState(std::make_unique<WheelTiltHoldStateAction>(_wheelInputCommandStrategy));
}
