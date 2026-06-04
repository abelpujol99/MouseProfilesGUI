#include "State/Wheel/WheelTiltPressStateAction.h"

#include "Input/Strategy/WheelTiltInputCommandStrategy.h"
#include "State/Wheel/WheelTiltHoldStateAction.h"

WheelTiltPressStateAction::WheelTiltPressStateAction(WheelTiltInputCommandStrategy* wheelInputCommandStrategy)
    : _wheelInputCommandStrategy(wheelInputCommandStrategy)
{}

void WheelTiltPressStateAction::OnReceiveInputEvent()
{
    _wheelInputCommandStrategy->Press();
    _wheelInputCommandStrategy->UpdateWheelTiltInputCommandPressRegister();

    _wheelInputCommandStrategy->ChangeState(std::make_unique<WheelTiltHoldStateAction>(_wheelInputCommandStrategy));
}
