#pragma once
#include "backend/State/Wheel/IWheelTiltInputStateAction.h"

class WheelTiltInputCommandStrategy;

class WheelTiltPressStateAction : public IWheelTiltInputStateAction
{
private:

    WheelTiltInputCommandStrategy* _wheelInputCommandStrategy;

public:

    WheelTiltPressStateAction(WheelTiltInputCommandStrategy* wheelInputCommandStrategy);

    void OnReceiveInputEvent() override;
};