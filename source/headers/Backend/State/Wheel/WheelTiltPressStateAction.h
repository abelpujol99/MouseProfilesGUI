#pragma once
#include "Backend/State/Wheel/IWheelTiltInputStateAction.h"

class WheelTiltInputCommandStrategy;

class WheelTiltPressStateAction : public IWheelTiltInputStateAction
{
public:

    WheelTiltPressStateAction(WheelTiltInputCommandStrategy* wheelInputCommandStrategy);

    void OnReceiveInputEvent() override;

private:

    WheelTiltInputCommandStrategy* _wheelInputCommandStrategy;

};