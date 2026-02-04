#include <WheelTiltPressStateAction.h>

#include <WheelTiltInputCommandStrategy.h>
#include <WheelTiltHoldStateAction.h>

WheelTiltPressStateAction::WheelTiltPressStateAction(WheelTiltInputCommandStrategy* wheelInputCommandStrategy)
    : _wheelInputCommandStrategy(wheelInputCommandStrategy)
{}

void WheelTiltPressStateAction::OnReceiveInputEvent()
{
    _wheelInputCommandStrategy->Press();
    _wheelInputCommandStrategy->UpdateWheelTiltInputCommandPressRegister();

    _wheelInputCommandStrategy->ChangeState(std::make_unique<WheelTiltHoldStateAction>(_wheelInputCommandStrategy));
}
