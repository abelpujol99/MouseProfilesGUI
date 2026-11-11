#pragma once
#include "State/Key/IKeyState.h"

class KeyInputStrategy;

class PressKeyState : public IKeyState
{
public:

    PressKeyState(KeyInputStrategy* keyInputStrategy);

    void OnInput(DeviceId deviceId) override;

private:

    KeyInputStrategy* _keyInputStrategy;

};