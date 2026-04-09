#pragma once

class IWheelTiltInputStateAction
{
public:

    virtual ~IWheelTiltInputStateAction() = default;

    virtual void OnReceiveInputEvent() = 0;
};