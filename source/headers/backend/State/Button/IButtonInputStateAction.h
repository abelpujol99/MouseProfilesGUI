#pragma once

class IButtonInputStateAction
{
public:

    virtual ~IButtonInputStateAction() = default;

    virtual void OnReceiveInputEvent() = 0;
};
