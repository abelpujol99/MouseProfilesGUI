#include "backend/State/Wheel/WheelTiltHoldStateAction.h"

#include "backend/Input/Strategies/WheelTiltInputCommandStrategy.h"

WheelTiltHoldStateAction::WheelTiltHoldStateAction(WheelTiltInputCommandStrategy* wheelInputCommand)
    : _wheelInputCommandStrategy(wheelInputCommand)
{}

void WheelTiltHoldStateAction::OnReceiveInputEvent()
{
    _wheelInputCommandStrategy->UpdateWheelTiltInputCommandPressRegister();
}