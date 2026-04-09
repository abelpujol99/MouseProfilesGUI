#include "Backend/State/Wheel/WheelTiltHoldStateAction.h"

#include "Backend/Input/Strategy/WheelTiltInputCommandStrategy.h"

WheelTiltHoldStateAction::WheelTiltHoldStateAction(WheelTiltInputCommandStrategy* wheelInputCommand)
    : _wheelInputCommandStrategy(wheelInputCommand)
{}

void WheelTiltHoldStateAction::OnReceiveInputEvent()
{
    _wheelInputCommandStrategy->UpdateWheelTiltInputCommandPressRegister();
}