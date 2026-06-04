#pragma once
#include "State/Wheel/IWheelTiltInputStateAction.h"

class WheelTiltInputCommandStrategy;

class WheelTiltHoldStateAction : public IWheelTiltInputStateAction
{
public:

    WheelTiltHoldStateAction(WheelTiltInputCommandStrategy* wheelInputCommandStrategy);

    void OnReceiveInputEvent() override;

private:

    WheelTiltInputCommandStrategy* _wheelInputCommandStrategy;

};