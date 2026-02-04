#pragma once
#include <IWheelTiltInputStateAction.h>

class WheelTiltInputCommandStrategy;

class WheelTiltHoldStateAction : public IWheelTiltInputStateAction
{
private:

    WheelTiltInputCommandStrategy* _wheelInputCommandStrategy;

public:

    WheelTiltHoldStateAction(WheelTiltInputCommandStrategy* wheelInputCommandStrategy);

    void OnReceiveInputEvent() override;
};
