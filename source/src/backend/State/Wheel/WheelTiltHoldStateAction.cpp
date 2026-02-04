#include <WheelTiltHoldStateAction.h>

#include <WheelTiltInputCommandStrategy.h>

WheelTiltHoldStateAction::WheelTiltHoldStateAction(WheelTiltInputCommandStrategy* wheelInputCommand)
    : _wheelInputCommandStrategy(wheelInputCommand)
{}

void WheelTiltHoldStateAction::OnReceiveInputEvent()
{
    _wheelInputCommandStrategy->UpdateWheelTiltInputCommandPressRegister();
}