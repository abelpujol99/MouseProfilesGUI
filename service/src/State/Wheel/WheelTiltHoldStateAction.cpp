#include "State/Wheel/WheelTiltHoldStateAction.h"

#include "Input/Strategy/WheelTiltInputCommandStrategy.h"

WheelTiltHoldStateAction::WheelTiltHoldStateAction(WheelTiltInputCommandStrategy* wheelInputCommand)
    : _wheelInputCommandStrategy(wheelInputCommand)
{}

void WheelTiltHoldStateAction::OnReceiveInputEvent()
{
    _wheelInputCommandStrategy->UpdateWheelTiltInputCommandPressRegister();
}